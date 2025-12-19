/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:51:18 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 10:59:44 by rgregori         ###   ########.fr       */
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
		return (NULL);
	if (s)
		ft_memcpy(new_s, s, len);
	new_s[len] = c;
	new_s[len + 1] = '\0';
	return (new_s);
}

static char	**add_split_parts(char **new_args, char *arg)
{
	char	**parts;
	char	*dup;
	int		i;

	parts = ft_split(arg, ' ');
	if (!parts)
		return (new_args);
	i = 0;
	while (parts[i])
	{
		dup = ft_strdup(parts[i]);
		if (dup)
			new_args = ft_add_to_array(new_args, dup);
		i++;
	}
	free_array(parts);
	return (new_args);
}

static char	**process_arg_token(char **new_args, char *arg)
{
	char	*dup;

	if (ft_strchr(arg, ' ') || ft_strchr(arg, '\t'))
		return (add_split_parts(new_args, arg));
	dup = ft_strdup(arg);
	if (!dup)
		return (new_args);
	return (ft_add_to_array(new_args, dup));
}

static char	**rebuild_args(char **old_args)
{
	char	**new_args;
	int		i;

	new_args = NULL;
	i = 0;
	while (old_args && old_args[i])
	{
		new_args = process_arg_token(new_args, old_args[i]);
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
