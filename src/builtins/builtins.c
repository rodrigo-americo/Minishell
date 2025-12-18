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

#include "minishell.h"

/*
** is_builtin - Verifica se comando é um built-in
**
** Built-ins são: echo, cd, pwd, export, unset, env, exit
**
** @cmd: nome do comando
**
** Return: 1 se é builtin, 0 senão
*/

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

/*
** execute_builtin - Executa comando built-in
**
** Faz o dispatch para a função correta baseado no nome do comando.
** Cada built-in retorna seu próprio exit status.
**
** @cmd: estrutura do comando
** @shell: ponteiro para estrutura shell
**
** Return: Exit status do built-in executado
*/
int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_name;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	cmd_name = cmd->args[0];
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (builtin_echo(cmd->args));
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (builtin_cd(cmd->args, shell));
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd_name, "export") == 0)
		return (builtin_export(cmd->args, shell));
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (builtin_unset(cmd->args, shell));
	if (ft_strcmp(cmd_name, "env") == 0)
		return (builtin_env(shell));
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (builtin_exit(cmd->args, shell));
	return (0);
}
