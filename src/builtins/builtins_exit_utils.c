/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-14 14:11:35 by rgregori          #+#    #+#             */
/*   Updated: 2026-01-14 14:11:35 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_validation(char *str, int *i, int *sign)
{
	*i = 0;
	*sign = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			*sign = -1;
		(*i)++;
	}
}

int	check_overflow(long long num, char digit)
{
	if (num > LLONG_MAX_DIV_10)
		return (1);
	if (num == LLONG_MAX_DIV_10 && (digit - '0') > LLONG_MAX_MOD_10)
		return (1);
	return (0);
}
