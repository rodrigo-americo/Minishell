/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:47:32 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal_status(t_shell *shell)
{
	if (g_signal_received == SIGINT)
	{
		g_signal_received = 0;
		shell->exit_status = 130;
	}
}

static int	get_input(t_shell *shell)
{
	shell->input = read_with_continuation("minishell> ");
	if (!shell->input)
		return (0);
	if (*shell->input)
		add_history(shell->input);
	return (1);
}

static t_cmd	*parse_input(t_shell *shell)
{
	t_list	*tokens;
	t_cmd	*cmds;

	tokens = lexer(shell->input);
	if (!tokens)
		return (NULL);
	cmds = parser(tokens, shell);
	tokens_list_clear(&tokens);
	return (cmds);
}

void	main_loop(t_shell *shell)
{
	while (1)
	{
		handle_signal_status(shell);
		if (!get_input(shell))
			break ;
		if (*shell->input)
		{
			shell->cmds = parse_input(shell);
			if (shell->cmds)
			{
				expander(shell->cmds, shell);
				executor(shell->cmds, shell);
				free_commands(shell->cmds);
				shell->cmds = NULL;
			}
			else
				shell->exit_status = 2;
		}
		free(shell->input);
		shell->input = NULL;
	}
	ft_putendl_fd("exit", 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		exit_code;

	(void)argc;
	(void)argv;
	setup_signals();
	shell = shell_init(envp);
	main_loop(shell);
	exit_code = shell->exit_status;
	rl_clear_history();
	free_env(shell->env);
	free(shell);
	return (exit_code);
}
