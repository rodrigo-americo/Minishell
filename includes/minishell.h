/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:02:03 by rgregori          #+#    #+#             */
/*   Updated: 2025/11/25 15:08:45 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                              INCLUDES                                      */
/* ************************************************************************** */

/* Standard Library */
# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, exit, getenv
# include <unistd.h>     // write, access, read, close, fork, execve, 
                         // dup, dup2, pipe, getcwd, chdir, isatty, 
                         // ttyname, ttyslot
# include <string.h>     // strerror

/* File Operations */
# include <fcntl.h>      // open
# include <sys/stat.h>   // stat, lstat, fstat
# include <sys/types.h>  // types for system calls
# include <dirent.h>     // opendir, readdir, closedir

/* Process Control */
# include <sys/wait.h>   // wait, waitpid, wait3, wait4

/* Signal Handling */
# include <signal.h>     // signal, sigaction, sigemptyset, sigaddset, kill

/* Terminal Control */
# include <termios.h>    // tcsetattr, tcgetattr
# include <term.h>       // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/ioctl.h>  // ioctl

/* Readline Library */
# include <readline/readline.h>  // readline, rl_clear_history, rl_on_new_line,
                                  // rl_replace_line, rl_redisplay
# include <readline/history.h>   // add_history

/* ************************************************************************** */
/*                              DEFINES                                       */
/* ************************************************************************** */

/* Exit Status */
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

/* Buffer Sizes */
# define BUFFER_SIZE 1024
# define PATH_MAX_LEN 4096

/* Token Types */
# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIR_IN 3
# define TOKEN_REDIR_OUT 4
# define TOKEN_REDIR_APPEND 5
# define TOKEN_REDIR_HEREDOC 6

/* Error Messages */
# define ERR_MALLOC "minishell: memory allocation failed\n"
# define ERR_FORK "minishell: fork failed\n"
# define ERR_PIPE "minishell: pipe failed\n"
# define ERR_SYNTAX "minishell: syntax error\n"
# define ERR_CMD_NOT_FOUND "minishell: command not found: %s\n"

/* ************************************************************************** */
/*                              STRUCTURES                                    */
/* ************************************************************************** */

/* Token Structure */
typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

/* Redirection Structure */
typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

/* Tipos de Redirecionamento */
typedef enum e_redir_type
{
	REDIR_IN,          // <
	REDIR_OUT,         // >
	REDIR_APPEND,      // >>
	REDIR_HEREDOC      // <<
}	t_redir_type;

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
	char			*input;
	t_token			*tokens;
	t_cmd			*cmds;
	t_env			*env;
	int				exit_status;
	int				stdin_backup;
	int				stdout_backup;
}	t_shell;

/* ************************************************************************** */
/*                         FUNCTION PROTOTYPES                                */
/* ************************************************************************** */

/* Main Loop */
void	main_loop(t_shell *shell);
void	init_shell(t_shell *shell, char **envp);
void	cleanup_shell(t_shell *shell);

/* Signal Handling */
void	setup_signals(void);
void	signal_handler(int signum);

/* Lexer */
t_token	*lexer(char *input);
t_token	*create_token(char *value, int type);
void	free_tokens(t_token *tokens);

/* Parser */
t_cmd	*parser(t_token *tokens);
void	free_commands(t_cmd *cmds);

/* Expansion */
char	*expand_variables(char *str, t_shell *shell);
char	*expand_exit_status(char *str, int exit_status);

/* Executor */
void	executor(t_cmd *cmds, t_shell *shell);
void	execute_command(t_cmd *cmd, t_shell *shell);
void	execute_pipeline(t_cmd *cmds, t_shell *shell);

/* Built-ins */
int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, t_shell *shell);
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_shell *shell);
int		builtin_pwd(void);
int		builtin_export(char **args, t_shell *shell);
int		builtin_unset(char **args, t_shell *shell);
int		builtin_env(t_shell *shell);
int		builtin_exit(char **args, t_shell *shell);

/* Redirections */
int		setup_redirections(t_redir *redirs);
int		handle_heredoc(char *delimiter);

/* Path Resolution */
char	*find_command(char *cmd, t_shell *shell);
char	**get_paths(t_shell *shell);

/* Environment */
t_env	*create_env(char **envp);
char	*get_env_value(char *key, t_env *env);
void	set_env_value(char *key, char *value, t_env **env);
void	unset_env_value(char *key, t_env **env);
void	free_env(t_env *env);

/* Utils */
void	error_exit(char *msg);
void	print_error(char *cmd, char *msg);
char	**ft_split(char *str, char delimiter);
void	free_array(char **arr);
char	*skip_whitespace(char *input);
int		is_separator(char c);
char **ft_add_to_array(char **arr, char *new_str);
void add_redir_to_end(t_redir **head, t_redir *new_redir);
t_redir *create_redir(char *file_name, t_redir_type type);

#endif