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

#include "minishell.h"

char	*get_env_value(char *key, t_env *env)
{
    t_env *currunt;

    currunt = env;
    while (currunt)
    {
        if(ft_strcmp(currunt->key, key) == 0)
            return (ft_strdup(currunt->value));
        currunt = currunt->next;
    }
    return (NULL);
}
void	set_env_value(char *key, char *value, t_env **env)
{
	t_env	*current;
	t_env	*new_node;
	char	*new_value;

	if (!key || !value || !env)
		return ;
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			new_value = ft_strdup(value);
			if (!new_value)
				return ;
			free(current->value);
			current->value = new_value;
			return ;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	new_node = create_env_node(key, value);
	if (!new_node)
		return ;
	if (!*env)
		*env = new_node;
	else
		current->next = new_node;
}

void	unset_env_value(char *key, t_env **env)
{
	t_env	*current;
	t_env	*prev;

	if (!key || !env || !*env)
		return ;
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	free_env(t_env *env)
{
    t_env *currunt;
    t_env *tmp;
    currunt = env;
    while (currunt)
    {
        free(currunt->key);
        free(currunt->value);
        tmp = currunt->next;
        free(currunt);
        currunt = tmp;   
    }
}
