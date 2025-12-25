/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/18 00:00:00 by rgregori         ###   ########.fr       */
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

/* Heredoc Processing */
int		process_heredoc_at_parse_time(t_redir *redir, t_shell *shell);

/* Command Management */
void	free_cmd(t_cmd *cmd);
void	free_commands(t_cmd *cmds);

#endif
