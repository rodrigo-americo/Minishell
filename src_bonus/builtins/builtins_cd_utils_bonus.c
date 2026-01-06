/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/02 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	validate_args_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		print_error("cd", "too many arguments");
		return (0);
	}
	return (1);
}

static char	*get_home_path(t_env *env)
{
	char	*path;

	path = get_env_value("HOME", env);
	if (!path)
		print_error("cd", "HOME not set");
	return (path);
}

static char	*get_oldpwd_path(t_env *env)
{
	char	*path;

	path = get_env_value("OLDPWD", env);
	if (!path)
	{
		print_error("cd", "OLDPWD not set");
		return (NULL);
	}
	return (path);
}

char	*get_target_path(char **args, t_env *env)
{
	if (!validate_args_count(args))
		return (NULL);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		return (get_home_path(env));
	if (ft_strcmp(args[1], "-") == 0)
		return (get_oldpwd_path(env));
	return (ft_strdup(args[1]));
}
