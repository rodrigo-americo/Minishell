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

int	fork_and_exec(t_cmd *curr, t_shell *shell, t_exec *ex)
{
	ex->pid = fork();
	if (ex->pid == -1)
	{
		perror("minishell: fork");
		fork_error_cleanup(ex, curr);
		return (-1);
	}
	if (ex->pid == 0)
		child_process(curr, shell, ex, (curr->next != NULL));
	ex->last_pid = ex->pid;
	parent_process(ex, (curr->next != NULL));
	return (0);
}
