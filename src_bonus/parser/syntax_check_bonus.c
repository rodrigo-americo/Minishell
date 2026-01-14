/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:48:15 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/03 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	check_pipe_syntax(t_list *node, int is_first)
{
	t_token	*next;

	(void)node->content;
	if (!node->next || is_first)
		return (print_error("syntax error", "unexpected token '|'"), 1);
	next = (t_token *)node->next->content;
	if (next->type == TOKEN_PIPE || next->type == TOKEN_AND
		|| next->type == TOKEN_OR)
		return (print_error("syntax error", "unexpected token"), 1);
	return (0);
}

static int	check_logical_syntax(t_list *node, int is_first)
{
	t_token	*tok;
	t_token	*next;

	tok = (t_token *)node->content;
	if (!node->next || is_first)
	{
		if (tok->type == TOKEN_AND)
			return (print_error("syntax error", "unexpected token '&&'"), 1);
		return (print_error("syntax error", "unexpected token '||'"), 1);
	}
	next = (t_token *)node->next->content;
	if (next->type == TOKEN_PIPE || next->type == TOKEN_AND
		|| next->type == TOKEN_OR)
		return (print_error("syntax error", "unexpected token"), 1);
	return (0);
}

static int	is_operator_string(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "&") == 0)
		return (1);
	if (ft_strcmp(str, "&&") == 0)
		return (1);
	if (ft_strcmp(str, "||") == 0)
		return (1);
	return (0);
}

static int	check_redir_syntax(t_list *node)
{
	t_token	*next;

	if (!node->next)
		return (print_error("syntax error", "unexpected newline"), 1);
	next = (t_token *)node->next->content;
	if (next->type != TOKEN_WORD)
		return (print_error("syntax error", "unexpected token"), 1);
	if (is_operator_string(next->value))
		return (print_error("syntax error", "unexpected token"), 1);
	if (next->value && next->value[0] == '&' && next->value[1] == '\0')
		return (print_error("syntax error", "unexpected token '&'"), 1);
	return (0);
}

static int	count_parens(t_list *node)
{
	t_token	*tok;
	int		paren_count;

	paren_count = 0;
	while (node)
	{
		tok = (t_token *)node->content;
		if (tok->type == TOKEN_LPAREN)
			paren_count++;
		else if (tok->type == TOKEN_RPAREN)
		{
			paren_count--;
			if (paren_count == 0)
				return (0);
		}
		node = node->next;
	}
	if (paren_count > 0)
		return (1);
	return (paren_count);
}

static int	check_paren_syntax(t_list *node)
{
	t_token	*tok;
	t_list	*current;

	tok = (t_token *)node->content;
	if (tok->type == TOKEN_LPAREN)
	{
		current = node->next;
		if (!current || ((t_token *)current->content)->type == TOKEN_RPAREN)
			return (print_error("syntax error", "empty parentheses"), 1);
		if (count_parens(node) != 0)
			return (print_error("syntax error", "unmatched '('"), 1);
	}
	return (0);
}

static int	is_redir_token(int type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC
		|| type == TOKEN_REDIR_STDERR_OUT || type == TOKEN_REDIR_STDERR_APPEND);
}

static int	check_token_syntax(t_list *node, t_token *tok, int is_first)
{
	if (tok->type == TOKEN_PIPE && check_pipe_syntax(node, is_first))
		return (1);
	if ((tok->type == TOKEN_AND || tok->type == TOKEN_OR)
		&& check_logical_syntax(node, is_first))
		return (1);
	if (is_redir_token(tok->type) && check_redir_syntax(node))
		return (1);
	if ((tok->type == TOKEN_LPAREN || tok->type == TOKEN_RPAREN)
		&& check_paren_syntax(node))
		return (1);
	return (0);
}

int	check_syntax(t_list *tokens)
{
	t_list	*node;
	t_token	*tok;
	int		is_first;

	node = tokens;
	is_first = 1;
	while (node)
	{
		tok = (t_token *)node->content;
		if (check_token_syntax(node, tok, is_first))
			return (1);
		is_first = 0;
		node = node->next;
	}
	return (0);
}
