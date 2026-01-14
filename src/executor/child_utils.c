/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:45:37 by ccavalca          #+#    #+#             */
/*   Updated: 2026/01/14 16:45:39 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_child(t_cmd *cmds, t_shell *shell, char *path, char **env)
{
	if (path)
		free(path);
	if (env)
		free_array(env);
	free_commands(cmds);
	free_env(shell->env);
	if (shell->input)
		free(shell->input);
	free(shell);
	rl_clear_history();
}

void	child_exit(t_cmd *cmds, t_shell *shell, char *path, int code)
{
	cleanup_child(cmds, shell, path, NULL);
	exit(code);
}

void	conf_child_pipes(t_exec *ex)
{
	if (ex->prev_fd != -1)
	{
		dup2(ex->prev_fd, STDIN_FILENO);
		close(ex->prev_fd);
	}
	if (ex->has_next)
	{
		close(ex->fd[0]);
		dup2(ex->fd[1], STDOUT_FILENO);
		close(ex->fd[1]);
	}
}

void	execute_external_cmd_child(t_cmd *cmd, t_cmd *cmds,
		t_shell *shell, char *path)
{
	char	**env;
	char	**args;

	if (!path)
	{
		print_error(cmd->args[0], "command not found\n");
		child_exit(cmds, shell, NULL, 127);
	}
	env = env_to_array(shell->env);
	args = copy_array(cmd->args);
	cleanup_child(cmds, shell, NULL, NULL);
	execve(path, args, env);
	perror("minishell");
	free(path);
	free_array(args);
	free_array(env);
	exit(126);
}

void	execute_child_builtin(t_cmd *cmd, t_cmd *cmds, t_shell *shell)
{
	int	ret;

	ret = execute_builtin(cmd, shell);
	child_exit(cmds, shell, NULL, ret);
}
