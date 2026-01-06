/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:05:49 by ccavalca          #+#    #+#             */
/*   Updated: 2026/01/03 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	close_redir_heredocs(t_redir *redirs)
{
	t_redir	*curr;

	curr = redirs;
	while (curr)
	{
		if (curr->type == REDIR_HEREDOC && curr->hrdc_fd != -1)
		{
			close(curr->hrdc_fd);
			curr->hrdc_fd = -1;
		}
		curr = curr->next;
	}
}

void	close_heredocs_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
		close_redir_heredocs(node->redirs);
	close_heredocs_ast(node->left);
	close_heredocs_ast(node->right);
}
