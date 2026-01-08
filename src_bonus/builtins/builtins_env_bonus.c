/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:44:37 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/19 10:15:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int set_or_error(char *key, char *value, t_shell *shell, char *original_arg) {
  char *error_msg;

  if (is_valid_identifier(key)) {
    set_env_value(key, value, &shell->env);
    return (1);
  }
  error_msg = ft_strjoin("`", original_arg);
  if (error_msg) {
    char *temp = error_msg;
    error_msg = ft_strjoin(error_msg, "': not a valid identifier");
    free(temp);
  }
  if (error_msg) {
    fprintf(stderr, "export: %s\n", error_msg);
    free(error_msg);
  } else {
    print_error("export", "not a valid identifier");
  }
  return (0);
}

static int process_export_arg(char *arg, t_shell *shell) {
  char *key;
  char *value;
  int result;

  key = NULL;
  value = NULL;
  extract_key_value(arg, &key, &value);
  if (!validate_export_key(key, value, arg))
    return (0);
  result = set_or_error(key, value, shell, arg);
  free(key);
  if (value)
    free(value);
  return (result);
}

int builtin_export(char **args, t_shell *shell) {
  int i;
  int status;

  if (!args[1]) {
    list_sorted_env(shell->env);
    return (0);
  }
  status = 0;
  i = 1;
  while (args[i]) {
    if (!process_export_arg(args[i], shell))
      status = 1;
    i++;
  }
  return (status);
}

int builtin_unset(char **args, t_shell *shell) {
  int i;

  i = 1;
  if (!args[i])
    return (0);
  while (args[i]) {
    if (is_valid_identifier(args[i]))
      unset_env_value(args[i], &shell->env);
    /* bash is silent for invalid identifiers in unset */
    i++;
  }
  return (0);
}

int builtin_env(t_shell *shell) {
  t_env *tmp;

  if (!shell || !shell->env)
    return (0);
  tmp = shell->env;
  while (tmp) {
    if (tmp->value)
      printf("%s=%s\n", tmp->key, tmp->value);
    tmp = tmp->next;
  }
  return (0);
}
