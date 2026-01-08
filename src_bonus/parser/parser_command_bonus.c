/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/03 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static t_ast_node	*parse_cmd_error(t_ast_node *node)
{
	if (node)
		free_ast(node);
	return (NULL);
}

static int	parse_cmd_loop(t_ast_node *node, t_list **tokens, t_shell *shell)
{
	t_token	*tok;
	t_redir	*redir;

	tok = peek_token(*tokens);
	if ((tok->type >= TOKEN_REDIR_IN && tok->type <= TOKEN_REDIR_HEREDOC)
		|| tok->type == TOKEN_REDIR_STDERR_OUT
		|| tok->type == TOKEN_REDIR_STDERR_APPEND)
	{
		redir = parse_redirection(tokens, shell);
		if (!redir)
			return (0);
		add_redir_to_end(&node->redirs, redir);
	}
	else if (tok->type == TOKEN_WORD)
	{
		node->args = ft_add_to_array(node->args, tok->value);
		tok->value = NULL;
		consume_token(tokens);
	}
	else
		return (-1);
	return (1);
}

t_ast_node	*parse_command(t_list **tokens, t_shell *shell)
{
	t_ast_node	*node;
	int			result;

	node = create_ast_node(NODE_CMD);
	if (!node)
		return (NULL);
	node->args = NULL;
	node->redirs = NULL;
	while (peek_token(*tokens) && !is_operator(peek_token(*tokens)))
	{
		result = parse_cmd_loop(node, tokens, shell);
		if (result == 0)
			return (parse_cmd_error(node));
		if (result == -1)
			break ;
	}
	if (!node->args && !node->redirs)
		return (parse_cmd_error(node));
	return (node);
}
