/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/23 19:02:05 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "types.h"

/* Built-in Detection and Execution */
int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_shell *shell);

/* Built-in Commands */
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_shell *shell);
int		builtin_pwd(void);
int		builtin_export(char **args, t_shell *shell);
int		builtin_unset(char **args, t_shell *shell);
int		builtin_env(t_shell *shell);
int		builtin_exit(char **args, t_shell *shell);

/* Built-in Utilities */
char	*get_target_path(char **args, t_env *env);
int		list_sorted_env(t_env *env);
int		is_valid_identifier(char *str);
void	swap_nodes_data(t_env *a, t_env *b);
t_env	*copy_env_list(t_env *env);
int		validate_export_key(char *key, char *value);
void	extract_key_value(char *arg, char **key, char **value);
void	init_validation(char *str, int *i, int *sign);
int		check_overflow(long long num, char digit);
#endif
