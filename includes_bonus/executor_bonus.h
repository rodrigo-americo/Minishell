/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bonus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 10:45:07 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_BONUS_H
#  define EXECUTOR_BONUS_H

#  include "types_bonus.h"

/* Redirections */
int		setup_redirections(t_redir *redirs);

/* Path Resolution */
char	*find_command(char *cmd, t_shell *shell);
char	**get_paths(t_shell *shell);

/* Environment Conversion */
char	**env_to_array(t_env *env);

/* Exit Status */
int		get_exit_status(int status);
int		handle_command_not_found(char *cmd_name);

/* ************************************************************************** */
/*                         BONUS: AST EXECUTOR                                */
/* ************************************************************************** */

/* Main Executor */
int		executor(t_ast_node *node, t_shell *shell);

/* Command Execution */
int		execute_command(t_ast_node *node, t_shell *shell);
int		exec_builtin_with_redir(char **args, t_redir *redirs, t_shell *shell);
int		exec_external(char **args, t_redir *redirs, t_shell *shell);

/* Logical Operators */
int		execute_and(t_ast_node *node, t_shell *shell);
int		execute_or(t_ast_node *node, t_shell *shell);

/* Pipe and Subshell */
int		execute_pipe(t_ast_node *node, t_shell *shell);
int		execute_subshell(t_ast_node *node, t_shell *shell);

/* Heredoc Cleanup for AST */
void	close_heredocs_ast(t_ast_node *node);

#endif
