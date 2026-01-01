/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:46:22 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/23 18:59:17 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_nodes_data(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_val;

	tmp_key = a->key;
	tmp_val = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_val;
}

static void	sort_env_list(t_env *head)
{
	int		swapped;
	t_env	*ptr;

	swapped = 1;
	if (!head)
		return ;
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
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	free_env(copy);
	return (0);
}

t_env	*copy_env_list(t_env *env)
{
	t_env	*new_list;
	t_env	*curr;
	t_env	*new_node;
	t_env	*last;

	new_list = NULL;
	curr = env;
	last = NULL;
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
