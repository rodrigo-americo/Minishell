/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_lines(char *acc, char *line)
{
	char	*result;
	int		len;

	if (!acc)
		return (ft_strdup(line));
	len = ft_strlen(acc);
	if (len > 0 && acc[len - 1] == '\\')
		acc[len - 1] = ' ';
	result = ft_strjoin(acc, line);
	free(acc);
	return (result);
}

char	*join_lines_no_replace(char *acc, char *line)
{
	char	*tmp;
	char	*result;

	if (!acc)
		return (ft_strdup(line));
	tmp = ft_strjoin(acc, " ");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, line);
	free(tmp);
	free(acc);
	return (result);
}
