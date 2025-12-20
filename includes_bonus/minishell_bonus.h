/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:02:03 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/20 10:06:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

/* ************************************************************************** */
/*                         STANDARD LIBRARY INCLUDES                          */
/* ************************************************************************** */

/* Standard Library */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

/* File Operations */
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>

/* Process Control */
# include <sys/wait.h>

/* Signal Handling */
# include <signal.h>

/* Terminal Control */
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>

/* Readline Library */
# include <readline/readline.h>
# include <readline/history.h>

/* ************************************************************************** */
/*                         PROJECT INCLUDES                                   */
/* ************************************************************************** */

/* Libft */
# include "libft.h"

/* Project Headers */
# include "defines_bonus.h"
# include "types_bonus.h"
# include "signals_bonus.h"
# include "lexer_bonus.h"
# include "parser_bonus.h"
# include "expander_bonus.h"
# include "executor_bonus.h"
# include "builtins_bonus.h"
# include "env_bonus.h"
# include "utils_bonus.h"

#endif
