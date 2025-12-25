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

/*
** Remove quotes from delimiter and sets is_quoted flag
** Examples:
**   'eof'  -> eof (is_quoted=1)
**   "eof"  -> eof (is_quoted=1)
**   eof    -> eof (is_quoted=0)
*/
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

/*
** Expand variables in heredoc line if is_quoted == 0
** Reuses existing expander logic
*/
static char	*expand_heredoc_line(char *line, t_shell *shell, int is_quoted)
{
	if (is_quoted)
		return (ft_strdup(line));
	return (process_string_content(line, shell));
}

/*
** Write line to heredoc pipe
** Returns 0 on success, -1 on error
*/
static int	write_heredoc_line(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		return (-1);
	if (write(fd, "\n", 1) == -1)
		return (-1);
	return (0);
}

/*
** Process heredoc at parse time
** Reads lines from terminal, writes to pipe, saves fd
*/
int	process_heredoc_at_parse_time(t_redir *redir, t_shell *shell)
{
	int		fd[2];
	char	*line;
	char	*delimiter;
	char	*expanded;

	delimiter = remove_delimiter_quotes(redir->file, &redir->is_quoted);
	if (!delimiter || pipe(fd) == -1)
		return (free(delimiter), -1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_heredoc_line(line, shell, redir->is_quoted);
		free(line);
		if (!expanded || write_heredoc_line(fd[1], expanded) == -1)
		{
			free(expanded);
			return (close(fd[0]), close(fd[1]), free(delimiter), -1);
		}
		free(expanded);
	}
	close(fd[1]);
	redir->hrdc_fd = fd[0];
	free(delimiter);
	return (0);
}
