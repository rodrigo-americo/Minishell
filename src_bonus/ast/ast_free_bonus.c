/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/20 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	free_ast_redirs(t_redir *redirs)
{
	t_redir	*current;
	t_redir	*next;

	current = redirs;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	if (node->args)
		free_array(node->args);
	if (node->redirs)
		free_ast_redirs(node->redirs);
	free(node);
}

void	free_ast_preserve_data(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_ast_preserve_data(node->left);
	if (node->right)
		free_ast_preserve_data(node->right);
	free(node);
}
