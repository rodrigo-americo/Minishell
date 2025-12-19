/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/16 11:27:25 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_cmd *cmd, t_shell *shell, t_exec *ex, int has_next)
{
	char	*path;
	char	**env;

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
	if (cmd->redirs && setup_redirections(cmd->redirs) < 0)
		exit(1);
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
		exit_code = get_exit_status(status);
	}
	while (wait(NULL) != -1)
		continue ;
	return (exit_code);
}

static int	init_exec(t_exec *ex)
{
	ex->prev_fd = -1;
	ex->last_pid = -1;
	return (0);
}

int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	t_exec	ex;
	t_cmd	*curr;

	init_exec(&ex);
	setup_signals_executing();
	curr = cmds;
	while (curr)
	{
		if (curr->next && pipe(ex.fd) == -1)
			return (perror("minishell: pipe"), 1);
		ex.pid = fork();
		if (ex.pid == -1)
		{
			perror("minishell: fork");
			if (curr->next)
			{
				close(ex.fd[0]);
				close(ex.fd[1]);
			}
			if (ex.prev_fd != -1)
				close(ex.prev_fd);
			return (1);
		}
		if (ex.pid == 0)
			child_process(curr, shell, &ex, (curr->next != NULL));
		ex.last_pid = ex.pid;
		parent_process(&ex, (curr->next != NULL));
		curr = curr->next;
	}
	return (wait_all(&ex));
}
