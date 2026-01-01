/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/23 16:44:28 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

/* Error Handling */
void	error_exit(char *msg);
void	print_error(char *cmd, char *msg);

/* String Utilities */
char	*skip_whitespace(char *input);
char	*ft_strjoin_char(char *s, char c);

/* Array Utilities */
void	free_array(char **arr);
char	**ft_add_to_array(char **arr, char *new_str);

/* Free expander*/
void	free_expander(char *val, char *key);

/* Character Checks */
int		is_separator(char c);

/* Shell Initialization */
t_shell	*shell_init(char **envp);
void	init_shell(t_shell *shell, char **envp);
void	cleanup_shell(t_shell *shell);

/* Line Continuation */
int		skip_quotes(char *str, int i);
int		ends_with_backslash(char *str);
int		ends_with_pipe(char *str);
int		needs_continuation(char *line);
char	*read_with_continuation(char *prompt);

/* Line Joining */
char	*join_lines(char *acc, char *line);
char	*join_lines_no_replace(char *acc, char *line);

#endif
