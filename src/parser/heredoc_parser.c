/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/24 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <errno.h>

static void	signal_handler_heredoc(int signum)
{
	g_signal_received = signum;
	if (signum == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

static void	setup_signals_heredoc(struct sigaction *old_int,
	struct sigaction *old_quit)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = signal_handler_heredoc;
	sigaction(SIGINT, &sa_int, old_int);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, old_quit);
}

static void	restore_signals_heredoc(struct sigaction *old_int,
	struct sigaction *old_quit)
{
	sigaction(SIGINT, old_int, NULL);
	sigaction(SIGQUIT, old_quit, NULL);
}

static char	*remove_delimiter_quotes(char *str, int *is_quoted)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	*is_quoted = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			*is_quoted = 1;
			quote = str[i++];
			while (str[i] && str[i] != quote)
				result[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static char	*expand_heredoc_line(char *line, t_shell *shell, int is_quoted)
{
	if (is_quoted)
		return (ft_strdup(line));
	return (process_string_content(line, shell));
}

static int	write_heredoc_line(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		return (-1);
	if (write(fd, "\n", 1) == -1)
		return (-1);
	return (0);
}

static char	*read_line_heredoc(void)
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

static int	read_heredoc_loop(int *fd, char *delim, t_redir *redir, t_shell *sh)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = read_line_heredoc();
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
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			return (0);
		}
		expanded = expand_heredoc_line(line, sh, redir->is_quoted);
		free(line);
		if (!expanded || write_heredoc_line(fd[1], expanded) == -1)
		{
			free(expanded);
			return (-1);
		}
		free(expanded);
	}
}

int	process_heredoc_at_parse_time(t_redir *redir, t_shell *shell)
{
	int					fd[2];
	char				*delimiter;
	struct sigaction	old_int;
	struct sigaction	old_quit;

	delimiter = remove_delimiter_quotes(redir->file, &redir->is_quoted);
	if (!delimiter || pipe(fd) == -1)
		return (free(delimiter), -1);
	setup_signals_heredoc(&old_int, &old_quit);
	if (read_heredoc_loop(fd, delimiter, redir, shell) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		free(delimiter);
		restore_signals_heredoc(&old_int, &old_quit);
		return (-1);
	}
	restore_signals_heredoc(&old_int, &old_quit);
	close(fd[1]);
	redir->hrdc_fd = fd[0];
	free(delimiter);
	return (0);
}
