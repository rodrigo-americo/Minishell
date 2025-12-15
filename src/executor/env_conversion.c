/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/15 15:29:29 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_array(t_env *env)
{
	char	**arr;
	char	*temp;
	int		size;
	int		i;

	size = ft_lstsize(env);
	arr = malloc(sizeof(char *) * (sizeof(size + 1)));
	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		arr[i] = ft_strjoin(temp, env->value);
		free(temp);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
