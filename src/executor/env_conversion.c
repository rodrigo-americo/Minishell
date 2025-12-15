/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/14 10:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** env_to_array - Converte lista encadeada de env para array de strings
**
** Formato necessário para execve(): char *envp[]
** Cada string no formato "KEY=VALUE"
** Array terminado com NULL
**
** @env: lista encadeada de variáveis de ambiente
**
** Return: Array de strings NULL-terminated, ou NULL em erro
**
** Exemplo:
**   Input: env = {USER=john} -> {HOME=/home/john} -> NULL
**   Output: ["USER=john", "HOME=/home/john", NULL]
*/

static int	count_env_nodes(t_env *env)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static char	*create_env_string(char *key, char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

char	**env_to_array(t_env *env)
{
	char	**array;
	t_env	*current;
	int		count;
	int		i;

	count = count_env_nodes(env);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		array[i] = create_env_string(current->key, current->value);
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
