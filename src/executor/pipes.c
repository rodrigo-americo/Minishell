/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 12:30:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_child(t_cmd *cmds, t_shell *shell, char *path, char **env)
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

static void	child_exit(t_cmd *cmds, t_shell *shell, char *path,
		int code)
{
	cleanup_child(cmds, shell, path, NULL);
	exit(code);
}

static void	conf_child_pipes(t_exec *ex)
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

void	child_process(t_cmd *cmd, t_cmd *cmds, t_shell *shell, t_exec *ex)
{
	char	*path;
	char	**env;
	int		builtin_ret;

	conf_child_pipes(ex);
	if (cmd->redirs && setup_redirections(cmd->redirs) < 0)
		child_exit(cmds, shell, NULL, 1);
	close_heredocs(cmds);
	if (!cmd->args || !cmd->args[0])
		child_exit(cmds, shell, NULL, 0);
	if (is_builtin(cmd->args[0]))
	{
		builtin_ret = execute_builtin(cmd, shell);
		child_exit(cmds, shell, NULL, builtin_ret);
	}
	path = find_command(cmd->args[0], shell);
	if (!path)
	{
		print_error(cmd->args[0], "command not found\n");
		child_exit(cmds, shell, NULL, 127);
	}
	env = env_to_array(shell->env);
	execve(path, cmd->args, env);
	perror("minishell");
	cleanup_child(cmds, shell, path, env);
	exit(126);
}

void	parent_process(t_exec *ex)
{
	if (ex->prev_fd != -1)
		close(ex->prev_fd);
	if (ex->has_next)
	{
		close(ex->fd[1]);
		ex->prev_fd = ex->fd[0];
	}
	else
		ex->prev_fd = -1;
}

static int	wait_all(t_exec *ex)
{
	int	exit_code;
	int	status;

	exit_code = 0;
	if (ex->last_pid != -1)
	{
		waitpid(ex->last_pid, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
	}
	while (wait(NULL) != -1)
		continue ;
	return (exit_code);
}

int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	t_exec	ex;
	t_cmd	*curr;

	ex.prev_fd = -1;
	ex.last_pid = -1;
	setup_signals_executing();
	curr = cmds;
	while (curr)
	{
		if (setup_pipe(&ex, curr) == -1)
			return (1);
		if (fork_and_exec(curr, cmds, shell, &ex) == -1)
			return (1);
		curr = curr->next;
	}
	return (close_heredocs(cmds), wait_all(&ex));
}
