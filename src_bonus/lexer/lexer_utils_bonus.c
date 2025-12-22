/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/20 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	init_operator(t_operator *op, char *symbol, int type, int len)
{
	op->symbol = symbol;
	op->type = type;
	op->len = len;
}

void	init_operators_bonus(t_operator operators[10])
{
	init_operator(&operators[0], "&&", TOKEN_AND, 2);
	init_operator(&operators[1], "||", TOKEN_OR, 2);
	init_operator(&operators[2], "<<", TOKEN_REDIR_HEREDOC, 2);
	init_operator(&operators[3], ">>", TOKEN_REDIR_APPEND, 2);
	init_operator(&operators[4], "|", TOKEN_PIPE, 1);
	init_operator(&operators[5], "<", TOKEN_REDIR_IN, 1);
	init_operator(&operators[6], ">", TOKEN_REDIR_OUT, 1);
	init_operator(&operators[7], "(", TOKEN_LPAREN, 1);
	init_operator(&operators[8], ")", TOKEN_RPAREN, 1);
	init_operator(&operators[9], NULL, 0, 0);
}

int	is_operator_start(char c)
{
	return (c == '|' || c == '&' || c == '<' 
		|| c == '>' || c == '(' || c == ')');
}
