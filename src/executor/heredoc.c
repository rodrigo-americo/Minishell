/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:05:49 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/19 01:32:57 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	pre_process_heredocs(t_cmd *cmds, t_shell *shell)
// {
// 	t_cmd	*curr_cmd;
// 	t_redir	*curr_redir;

// 	curr_cmd = cmds;
// 	while (curr_cmd)
// 	{
// 		curr_redir = curr_cmd->redirs;
// 		while (curr_redir)
// 		{
// 			if (curr_redir->type == REDIR_HEREDOC && curr_redir->file)
// 				curr_redir->hrdc_fd = handle_heredoc(curr_redir->file, shell);
// 			curr_redir = curr_redir->next;
// 		}
// 		curr_cmd = curr_cmd->next;
// 	}
// }

// int	handle_heredoc(char *delimiter, t_shell *shell)
// {
// 	int		fd[2];
// 	char	*line;
// 	char	*exp_line;

// 	if (pipe(fd) == -1)
// 		return (-1);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		exp_line = process_string_content(line, shell);
// 		ft_putendl_fd(exp_line, fd[1]);
// 		free(line);
// 		free(exp_line);
// 	}
// 	close(fd[1]);
// 	return (fd[0]);
// }

void	close_heredocs(t_cmd *cmds)
{
	t_cmd	*curr_cmd;
	t_redir	*curr_redir;

	curr_cmd = cmds;
	while (curr_cmd)
	{
		curr_redir = curr_cmd->redirs;
		while (curr_redir)
		{
			if (curr_redir->type == REDIR_HEREDOC && curr_redir->hrdc_fd != -1)
			{
				close(curr_redir->hrdc_fd);
				curr_redir->hrdc_fd = -1;
			}
			curr_redir = curr_redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
}