/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static pid_t	fork_pipe_left(int *fd, t_ast_node *node, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), -1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exit(executor(node->left, shell));
	}
	return (pid);
}

static pid_t	fork_pipe_right(int *fd, t_ast_node *node, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), -1);
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exit(executor(node->right, shell));
	}
	return (pid);
}

int	execute_pipe(t_ast_node *node, t_shell *shell)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(fd) == -1)
		return (perror("minishell: pipe"), 1);
	pid_left = fork_pipe_left(fd, node, shell);
	if (pid_left == -1)
		return (close(fd[0]), close(fd[1]), 1);
	pid_right = fork_pipe_right(fd, node, shell);
	if (pid_right == -1)
		return (close(fd[0]), close(fd[1]), 1);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	return (get_exit_status(status));
}

int	execute_subshell(t_ast_node *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		exit(executor(node->left, shell));
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}
