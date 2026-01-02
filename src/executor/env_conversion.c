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
#include <sys/stat.h>

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
	int		i;

	array = malloc(sizeof(char *) * (count_env_nodes(env) + 1));
	if (!array)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		array[i] = create_env_string(current->key, current->value);
		if (!array[i])
			return (free_array(array), NULL);
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	handle_command_not_found(char *cmd_name)
{
	struct stat	path_stat;

	if (ft_strchr(cmd_name, '/'))
	{
		if (stat(cmd_name, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		{
			fprintf(stderr, "minishell: %s: Is a directory\n", cmd_name);
			return (126);
		}
		fprintf(stderr, "minishell: %s: No such file or directory\n", cmd_name);
		return (127);
	}
	fprintf(stderr, "minishell: %s: command not found\n", cmd_name);
	return (127);
}
