/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

int	exec_builtin_with_redir(char **args, t_redir *redirs, t_shell *shell)
{
	int	bkp[3];
	int	status;

	if (backup_fds(bkp) == -1)
		return (1);
	if (setup_redirections(redirs) == -1)
	{
		restore_fds(bkp);
		return (1);
	}
	status = execute_builtin(args, shell);
	restore_fds(bkp);
	return (status);
}

int	exec_external(char **args, t_redir *redirs, t_shell *shell)
{
	char	*path;
	char	**envp;
	pid_t	pid;
	int		status;

	path = find_command(args[0], shell);
	if (!path)
		return (handle_command_not_found(args[0]));
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), free(path), 1);
	if (pid == 0)
	{
		if (redirs && setup_redirections(redirs) < 0)
			exit(1);
		envp = env_to_array(shell->env);
		execve(path, args, envp);
		perror("minishell");
		exit(126);
	}
	free(path);
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}

int	execute_command(t_ast_node *node, t_shell *shell)
{
	if (!node->args || !node->args[0])
		return (0);
	if (is_builtin(node->args[0]))
		return (exec_builtin_with_redir(node->args, node->redirs, shell));
	return (exec_external(node->args, node->redirs, shell));
}
