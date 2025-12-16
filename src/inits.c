/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/15 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_operator(t_operator *op, char *symbol, int type, int len)
{
	op->symbol = symbol;
	op->type = type;
	op->len = len;
}

void	init_operators(t_operator operators[6])
{
	init_operator(&operators[0], ">>", TOKEN_REDIR_APPEND, 2);
	init_operator(&operators[1], "<<", TOKEN_REDIR_HEREDOC, 2);
	init_operator(&operators[2], ">", TOKEN_REDIR_OUT, 1);
	init_operator(&operators[3], "<", TOKEN_REDIR_IN, 1);
	init_operator(&operators[4], "|", TOKEN_PIPE, 1);
	init_operator(&operators[5], NULL, 0, 0);
}
