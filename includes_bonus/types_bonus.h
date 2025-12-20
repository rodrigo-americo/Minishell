/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/20 10:08:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

# include "libft.h"

/* ************************************************************************** */
/*                              ENUMERATIONS                                  */
/* ************************************************************************** */

/* Redirection Types */
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

/* ************************************************************************** */
/*                              STRUCTURES                                    */
/* ************************************************************************** */

/* Token Structure */
typedef struct s_token
{
	char	*value;
	int		type;
}	t_token;

/* Operator Lookup Structure */
typedef struct s_operator
{
	char	*symbol;
	int		type;
	int		len;
}	t_operator;

/* Redirection Structure */
typedef struct s_redir
{
	int				type;
	char			*file;
	int				hrdc_fd;
	struct s_redir	*next;
}	t_redir;

/* Command Structure */
typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

/* Environment Variable Structure */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* Main Shell Structure */
typedef struct s_shell
{
	char	*input;
	t_list	*tokens;
	t_cmd	*cmds;
	t_env	*env;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;
}	t_shell;

/* Execution Context Structure */
typedef struct s_exec
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;
	int		status;
}	t_exec;

/* ************************************************************************** */
/*                         BONUS: AST STRUCTURES                              */
/* ************************************************************************** */

/* AST Node Types */
typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}	t_node_type;

/* AST Node Structure */
typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	t_redir				*redirs;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

/* Shell Structure with AST (Bonus) */
typedef struct s_shell_bonus
{
	char		*input;
	t_list		*tokens;
	t_ast_node	*ast;
	t_env		*env;
	int			exit_status;
	int			stdin_backup;
	int			stdout_backup;
}	t_shell_bonus;

#endif
