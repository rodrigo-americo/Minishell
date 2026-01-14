/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 12:30:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_cmd *cmd, t_cmd *cmds, t_shell *shell, t_exec *ex)
{
	shell->is_main = 0;
	conf_child_pipes(ex);
	if (cmd->redirs && setup_redirections(cmd->redirs) < 0)
		child_exit(cmds, shell, NULL, 1);
	close_heredocs(cmds);
	if (!cmd->args || !cmd->args[0])
		child_exit(cmds, shell, NULL, 0);
	if (is_builtin(cmd->args[0]))
	{
		execute_child_builtin(cmd, cmds, shell);
		return ;
	}
	execute_external_cmd_child(cmd, cmds, shell,
		find_command(cmd->args[0], shell));
}

void	parent_process(t_exec *ex)
{
	if (ex->prev_fd != -1)
		close(ex->prev_fd);
	if (ex->has_next)
	{
		close(ex->fd[1]);
		ex->prev_fd = ex->fd[0];
	}
	else
		ex->prev_fd = -1;
}

int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	t_exec	ex;
	t_cmd	*curr;

	ex.prev_fd = -1;
	ex.last_pid = -1;
	setup_signals_executing();
	curr = cmds;
	while (curr)
	{
		if (setup_pipe(&ex, curr) == -1)
			return (1);
		if (fork_and_exec(curr, cmds, shell, &ex) == -1)
			return (1);
		curr = curr->next;
	}
	return (close_heredocs(cmds), wait_all(&ex));
}
