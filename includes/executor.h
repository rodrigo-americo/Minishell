/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/18 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "types.h"

/* Main Execution */
void	executor(t_cmd *cmds, t_shell *shell);
int		execute_simple_command(t_cmd *cmd, t_shell *shell);
int		execute_pipeline(t_cmd *cmds, t_shell *shell);

/* Redirections */
int		setup_redirections(t_redir *redirs);
int		handle_heredoc(char *delimiter);

/* Path Resolution */
char	*find_command(char *cmd, t_shell *shell);
char	**get_paths(t_shell *shell);

/* Environment Conversion */
char	**env_to_array(t_env *env);

/* Exit Status */
int		get_exit_status(int status);
int		handle_command_not_found(char *cmd_name);

#endif
