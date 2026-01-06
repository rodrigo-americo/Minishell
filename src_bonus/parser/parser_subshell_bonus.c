/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/03 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_ast_node	*parse_subshell(t_list **tokens, t_shell *shell)
{
	t_ast_node	*content;
	t_ast_node	*node;
	t_token		*tok;

	consume_token(tokens);
	content = parse_or(tokens, shell);
	if (!content)
		return (NULL);
	tok = peek_token(*tokens);
	if (!tok || tok->type != TOKEN_RPAREN)
	{
		free_ast(content);
		return (print_error("syntax error", "expected ')'\n"), NULL);
	}
	consume_token(tokens);
	node = create_ast_node(NODE_SUBSHELL);
	if (!node)
		return (free_ast(content), NULL);
	node->left = content;
	node->right = NULL;
	return (node);
}

t_ast_node	*parse_primary(t_list **tokens, t_shell *shell)
{
	t_token	*tok;

	tok = peek_token(*tokens);
	if (!tok)
		return (NULL);
	if (tok->type == TOKEN_LPAREN)
		return (parse_subshell(tokens, shell));
	return (parse_command(tokens, shell));
}
