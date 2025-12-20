/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 11:30:00 by rgregori         ###   ########.fr       */
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
	perror("minishell");
	exit(126);
}

static int	exec_builtin_wrapper(t_cmd *cmd, t_shell *shell)
{
	int	bkp[2];
	int	ret;

	bkp[0] = dup(STDIN_FILENO);
	bkp[1] = dup(STDOUT_FILENO);
	if (cmd->redirs && setup_redirections(cmd->redirs) < 0)
	{
		dup2(bkp[0], STDIN_FILENO);
		dup2(bkp[1], STDOUT_FILENO);
		close(bkp[0]);
		close(bkp[1]);
		return (1);
	}
	ret = execute_builtin(cmd, shell);
	dup2(bkp[0], STDIN_FILENO);
	dup2(bkp[1], STDOUT_FILENO);
	close(bkp[0]);
	close(bkp[1]);
	return (ret);
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

int	execute_simple_command(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (is_builtin(cmd->args[0]))
		return (exec_builtin_wrapper(cmd, shell));
	cmd_path = find_command(cmd->args[0], shell);
	if (!cmd_path)
		return (handle_command_not_found(cmd->args[0]));
	return (fork_and_execute(cmd_path, cmd, shell));
}

void	executor(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return ;
	if (cmds->next)
		shell->exit_status = execute_pipeline(cmds, shell);
	else
		shell->exit_status = execute_simple_command(cmds, shell);
	close_heredocs(cmds);
}
