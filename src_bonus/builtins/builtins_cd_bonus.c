/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/02 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	get_old_pwd(char *old_path, t_env *env)
{
	char	*pwd;

	if (getcwd(old_path, PATH_MAX_LEN) == NULL)
	{
		pwd = get_env_value("PWD", env);
		if (pwd)
		{
			ft_strlcpy(old_path, pwd, PATH_MAX_LEN);
			return (1);
		}
		perror("cd: getcwd");
		return (0);
	}
	return (1);
}

static int	change_directory(char *path)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (0);
	}
	return (1);
}

static int	update_pwd(char *old_path, char *path, t_env **env)
{
	char	new_pwd[PATH_MAX_LEN];
	char	*old_pwd;

	set_env_value("OLDPWD", old_path, env);
	if (getcwd(new_pwd, PATH_MAX_LEN) != NULL)
	{
		set_env_value("PWD", new_pwd, env);
		return (1);
	}
	old_pwd = get_env_value("PWD", *env);
	if (old_pwd && path[0] != '/')
	{
		ft_strlcpy(new_pwd, old_path, PATH_MAX_LEN);
		ft_strlcat(new_pwd, "/", PATH_MAX_LEN);
		ft_strlcat(new_pwd, path, PATH_MAX_LEN);
		set_env_value("PWD", new_pwd, env);
		return (1);
	}
	set_env_value("PWD", path, env);
	return (1);
}

int	builtin_cd(char **args, t_shell *shell)
{
	char	*path;
	char	old_path[PATH_MAX_LEN];

	if (!get_old_pwd(old_path, shell->env))
		return (1);
	path = get_target_path(args, shell->env);
	if (!path)
		return (1);
	if (!change_directory(path))
	{
		free(path);
		return (1);
	}
	if (!update_pwd(old_path, path, &shell->env))
	{
		free(path);
		return (1);
	}
	free(path);
	return (0);
}
