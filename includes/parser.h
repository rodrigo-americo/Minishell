/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/14 16:52:07 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

/* Parser Main Function */
t_cmd	*parser(t_list *tokens, t_shell *shell);

/* Syntax Checking */
int		check_syntax(t_list *node, t_cmd *head);

/* Redirection Management */
t_redir	*create_redir(char *file_name, t_redir_type type);
void	add_redir_to_end(t_redir **head, t_redir *new_redir);
int		process_redir(t_cmd *cmd, t_list **current, t_shell *shell);

/* Heredoc Processing */
int		process_heredoc_at_parse_time(t_redir *redir, t_shell *shell);

/* Heredoc Delimiter */
char	*remove_delimiter_quotes(char *str, int *is_quoted);

/* Heredoc Utils */
char	*expand_heredoc_line(char *line, t_shell *shell, int is_quoted);
int		write_heredoc_line(int fd, char *line);
char	*read_line_heredoc(void);
int		check_line_signal(char *line);
int		process_heredoc_line(int fd, char *line, t_redir *redir,
			t_shell *sh);

/* Command Management */
void	free_cmd(t_cmd *cmd);
void	free_commands(t_cmd *cmds);

/* Array Utilities */
char	**copy_array(char **arr);

#endif
