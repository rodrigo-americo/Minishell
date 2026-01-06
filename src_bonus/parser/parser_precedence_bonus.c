/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_precedence.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/03 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_ast_node	*parse_pipe(t_list **tokens, t_shell *shell)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_token		*tok;

	left = parse_primary(tokens, shell);
	if (!left)
		return (NULL);
	while (1)
	{
		tok = peek_token(*tokens);
		if (!tok || tok->type != TOKEN_PIPE)
			break ;
		consume_token(tokens);
		right = parse_primary(tokens, shell);
		if (!right)
			return (free_ast(left), NULL);
		left = create_binary_node(NODE_PIPE, left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_ast_node	*parse_and(t_list **tokens, t_shell *shell)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_token		*tok;

	left = parse_pipe(tokens, shell);
	if (!left)
		return (NULL);
	while (1)
	{
		tok = peek_token(*tokens);
		if (!tok || tok->type != TOKEN_AND)
			break ;
		consume_token(tokens);
		right = parse_pipe(tokens, shell);
		if (!right)
			return (free_ast(left), NULL);
		left = create_binary_node(NODE_AND, left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_ast_node	*parse_or(t_list **tokens, t_shell *shell)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_token		*tok;

	left = parse_and(tokens, shell);
	if (!left)
		return (NULL);
	while (1)
	{
		tok = peek_token(*tokens);
		if (!tok || tok->type != TOKEN_OR)
			break ;
		consume_token(tokens);
		right = parse_and(tokens, shell);
		if (!right)
			return (free_ast(left), NULL);
		left = create_binary_node(NODE_OR, left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}
