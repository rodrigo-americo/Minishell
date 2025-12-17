/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:51:18 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/17 10:54:11 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_char(char *s, char c)
{
	char	*new_s;
	int		len;

	if (!s)
		len = 0;
	else
		len = ft_strlen(s);
	new_s = malloc(len + 2);
	if (!new_s)
	{
		free(s);
		return (NULL);
	}
	if (s)
		ft_memcpy(new_s, s, len);
	new_s[len] = c;
	new_s[len + 1] = '\0';
	if (s)
		free(s);
	return (new_s);
}

static char	**split_single_arg(char *arg)
{
	char	**parts;
	int		i;

	parts = ft_split(arg, ' ');
	if (!parts)
		return (NULL);
	i = 0;
	while (parts[i])
	{
		if (ft_strlen(parts[i]) == 0)
		{
			free(parts[i]);
			parts[i] = NULL;
		}
		i++;
	}
	return (parts);
}

static char	**rebuild_args(char **old_args)
{
	char	**new_args;
	char	**parts;
	int		i;
	int		j;

	new_args = NULL;
	i = 0;
	while (old_args && old_args[i])
	{
		if (ft_strchr(old_args[i], ' ') || ft_strchr(old_args[i], '\t'))
		{
			parts = split_single_arg(old_args[i]);
			j = 0;
			while (parts && parts[j])
			{
				new_args = ft_add_to_array(new_args, ft_strdup(parts[j]));
				j++;
			}
			free_array(parts);
		}
		else
			new_args = ft_add_to_array(new_args, ft_strdup(old_args[i]));
		i++;
	}
	return (new_args);
}

void	word_splitting(t_cmd *cmd)
{
	char	**new_args;

	if (!cmd || !cmd->args)
		return ;
	new_args = rebuild_args(cmd->args);
	if (new_args)
	{
		free_array(cmd->args);
		cmd->args = new_args;
	}
}
