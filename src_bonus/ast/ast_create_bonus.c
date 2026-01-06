/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/20 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_ast_node	*create_ast_node(t_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->redirs = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*create_cmd_node(char **args, t_redir *redirs)
{
	t_ast_node	*node;

	node = create_ast_node(NODE_CMD);
	if (!node)
		return (NULL);
	node->args = args;
	node->redirs = redirs;
	return (node);
}

t_ast_node	*create_operator_node(t_node_type type, t_ast_node *left,
								t_ast_node *right)
{
	t_ast_node	*node;

	node = create_ast_node(type);
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_ast_node	*create_subshell_node(t_ast_node *child, t_redir *redirs)
{
	t_ast_node	*node;

	node = create_ast_node(NODE_SUBSHELL);
	if (!node)
		return (NULL);
	node->left = child;
	node->redirs = redirs;
	return (node);
}
