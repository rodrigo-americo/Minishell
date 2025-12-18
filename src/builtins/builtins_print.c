/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:17:40 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/17 17:45:32 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (args[i] && !ft_strncmp(args[i], "-n", 2) && args[i][2] == '\0')
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
	(void)args;
	(void)shell;
	return (0);
}

// int	builtin_cd(char **args, t_shell *shell)
// {
// 	int		i;
// 	char	*home_path;
// 	char	*old_pwd;
// 	char	*path;

// 	home_path = get_env_value(shell->env, "HOME");
// 	old_pwd = get_env_value(shell->env, "PWD");
// 	i = 1;
// 	if (!args[i])
// 	{
// 		path =
// 		chdir()
// 	}
// 	else
// 	{
// 		if (chdir(path) == 0)
// 		{
// 			update_existing_env(shell->env, old_pwd);
// 			update_existing_env
// 		}
// 		print_error("cd", "cd: HOME not set");
// 	}
// 	return (1);
// }

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
