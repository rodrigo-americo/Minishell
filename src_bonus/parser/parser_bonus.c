/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:30:33 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/03 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_token	*peek_token(t_list *tokens)
{
	if (!tokens)
		return (NULL);
	return ((t_token *)tokens->content);
}

t_token	*consume_token(t_list **tokens)
{
	t_token	*token;

	if (!tokens || !*tokens)
		return (NULL);
	token = peek_token(*tokens);
	*tokens = (*tokens)->next;
	return (token);
}

int	is_operator(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == TOKEN_PIPE || tok->type == TOKEN_AND
		|| tok->type == TOKEN_OR || tok->type == TOKEN_LPAREN
		|| tok->type == TOKEN_RPAREN)
		return (1);
	return (0);
}

t_ast_node	*create_binary_node(t_node_type type, t_ast_node *left,
		t_ast_node *right)
{
	t_ast_node	*node;

	node = create_ast_node(type);
	if (!node)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	node->left = left;
	node->right = right;
	return (node);
}

t_ast_node	*parser(t_list *tokens, t_shell *shell)
{
	t_list		*current;
	t_ast_node	*ast;

	if (!tokens)
		return (NULL);
	if (check_syntax(tokens))
		return (NULL);
	current = tokens;
	ast = parse_or(&current, shell);
	if (!ast)
		return (NULL);
	if (current != NULL)
	{
		print_error("syntax error", "unexpected token\n");
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}
