/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/16 11:05:40 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_operator(t_operator *op, char *symbol, int type, int len)
{
	op->symbol = symbol;
	op->type = type;
	op->len = len;
}

void	init_operators(t_operator operators[6])
{
	init_operator(&operators[0], ">>", TOKEN_REDIR_APPEND, 2);
	init_operator(&operators[1], "<<", TOKEN_REDIR_HEREDOC, 2);
	init_operator(&operators[2], ">", TOKEN_REDIR_OUT, 1);
	init_operator(&operators[3], "<", TOKEN_REDIR_IN, 1);
	init_operator(&operators[4], "|", TOKEN_PIPE, 1);
	init_operator(&operators[5], NULL, 0, 0);
}

void	setup_signals(void)
{
	setup_signals_interactive();
}

t_shell	*shell_init(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		perror(ERR_MALLOC);
		exit(1);
	}
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->env = create_env(envp);
	shell->exit_status = 0;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	return (shell);
}
