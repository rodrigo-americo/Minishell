/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/14 16:51:38 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

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

static int	read_heredoc_loop(int *fd, char *delim, t_redir *redir, t_shell *sh)
{
	char	*line;
	int		status;

	while (1)
	{
		line = read_line_heredoc();
		status = check_line_signal(line);
		if (status <= 0)
			return (status);
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			return (0);
		}
		if (process_heredoc_line(fd[1], line, redir, sh) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
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
