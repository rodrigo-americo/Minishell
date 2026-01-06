/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/18 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BONUS_H
#  define PARSER_BONUS_H

#  include "types_bonus.h"

/* AST Parser Main Function */
t_ast_node	*parser(t_list *tokens, t_shell *shell);

/* AST Helper Functions */
void		free_ast(t_ast_node *node);
void		print_ast(t_ast_node *node, int depth);
t_ast_node	*create_ast_node(t_node_type type);
t_ast_node	*create_binary_node(t_node_type type, t_ast_node *left,
				t_ast_node *right);

/* AST Parsing Functions */
t_ast_node	*parse_or(t_list **tokens, t_shell *shell);
t_ast_node	*parse_and(t_list **tokens, t_shell *shell);
t_ast_node	*parse_pipe(t_list **tokens, t_shell *shell);
t_ast_node	*parse_primary(t_list **tokens, t_shell *shell);
t_ast_node	*parse_command(t_list **tokens, t_shell *shell);
t_ast_node	*parse_subshell(t_list **tokens, t_shell *shell);

/* Syntax Checking */
int			check_syntax(t_list *tokens);

/* Redirection Management */
t_redir		*create_redir(char *file_name, t_redir_type type);
t_redir		*parse_redirection(t_list **tokens, t_shell *shell);
void		add_redir_to_end(t_redir **head, t_redir *new_redir);
int			process_heredoc_at_parse_time(t_redir *redir, t_shell *shell);

/* Token Management */
t_token		*peek_token(t_list *tokens);
t_token		*consume_token(t_list **tokens);
int			is_operator(t_token *tok);

#endif
