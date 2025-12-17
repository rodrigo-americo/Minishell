/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:48:15 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/17 11:50:42 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_list *node, t_cmd *head)
{
	t_token	*tok;
	t_token	*next;

	tok = (t_token *)node->content;
	if (ft_strcmp(tok->value, "|") == 0)
	{
		if (!head || !node->next)
			return (print_error("syntax error", "unexpected token '|'\n"), 1);
		next = (t_token *)node->next->content;
		if (ft_strcmp(next->value, "|") == 0)
			return (print_error("syntax error", "unexpected token '|'\n"), 1);
	}
	if (tok->type >= TOKEN_REDIR_IN)
	{
		if (!node->next)
			return (print_error("syntax error", "unexpected newline\n"), 1);
		next = (t_token *)node->next->content;
		if (next->type != TOKEN_WORD)
			return (print_error("syntax error", "unexpected token\n"), 1);
	}
	return (0);
}
