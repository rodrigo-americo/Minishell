/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/14 10:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(char **args, t_shell *shell)
{
	char	*cmd_name;

	if (!args || !args[0])
		return (0);
	cmd_name = args[0];
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (builtin_echo(args));
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (builtin_cd(args, shell));
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd_name, "export") == 0)
		return (builtin_export(args, shell));
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (builtin_unset(args, shell));
	if (ft_strcmp(cmd_name, "env") == 0)
		return (builtin_env(shell));
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (builtin_exit(args, shell));
	return (0);
}
