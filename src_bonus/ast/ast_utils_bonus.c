/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/20 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ast_is_operator(t_ast_node *node)
{
	if (!node)
		return (0);
	return (node->type == NODE_PIPE || node->type == NODE_AND
		|| node->type == NODE_OR);
}

int	ast_is_logical_operator(t_ast_node *node)
{
	if (!node)
		return (0);
	return (node->type == NODE_AND || node->type == NODE_OR);
}

int	ast_count_commands(t_ast_node *node)
{
	int	count;

	if (!node)
		return (0);
	
	count = 0;
	if (node->type == NODE_CMD)
		count = 1;
	
	count += ast_count_commands(node->left);
	count += ast_count_commands(node->right);
	
	return (count);
}

int	ast_get_depth(t_ast_node *node)
{
	int	left_depth;
	int	right_depth;

	if (!node)
		return (0);
	
	left_depth = ast_get_depth(node->left);
	right_depth = ast_get_depth(node->right);
	
	if (left_depth > right_depth)
		return (left_depth + 1);
	return (right_depth + 1);
}

int	ast_has_redirs(t_ast_node *node)
{
	if (!node)
		return (0);

	if (node->redirs)
		return (1);

	return (ast_has_redirs(node->left) || ast_has_redirs(node->right));
}
