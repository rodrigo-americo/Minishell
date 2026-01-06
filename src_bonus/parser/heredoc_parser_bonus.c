/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/02 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"


static char	*remove_delimiter_quotes(char *str, int *is_quoted)
{
	int	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '\"' && str[len - 1] == '\"')))
	{
		*is_quoted = 1;
		return (ft_substr(str, 1, len - 2));
	}
	*is_quoted = 0;
	return (ft_strdup(str));
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

static int	read_heredoc_lines(int fd, char *delimiter, t_shell *shell,
		int is_quoted)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_heredoc_line(line, shell, is_quoted);
		free(line);
		if (!expanded || write_heredoc_line(fd, expanded) == -1)
		{
			free(expanded);
			return (-1);
		}
		free(expanded);
	}
	return (0);
}

int	process_heredoc_at_parse_time(t_redir *redir, t_shell *shell)
{
	int		fd[2];
	char	*delimiter;

	delimiter = remove_delimiter_quotes(redir->file, &redir->is_quoted);
	if (!delimiter || pipe(fd) == -1)
		return (free(delimiter), -1);
	if (read_heredoc_lines(fd[1], delimiter, shell, redir->is_quoted) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		free(delimiter);
		return (-1);
	}
	close(fd[1]);
	redir->hrdc_fd = fd[0];
	free(delimiter);
	return (0);
}
