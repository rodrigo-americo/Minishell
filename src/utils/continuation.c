/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continuation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/14 17:34:39 by ccavalca         ###   ########.fr       */
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

int	needs_continuation(char *line)
{
	if (ends_with_backslash(line))
		return (1);
	if (ends_with_pipe(line))
		return (2);
	return (0);
}

static char	*join_by_type(char *complete, char *line, int cont_type)
{
	if (cont_type == 1)
		return (join_lines(complete, line));
	else if (cont_type == 2)
		return (join_lines_no_replace(complete, line));
	else
		return (join_lines(complete, line));
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
		complete = join_by_type(complete, line, cont_type);
		free(line);
		if (!complete)
			return (complete);
		if (needs_continuation(complete) == 0)
			return (complete);
	}
}
