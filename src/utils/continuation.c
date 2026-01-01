/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continuation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quotes(char *str, int i)
{
	char	quote;

	if (str[i] != '\'' && str[i] != '\"')
		return (i);
	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

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

int	needs_continuation(char *line)
{
	if (ends_with_backslash(line))
		return (1);
	if (ends_with_pipe(line))
		return (2);
	return (0);
}

char	*read_with_continuation(char *prompt)
{
	char	*line;
	char	*complete;
	int		cont_type;

	complete = NULL;
	while (1)
	{
		if (complete)
			line = readline("> ");
		else
			line = readline(prompt);
		if (!line)
			return (complete);
		cont_type = needs_continuation(line);
		if (cont_type == 1)
			complete = join_lines(complete, line);
		else if (cont_type == 2)
			complete = join_lines_no_replace(complete, line);
		else
			complete = join_lines(complete, line);
		free(line);
		if (!complete || cont_type == 0)
			return (complete);
	}
}
