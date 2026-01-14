/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int backup_fds(int *bkp) {
  bkp[0] = dup(STDIN_FILENO);
  bkp[1] = dup(STDOUT_FILENO);
  bkp[2] = dup(STDERR_FILENO);
  if (bkp[0] == -1 || bkp[1] == -1 || bkp[2] == -1) {
    if (bkp[0] != -1)
      close(bkp[0]);
    if (bkp[1] != -1)
      close(bkp[1]);
    if (bkp[2] != -1)
      close(bkp[2]);
    return (perror("minishell: dup"), -1);
  }
  return (0);
}

static void restore_fds(int *bkp) {
  dup2(bkp[0], STDIN_FILENO);
  dup2(bkp[1], STDOUT_FILENO);
  dup2(bkp[2], STDERR_FILENO);
  close(bkp[0]);
  close(bkp[1]);
  close(bkp[2]);
}

int exec_builtin_with_redir(char **args, t_redir *redirs, t_shell *shell) {
  int bkp[3];
  int status;

  if (backup_fds(bkp) == -1)
    return (1);
  if (setup_redirections(redirs) == -1) {
    restore_fds(bkp);
    return (1);
  }
  status = execute_builtin(args, shell);
  restore_fds(bkp);
  return (status);
}

int exec_external(char **args, t_redir *redirs, t_shell *shell) {
  char *path;
  char **envp;
  pid_t pid;
  int status;

  path = find_command(args[0], shell);
  if (!path)
    return (handle_command_not_found(args[0]));
  pid = fork();
  if (pid == -1)
    return (perror("minishell: fork"), free(path), 1);
  if (pid == 0) {
    setup_signals_child();
    if (redirs && setup_redirections(redirs) < 0)
      exit(1);
    envp = env_to_array(shell->env);
    execve(path, args, envp);
    perror("minishell");
    exit(126);
  }
  free(path);
  setup_signals_executing();
  waitpid(pid, &status, 0);
  setup_signals_interactive();
  return (get_exit_status(status));
}

static char **duplicate_array(char **arr) {
  char **dup;
  int i;
  int len;

  if (!arr)
    return (NULL);
  len = 0;
  while (arr[len])
    len++;
  dup = malloc(sizeof(char *) * (len + 1));
  if (!dup)
    return (NULL);
  i = 0;
  while (i < len) {
    dup[i] = ft_strdup(arr[i]);
    if (!dup[i]) {
      while (--i >= 0)
        free(dup[i]);
      return (free(dup), NULL);
    }
    i++;
  }
  dup[i] = NULL;
  return (dup);
}

int execute_command(t_ast_node *node, t_shell *shell) {
  char **args_to_use;
  char **args_copy;
  char **expanded;
  int ret;

  expand_command_node(node, shell);

  if (!node->args || !node->args[0])
    return (0);
  args_copy = duplicate_array(node->args);
  if (!args_copy)
    return (1);
  expanded = expand_wildcards(args_copy);
  if (expanded)
    args_to_use = expanded;
  else
    args_to_use = args_copy;
  restore_spaces(args_to_use);
  restore_spaces_in_redirs(node->redirs);
  if (is_builtin(args_to_use[0]))
    ret = exec_builtin_with_redir(args_to_use, node->redirs, shell);
  else
    ret = exec_external(args_to_use, node->redirs, shell);
  if (expanded)
    free_array(expanded);
  else
    free_array(args_copy);
  return (ret);
}
