/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/20 10:08:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_BONUS_H
# define DEFINES_BONUS_H

/* ************************************************************************** */
/*                              EXIT STATUS                                   */
/* ************************************************************************** */

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

/* ************************************************************************** */
/*                              BUFFER SIZES                                  */
/* ************************************************************************** */

# define BUFFER_SIZE 1024
# define PATH_MAX_LEN 4096

/* ************************************************************************** */
/*                              TOKEN TYPES                                   */
/* ************************************************************************** */

# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIR_IN 3
# define TOKEN_REDIR_OUT 4
# define TOKEN_REDIR_APPEND 5
# define TOKEN_REDIR_HEREDOC 6

/* ************************************************************************** */
/*                         BONUS TOKEN TYPES                                  */
/* ************************************************************************** */

# define TOKEN_AND 7
# define TOKEN_OR 8
# define TOKEN_LPAREN 9
# define TOKEN_RPAREN 10

/* ************************************************************************** */
/*                              ERROR MESSAGES                                */
/* ************************************************************************** */

# define ERR_MALLOC "minishell: memory allocation failed\n"
# define ERR_FORK "minishell: fork failed\n"
# define ERR_PIPE "minishell: pipe failed\n"
# define ERR_SYNTAX "minishell: syntax error\n"
# define ERR_CMD_NOT_FOUND "minishell: command not found: %s\n"

#endif
