/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_pipe(t_exec *ex, t_cmd *curr)
{
	if (curr->next && pipe(ex->fd) == -1)
	{
		if (ex->prev_fd != -1)
			close(ex->prev_fd);
		return (perror("minishell: pipe"), -1);
	}
	return (0);
}

int	fork_and_exec(t_cmd *curr, t_cmd *cmds, t_shell *shell, t_exec *ex)
{
	ex->has_next = (curr->next != NULL);
	ex->pid = fork();
	if (ex->pid == -1)
	{
		perror("minishell: fork");
		fork_error_cleanup(ex, curr);
		return (-1);
	}
	if (ex->pid == 0)
		child_process(curr, cmds, shell, ex);
	ex->last_pid = ex->pid;
	parent_process(ex);
	return (0);
}

int	wait_all(t_exec *ex)
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
