/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:41:45 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 10:45:45 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_error_cleanup(t_exec *ex, t_cmd *curr)
{
	if (ex->prev_fd != -1)
		close(ex->prev_fd);
	if (curr->next)
	{
		close(ex->fd[0]);
		close(ex->fd[1]);
	}
}
