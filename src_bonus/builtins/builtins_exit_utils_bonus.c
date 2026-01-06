/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

void	cleanup_and_exit(int code)
{
	int	fd;

	fd = 3;
	while (fd < MAX_FD)
		close(fd++);
	exit(code);
}
