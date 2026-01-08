/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/20 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_BONUS_H
# define LEXER_BONUS_H

# include "types_bonus.h"

t_list	*lexer(char *input);
int		is_operator_start(char c);
int		is_redir_prefix(char *input);
void	init_operators_bonus(t_operator operators[12]);
t_list	*extract_operator_token(char **input);
t_token	*token_new(const char *value, int type);
void	token_del(void *p);
t_list	*token_node_new(char *value, int type);
void	tokens_list_add_back(t_list **head, t_list *new_node);
void	tokens_list_clear(t_list **tokens);

#endif