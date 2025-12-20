/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_bonus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 11:03:47 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_BONUS_H
#  define EXPANDER_BONUS_H

#  include "types_bonus.h"

/* Main Expansion */
void	expander(t_cmd *cmds, t_shell *shell);

/* String Processing */
char	*process_string_content(char *original_str, t_shell *shell);
int		ft_handle_expansion(char **new_str,
			char *str_at_dollar, t_shell *shell);

/* Word Splitting */
void	word_splitting(t_cmd *cmd);

/* ************************************************************************** */
/*                         BONUS: AST EXPANDER                                */
/* ************************************************************************** */

/* AST Node Expansion */
void	expand_ast_node(t_ast_node *node, t_shell_bonus *shell);

#endif
