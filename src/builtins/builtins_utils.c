/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:46:22 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/18 11:48:37 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_target_path(char **args, t_env *env)
{
	char	*path;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = get_env_value("HOME", env);
		if (!path)
			print_error("cd", "HOME not set");
		return (path);
	}
	return (ft_strdup(args[1]));
}

int is_valid_identifier(char *str)
{
	int i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void swap_nodes_data(t_env *a, t_env *b)
{
	char *tmp_key = a->key;
	char *tmp_val = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_val;
}

static void	sort_env_list(t_env *head)
{
	int     swapped;
	t_env   *ptr;
	
	swapped = 1;
	if (!head) return;
	while (swapped)
	{
		swapped = 0;
		ptr = head;
		while (ptr->next)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				swap_nodes_data(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
	}
}

int	list_sorted_env(t_env *env)
{
	t_env	*copy;
	t_env	*tmp;

	copy = copy_env_list(env);
	sort_env_list(copy);
	
	tmp = copy;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	
	free_env(copy);
	return (0);
}


t_env *copy_env_list(t_env *env)
{
    t_env *new_list = NULL;
    t_env *curr = env;
    t_env *new_node;
    t_env *last = NULL;

    while (curr)
    {
        new_node = create_env_node(curr->key, curr->value);
        if (!new_node)
            return (free_env(new_list), NULL);
        if (!new_list)
            new_list = new_node;
        else
            last->next = new_node;
        last = new_node;
        curr = curr->next;
    }
    return (new_list);
}