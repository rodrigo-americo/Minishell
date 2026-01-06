/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:53:02 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/12 13:07:57 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free(node->key);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

static t_env	*create_and_link_node(char *envp_line)
{
	char	*equal;
	char	*key;
	char	*value;
	t_env	*new;

	if (!envp_line || !*envp_line)
		return (NULL);
	equal = ft_strchr(envp_line, '=');
	if (!equal)
		return (NULL);
	key = ft_substr(envp_line, 0, equal - envp_line);
	value = ft_strdup(equal + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (NULL);
	}
	new = create_env_node(key, value);
	free(key);
	free(value);
	return (new);
}

t_env	*create_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		new = create_and_link_node(envp[i]);
		if (new)
		{
			if (!head)
				head = new;
			else
				current->next = new;
			current = new;
		}
		i++;
	}
	return (head);
}
