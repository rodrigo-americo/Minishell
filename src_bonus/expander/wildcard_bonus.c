/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/03 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <dirent.h>
#include <locale.h>

static void	free_partial_array(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(arr[i++]);
	free(arr);
}

static char	**add_match(char **matches, char *match, int *count)
{
	char	**new_matches;
	int		i;

	new_matches = malloc(sizeof(char *) * (*count + 2));
	if (!new_matches)
		return (NULL);
	i = 0;
	while (i < *count)
	{
		new_matches[i] = matches[i];
		i++;
	}
	new_matches[i] = ft_strdup(match);
	if (!new_matches[i])
	{
		free(new_matches);
		return (NULL);
	}
	new_matches[i + 1] = NULL;
	if (matches)
		free(matches);
	(*count)++;
	return (new_matches);
}

static int	compare_strings(const void *a, const void *b)
{
	return (strcoll(*(const char **)a, *(const char **)b));
}

static char	**expand_single_pattern(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				count;

	matches = NULL;
	count = 0;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match_pattern(pattern, entry->d_name))
		{
			matches = add_match(matches, entry->d_name, &count);
			if (!matches)
				return (closedir(dir), NULL);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (count == 0)
		return (NULL);
	qsort(matches, count, sizeof(char *), compare_strings);
	return (matches);
}

static char	**build_expanded_array(char **args, char **expanded, int idx)
{
	char	**result;
	int		total;
	int		i;
	int		j;

	total = 0;
	i = 0;
	while (args[i])
	{
		if (i != idx)
			total++;
		i++;
	}
	i = 0;
	while (expanded[i++])
		total++;
	result = malloc(sizeof(char *) * (total + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < idx)
	{
		result[i] = ft_strdup(args[i]);
		if (!result[i])
			return (free_partial_array(result, i), NULL);
	}
	j = 0;
	while (expanded[j])
	{
		result[i] = ft_strdup(expanded[j++]);
		if (!result[i])
			return (free_partial_array(result, i), NULL);
		i++;
	}
	while (args[++idx])
	{
		result[i] = ft_strdup(args[idx]);
		if (!result[i])
			return (free_partial_array(result, i), NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**expand_wildcards(char **args)
{
	char	**expanded;
	char	**result;
	int		i;

	if (!args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (has_wildcard(args[i]))
		{
			expanded = expand_single_pattern(args[i]);
			if (expanded)
			{
				result = build_expanded_array(args, expanded, i);
				free_array(expanded);
				if (!result)
					return (NULL);
				free_array(args);
				return (expand_wildcards(result));
			}
		}
		i++;
	}
	return (args);
}
