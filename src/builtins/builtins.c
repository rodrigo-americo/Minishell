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
** execute_builtin - Executa comando built-in (STUB por enquanto)
**
** Por enquanto apenas imprime mensagem que não está implementado.
** Implementação completa virá depois.
**
** @cmd: estrutura do comando
** @shell: ponteiro para estrutura shell
**
** Return: Exit status (0 por enquanto)
*/
int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	(void)shell;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	printf("Built-in '%s' not yet implemented\n", cmd->args[0]);
	return (0);
}
