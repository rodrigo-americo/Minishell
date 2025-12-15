/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/14 10:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** execute_child_process - Executa comando no processo filho
**
** @cmd_path: caminho completo do executável
** @cmd: estrutura do comando com args
** @shell: ponteiro para estrutura shell
**
** Esta função NUNCA retorna (exit ou execve substitui o processo)
*/
static void	execute_child_process(char *cmd_path, t_cmd *cmd, t_shell *shell)
{
	char	**envp;

	envp = env_to_array(shell->env);
	if (!envp)
	{
		perror("minishell: env_to_array");
		exit(1);
	}
	execve(cmd_path, cmd->args, envp);
	perror("minishell");
	exit(126);
}

/*
** get_exit_status - Extrai exit status do waitpid
**
** @status: status retornado por waitpid
**
** Return: Exit status correto (0-255, ou 128+N se morto por sinal)
*/
static int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

/*
** execute_simple_command - Executa um comando simples (sem pipes)
**
** Algoritmo:
** 1. Valida cmd e cmd->args[0]
** 2. Se builtin: executa e retorna
** 3. Busca executável com find_command()
** 4. Fork + execve
** 5. Aguarda filho e retorna exit status
**
** @cmd: estrutura do comando a executar
** @shell: ponteiro para estrutura shell
**
** Return: Exit status do comando (0-255, ou 127 se não encontrado)
*/
int	execute_simple_command(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd, shell));
	cmd_path = find_command(cmd->args[0], shell);
	if (!cmd_path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", cmd->args[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		free(cmd_path);
		return (1);
	}
	if (pid == 0)
		execute_child_process(cmd_path, cmd, shell);
	free(cmd_path);
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}

/*
** executor - Ponto de entrada principal da execução
**
** Por enquanto executa apenas o primeiro comando (sem pipes).
**
** @cmds: lista encadeada de comandos
** @shell: ponteiro para estrutura shell
*/
void executor(t_cmd *cmds, t_shell *shell)
{
    if (!cmds)
        return;
    shell->exit_status = execute_simple_command(cmds, shell);

    // FASE 2 (depois): iterar por cmds->next para pipes
    // while (cmds)
    // {
    //     executar com pipes...
    //     cmds = cmds->next;
    // }
}