/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/23 18:55:35 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child_process(char *cmd_path, t_cmd *cmd, t_shell *shell)
{
	char	**envp;

	setup_signals_child();
	if (cmd->redirs && setup_redirections(cmd->redirs) < 0)
		exit(1);
	envp = env_to_array(shell->env);
	if (!envp)
	{
		perror("minishell: env_to_array");
		exit(1);
	}
	execve(cmd_path, cmd->args, envp);
	free_array(envp);
	perror("minishell");
	exit(126);
}

static int	fork_and_execute(char *cmd_path, t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	setup_signals_executing();
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		free(cmd_path);
		setup_signals_interactive();
		return (1);
	}
	if (pid == 0)
		execute_child_process(cmd_path, cmd, shell);
	free(cmd_path);
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	return (get_exit_status(status));
}

int	execute_external_cmd(char **args, t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;

	cmd_path = find_command(args[0], shell);
	if (!cmd_path)
		return (handle_command_not_found(args[0]));
	return (fork_and_execute(cmd_path, cmd, shell));
}
