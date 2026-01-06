/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/18 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
#  define UTILS_BONUS_H

#  include "types_bonus.h"

/* Error Handling */
void	error_exit(char *msg);
void	print_error(char *cmd, char *msg);

/* String Utilities */
char	*skip_whitespace(char *input);
char	*ft_strjoin_char(char *s, char c);

/* Array Utilities */
void	free_array(char **arr);
char	**ft_add_to_array(char **arr, char *new_str);

/* Character Checks */
int		is_separator(char c);

/* Shell Initialization */
t_shell	*shell_init(char **envp);
void	init_shell(t_shell *shell, char **envp);
void	cleanup_shell(t_shell *shell);

/* Line Continuation */
char	*read_with_continuation(char *prompt);
int		needs_continuation(char *line);
int		ends_with_backslash(char *str);
int		ends_with_pipe(char *str);

/* Line Joining */
char	*join_lines(char *acc, char *line);
char	*join_lines_no_replace(char *acc, char *line);

/* Token Management */
void	tokens_list_add_back(t_list **head, t_list *new_node);
void	tokens_list_clear(t_list **tokens);
int		skip_quotes(char *str, int i);

/* Assignment Detection */
int		is_assignment(char *str);

#endif
