/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/20 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static const char	*get_node_type_string(t_node_type type)
{
	if (type == NODE_CMD)
		return ("CMD");
	else if (type == NODE_PIPE)
		return ("PIPE");
	else if (type == NODE_AND)
		return ("AND");
	else if (type == NODE_OR)
		return ("OR");
	else if (type == NODE_SUBSHELL)
		return ("SUBSHELL");
	return ("UNKNOWN");
}

static void	print_indent(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
}

static void	print_cmd_args(char **args)
{
	int	i;

	if (!args)
	{
		printf(" (no args)");
		return ;
	}
	printf(" [");
	i = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(", ");
		i++;
	}
	printf("]");
}

void	print_ast(t_ast_node *node, int depth)
{
	if (!node)
		return ;
	print_indent(depth);
	printf("%s", get_node_type_string(node->type));
	if (node->type == NODE_CMD)
		print_cmd_args(node->args);
	printf("\n");
	if (node->left)
		print_ast(node->left, depth + 1);
	if (node->right)
		print_ast(node->right, depth + 1);
}

void	print_ast_inline(t_ast_node *node)
{
	if (!node)
		return ;
	
	if (node->type == NODE_CMD)
	{
		printf("CMD");
		print_cmd_args(node->args);
	}
	else if (node->type == NODE_SUBSHELL)
	{
		printf("(");
		print_ast_inline(node->left);
		printf(")");
	}
	else
	{
		print_ast_inline(node->left);
		printf(" %s ", get_node_type_string(node->type));
		print_ast_inline(node->right);
	}
}
