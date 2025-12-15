/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/15 10:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** count_commands - Conta quantos comandos há na pipeline
**
** @cmds: lista encadeada de comandos
**
** Return: Número de comandos
*/
static int	count_commands(t_cmd *cmds)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmds;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/*
** setup_child_pipes - Configura pipes para processo filho
**
** @i: índice do comando atual
** @pipe_fd: array de file descriptors do pipe atual
** @prev_fd: file descriptor de leitura do pipe anterior
** @n_cmds: total de comandos na pipeline
**
** Lógica:
** - Primeiro comando: stdout → pipe[1]
** - Comandos do meio: stdin ← prev_fd, stdout → pipe[1]
** - Último comando: stdin ← prev_fd
*/
static void	setup_child_pipes(int i, int pipe_fd[2], int prev_fd, int n_cmds)
{
	if (i > 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i < n_cmds - 1)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

/*
** execute_pipeline_command - Executa um comando dentro de pipeline
**
** @cmd: comando a executar
** @shell: estrutura shell
** @i: índice do comando
** @pipe_fd: file descriptors do pipe atual
** @prev_fd: file descriptor do pipe anterior
** @n_cmds: total de comandos
*/
static void	exec_pipe_cmd(t_cmd *cmd, t_shell *shell, int i, int *data)
{
	char	*cmd_path;
	char	**envp;

	setup_signals_child();
	setup_child_pipes(i, &data[0], data[2], data[3]);
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, shell));
	cmd_path = find_command(cmd->args[0], shell);
	if (!cmd_path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", cmd->args[0]);
		exit(127);
	}
	envp = env_to_array(shell->env);
	if (!envp)
	{
		free(cmd_path);
		exit(1);
	}
	execve(cmd_path, cmd->args, envp);
	perror("minishell");
	exit(126);
}

/*
** execute_pipeline - Executa pipeline de comandos
**
** Algoritmo:
** 1. Conta número de comandos
** 2. Para cada comando:
**    a. Cria pipe (exceto último)
**    b. Fork processo filho
**    c. Filho: configura pipes e executa comando
**    d. Pai: fecha pipe[1], salva pipe[0] como prev_fd
** 3. Aguarda todos os filhos terminarem
**
** @cmds: lista encadeada de comandos
** @shell: estrutura shell
**
** Return: Exit status do último comando
*/
int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		n_cmds;
	int		pipe_fd[2];
	int		prev_fd;
	int		i;
	t_cmd	*current;
	pid_t	pid;
	int		status;
	int		last_status;
	int		data[4];

	setup_signals_executing();
	n_cmds = count_commands(cmds);
	prev_fd = -1;
	i = 0;
	current = cmds;
	while (current)
	{
		if (i < n_cmds - 1)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("minishell: pipe");
				return (1);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork");
			if (prev_fd != -1)
				close(prev_fd);
			return (1);
		}
		if (pid == 0)
		{
			data[0] = pipe_fd[0];
			data[1] = pipe_fd[1];
			data[2] = prev_fd;
			data[3] = n_cmds;
			exec_pipe_cmd(current, shell, i, data);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (i < n_cmds - 1)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		i++;
		current = current->next;
	}
	i = 0;
	while (i < n_cmds)
	{
		wait(&status);
		last_status = get_exit_status(status);
		i++;
	}
	setup_signals_interactive();
	return (last_status);
}
