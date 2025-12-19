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

t_cmd	*main_loop_handle(t_shell *shell)
{
	t_list	*tokens;
	t_cmd	*cmds;

	tokens = lexer(shell->input);
	if (!tokens)
	{
		free(shell->input);
		shell->input = NULL;
		return (NULL);
	}
	cmds = parser(tokens);
	tokens_list_clear(&tokens);
	if (!cmds)
	{
		free(shell->input);
		shell->input = NULL;
		return (NULL);
	}
	return (cmds);
}

void	main_loop(t_shell *shell)
{
	t_cmd	*cmds;

	while (1)
	{
		display_prompt(shell);
		if (!shell->input)
			break ;
		if (shell->input && *shell->input)
		{
			cmds = main_loop_handle(shell);
			if (!cmds)
				continue ;
			expander(cmds, shell);
			executor(cmds, shell);
			free_commands(cmds);
			dup2(shell->stdin_backup, STDIN_FILENO);
			dup2(shell->stdout_backup, STDOUT_FILENO);
		}
		if (shell->input)
			free(shell->input);
		shell->input = NULL;
	}
	printf("exit\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	setup_signals();
	shell = shell_init(envp);
	main_loop(shell);
	rl_clear_history();
	free_env(shell->env);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	free(shell);
	return (0);
}
