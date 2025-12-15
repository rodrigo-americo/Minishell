/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:47:32 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/02 14:40:51 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(t_shell *shell)
{
	char	*prompt;

	prompt = "minishell> ";
	shell->input = readline(prompt);
	if (shell->input && *shell->input)
		add_history(shell->input);
}

/* src/main.c */
void main_loop(t_shell *shell)
{
    t_list  *tokens;
    t_cmd	*cmds;

    while (1)
    {
        display_prompt(shell);
        if (!shell->input)
            break ;
        if (shell->input && *shell->input)
        {
            tokens = lexer(shell->input);
			if (!tokens)
			{
				free(shell->input);
				shell->input = NULL;
				continue ;
			}
    		cmds = parser(tokens);
			tokens_list_clear(&tokens);
			if (!cmds)
			{
				free(shell->input);
				shell->input = NULL;
				continue ;
			}
			expander(cmds, shell);
			executor(cmds, shell);
			free_commands(cmds);
        }
        if (shell->input)
			free(shell->input);
		shell->input = NULL;
    }
    printf("exit\n"); // Mensagem de saída para Ctrl+D
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	setup_signals();
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
	main_loop(shell);
	free_env(shell->env);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	free(shell);
	return (0);
}