/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:02:03 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 01:24:33 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "defines.h"
# include "types.h"
# include "signals.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "builtins.h"
# include "env.h"
# include "utils.h"

#endif
