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

static void	conf_child_pipes(t_exec *ex, int has_next)
{
	if (ex->prev_fd != -1)
	{
		dup2(ex->prev_fd, STDIN_FILENO);
		close(ex->prev_fd);
	}
	if (has_next)
	{
		close(ex->fd[0]);
		dup2(ex->fd[1], STDOUT_FILENO);
		close(ex->fd[1]);
	}
}

static void	child_process(t_cmd *cmd, t_shell *shell, t_exec *ex, int has_next)
{
	char	*path;
	char	**env;

	conf_child_pipes(ex, has_next);
	if (cmd->redirs && setup_redirections(cmd->redirs) < 0)
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, shell));
	path = find_command(cmd->args[0], shell);
	if (!path)
	{
		print_error(cmd->args[0], "command not found\n");
		exit(127);
	}
	env = env_to_array(shell->env);
	execve(path, cmd->args, env);
	perror("minishell");
	exit(126);
}

static void	parent_process(t_exec *ex, int has_next)
{
	if (ex->prev_fd != -1)
		close(ex->prev_fd);
	if (has_next)
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
		if (curr->next && pipe(ex.fd) == -1)
		{
			if (ex.prev_fd != -1)
				close(ex.prev_fd);
			return (perror("minishell: pipe"), 1);
		}
		ex.pid = fork();
		if (ex.pid == -1)
		{
			perror("minishell: fork");
			fork_error_cleanup(&ex, curr);
			return (1);
		}
		if (ex.pid == 0)
			child_process(curr, shell, &ex, (curr->next != NULL));
		ex.last_pid = ex.pid;
		parent_process(&ex, (curr->next != NULL));
		curr = curr->next;
	}
	return (close_heredocs(cmds), wait_all(&ex));
}
