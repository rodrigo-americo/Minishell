/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continuation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-14 13:51:44 by rgregori          #+#    #+#             */
/*   Updated: 2026-01-14 13:51:44 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ends_with_backslash(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len == 0)
		return (0);
	return (str[len - 1] == '\\');
}

int	ends_with_pipe(char *str)
{
	int	len;
	int	i;

	if (!str)
		return (0);
	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = skip_quotes(str, i);
		else
			i++;
	}
	i = len - 1;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (i >= 0 && str[i] == '|')
		return (1);
	return (0);
}
