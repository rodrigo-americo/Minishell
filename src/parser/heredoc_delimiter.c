/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delimiter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:50:25 by ccavalca          #+#    #+#             */
/*   Updated: 2026/01/14 16:52:26 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_quoted_content(char *str, char *result, int i, int j)
{
	char	quote;

	quote = str[i++];
	while (str[i] && str[i] != quote)
		result[j++] = str[i++];
	if (str[i] == quote)
		i++;
	return (i);
}

static char	*process_delimiter_str(char *str, int *is_quoted, char *result)
{
	int		i;
	int		j;

	*is_quoted = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			*is_quoted = 1;
			i = copy_quoted_content(str, result, i, j);
			j = ft_strlen(result);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*remove_delimiter_quotes(char *str, int *is_quoted)
{
	char	*result;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	return (process_delimiter_str(str, is_quoted, result));
}
