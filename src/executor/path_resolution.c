/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/15 14:26:39 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_shell *shell)
{
	char	*path_value;
	char	**paths;

	path_value = get_env_value("PATH", shell->env);
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	free(path_value);
	return (paths);
}

static char	*search_in_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*full_path;
	char	*joint;
	int		i;

	paths = get_paths(shell);
	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		joint = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(joint, cmd);
		free(joint);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*find_command(char *cmd, t_shell *shell)
{
	if (!cmd || !shell)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (search_in_path(cmd, shell));
}
