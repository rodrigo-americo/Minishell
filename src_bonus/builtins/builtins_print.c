/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:17:40 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/19 09:40:44 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}

int	builtin_cd(char **args, t_shell *shell)
{
	char	*path;
	char	old_path[PATH_MAX_LEN];
	char	new_pwd[PATH_MAX_LEN];

	if (getcwd(old_path, PATH_MAX_LEN) == NULL)
		return (1);
	path = get_target_path(args, shell->env);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		print_error("cd", "No such file or directory");
		free(path);
		return (1);
	}
	update_existing_env(shell->env, old_path);
	if (getcwd(new_pwd, PATH_MAX_LEN))
		update_existing_env(shell->env, new_pwd);
	free(path);
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[PATH_MAX_LEN];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	print_error("pwd", "failed to getcwd");
	return (1);
}
