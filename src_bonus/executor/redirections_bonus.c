/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 12:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	get_open_flags(int type)
{
	if (type == REDIR_IN)
		return (O_RDONLY);
	if (type == REDIR_OUT || type == TOKEN_REDIR_STDERR_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	return (O_WRONLY | O_CREAT | O_APPEND);
}

static int	get_target_fd(int type)
{
	if (type == REDIR_IN)
		return (STDIN_FILENO);
	if (type == TOKEN_REDIR_STDERR_OUT || type == TOKEN_REDIR_STDERR_APPEND)
		return (STDERR_FILENO);
	return (STDOUT_FILENO);
}

static int	handle_file_redir(t_redir *redir)
{
	int	fd;
	int	target_fd;
	int	flags;

	flags = get_open_flags(redir->type);
	fd = open(redir->file, flags, 0644);
	if (fd < 0)
		return (perror(redir->file), -1);
	target_fd = get_target_fd(redir->type);
	if (dup2(fd, target_fd) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (perror("minishell: pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (close(fd[0]), perror("minishell: dup2"), -1);
	close(fd[0]);
	return (0);
}

int	setup_redirections(t_redir *redirs)
{
	t_redir	*curr;

	curr = redirs;
	while (curr)
	{
		if (curr->type == REDIR_HEREDOC)
		{
			if (handle_heredoc(curr->file) < 0)
				return (-1);
		}
		else
		{
			if (handle_file_redir(curr) < 0)
				return (-1);
		}
		curr = curr->next;
	}
	return (0);
}
