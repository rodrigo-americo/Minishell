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

/* AST Node Expansion */
void	expander(t_ast_node *node, t_shell *shell);

/* String Processing */
char	*process_string_content(char *original_str, t_shell *shell);
int		ft_handle_expansion(char **new_str,
			char *str_at_dollar, t_shell *shell);

/* Expander Value Utilities */
char	*get_pid_str(void);
int		get_var_len(char *str);
char	*get_expanded_value(char *str, t_shell *shell, int *len);

/* Wildcard Match Utilities */
int		has_wildcard(char *str);
int		match_pattern(char *pattern, char *str);

/* Word Splitting */
void	word_splitting_ast(t_ast_node *node);
char	**expand_wildcards(char **args);
void	restore_spaces(char **args);
void	restore_spaces_in_redirs(t_redir *redirs);

#endif
