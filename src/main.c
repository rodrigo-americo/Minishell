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
    t_token	*tokens;
    t_cmd	*cmds;

    while (1)
    {
        display_prompt(shell); // Lê a entrada (e aloca shell->input)
        
        if (!shell->input) // Trata EOF (Ctrl+D)
            break ; 

        if (shell->input && *shell->input) // Garante que a linha não está vazia
        {
            // 1. Lexer: Quebra em tokens
            tokens = lexer(shell->input);
            free(shell->input); // Libera o que foi lido pelo readline

			if (!tokens)
				continue ; 
            // 2. Parser (Próxima Fase)
			cmds = parser(tokens);
			if (!cmds)
				continue ;
            // ... etc.

            // if (cmds)
            // {
            //     // 3. Executor
            //     // execute_pipeline(cmds, shell);
            //     // free_commands(cmds);
            // }
        }
        else
            free(shell->input); // Libera se for uma linha vazia (apenas enter)
    }
    printf("exit\n"); // Mensagem de saída para Ctrl+D
}

int main(void)
{
	t_shell				*shell;

	setup_signals();
	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		perror(ERR_MALLOC);
		exit(1);
	}
	main_loop(shell);
	return (0);
}