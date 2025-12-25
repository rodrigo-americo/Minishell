/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:24:02 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/17 17:41:44 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_existing_env(t_env *current, char *value)
{
	char	*new_value;

	if (!value)
		return (1);
	new_value = ft_strdup(value);
	if (!new_value)
		return (0);
	free(current->value);
	current->value = new_value;
	return (1);
}

static t_env	*find_env_node(t_env *env, char *key, t_env **last)
{
	t_env	*current;

	current = env;
	*last = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		*last = current;
		current = current->next;
	}
	return (NULL);
}

static int	add_new_env_node(t_env **env, t_env *last, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value);
	if (!new_node)
		return (0);
	if (!*env)
		*env = new_node;
	else
		last->next = new_node;
	return (1);
}

void	set_env_value(char *key, char *value, t_env **env)
{
	t_env	*found;
	t_env	*last;

	if (!key || !value || !env)
		return ;
	found = find_env_node(*env, key, &last);
	if (found)
		update_existing_env(found, value);
	else
		add_new_env_node(env, last, key, value);
}
