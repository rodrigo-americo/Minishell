/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:45:55 by ccavalca          #+#    #+#             */
/*   Updated: 2026/01/14 16:52:23 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

char	*expand_heredoc_line(char *line, t_shell *shell, int is_quoted)
{
	if (is_quoted)
		return (ft_strdup(line));
	return (process_string_content(line, shell));
}

int	write_heredoc_line(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		return (-1);
	if (write(fd, "\n", 1) == -1)
		return (-1);
	return (0);
}

char	*read_line_heredoc(void)
{
	char	buffer[1024];
	char	*line;
	ssize_t	n;

	write(STDOUT_FILENO, "> ", 2);
	n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	if (n == -1)
	{
		if (errno == EINTR)
			return (NULL);
		perror("read");
		return (NULL);
	}
	if (n == 0)
		return (NULL);
	if (buffer[n - 1] == '\n')
		n--;
	buffer[n] = '\0';
	line = ft_strdup(buffer);
	return (line);
}

int	check_line_signal(char *line)
{
	if (!line)
	{
		if (g_signal_received == SIGINT)
			return (-1);
		return (0);
	}
	if (g_signal_received == SIGINT)
	{
		free(line);
		return (-1);
	}
	return (1);
}

int	process_heredoc_line(int fd, char *line, t_redir *redir, t_shell *sh)
{
	char	*expanded;

	expanded = expand_heredoc_line(line, sh, redir->is_quoted);
	if (!expanded || write_heredoc_line(fd, expanded) == -1)
	{
		free(expanded);
		return (-1);
	}
	free(expanded);
	return (0);
}
