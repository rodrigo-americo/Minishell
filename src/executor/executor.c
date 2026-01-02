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

static int	backup_fds(int *bkp)
{
	bkp[0] = dup(STDIN_FILENO);
	bkp[1] = dup(STDOUT_FILENO);
	bkp[2] = dup(STDERR_FILENO);
	if (bkp[0] == -1 || bkp[1] == -1 || bkp[2] == -1)
	{
		if (bkp[0] != -1)
			close(bkp[0]);
		if (bkp[1] != -1)
			close(bkp[1]);
		if (bkp[2] != -1)
			close(bkp[2]);
		return (perror("minishell: dup"), -1);
	}
	return (0);
}

static void	restore_fds(int *bkp)
{
	dup2(bkp[0], STDIN_FILENO);
	dup2(bkp[1], STDOUT_FILENO);
	dup2(bkp[2], STDERR_FILENO);
	close(bkp[0]);
	close(bkp[1]);
	close(bkp[2]);
}

static int	exec_builtin_wrapper(t_cmd *cmd, t_shell *shell)
{
	int	bkp[3];
	int	ret;

	if (backup_fds(bkp) == -1)
		return (1);
	if (cmd->redirs && setup_redirections(cmd->redirs) < 0)
	{
		restore_fds(bkp);
		return (1);
	}
	ret = execute_builtin(cmd, shell);
	restore_fds(bkp);
	return (ret);
}

int	execute_simple_command(t_cmd *cmd, t_shell *shell)
{
	char	**orig_args;
	int		i;
	int		ret;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	i = process_all_assignments(cmd->args, shell);
	while (cmd->args[i] && cmd->args[i][0] == '\0')
		i++;
	if (!cmd->args[i])
		return (0);
	orig_args = cmd->args;
	cmd->args = &cmd->args[i];
	if (is_builtin(cmd->args[0]))
		ret = exec_builtin_wrapper(cmd, shell);
	else
		ret = execute_external_cmd(cmd->args, cmd, shell);
	cmd->args = orig_args;
	return (ret);
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
