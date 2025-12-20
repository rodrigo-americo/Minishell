/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/20 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_BONUS_H
# define AST_BONUS_H

# include "types_bonus.h"

t_ast_node	*create_ast_node(t_node_type type);
t_ast_node	*create_cmd_node(char **args, t_redir *redirs);
t_ast_node	*create_operator_node(t_node_type type, t_ast_node *left,
				t_ast_node *right);
t_ast_node	*create_subshell_node(t_ast_node *child, t_redir *redirs);
void		free_ast(t_ast_node *node);
void		free_ast_preserve_data(t_ast_node *node);
void		print_ast(t_ast_node *node, int depth);
void		print_ast_inline(t_ast_node *node);
int			ast_is_operator(t_ast_node *node);
int			ast_is_logical_operator(t_ast_node *node);
int			ast_count_commands(t_ast_node *node);
int			ast_get_depth(t_ast_node *node);
int			ast_has_redirs(t_ast_node *node);
void		ast_copy_node_data(t_ast_node *dest, t_ast_node *src);

#endif