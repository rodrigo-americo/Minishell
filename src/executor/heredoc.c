/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:05:49 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/19 10:07:51 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredocs(t_cmd *cmds)
{
	t_cmd	*curr_cmd;
	t_redir	*curr_redir;

	curr_cmd = cmds;
	while (curr_cmd)
	{
		curr_redir = curr_cmd->redirs;
		while (curr_redir)
		{
			if (curr_redir->type == REDIR_HEREDOC && curr_redir->hrdc_fd != -1)
			{
				close(curr_redir->hrdc_fd);
				curr_redir->hrdc_fd = -1;
			}
			curr_redir = curr_redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
}
