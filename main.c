/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:47:32 by rgregori          #+#    #+#             */
/*   Updated: 2025/10/24 13:52:05 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void display_prompt(t_shell *shell)
{
	char *propt;
	
	propt = "minishell> ";
	shell->input = readline(propt);
	if (*shell->input)
		add_history(shell->input);
	free(shell->input);	
}

void main_loop(t_shell *shell)
{
	while (1)
	{
		display_prompt(shell);
	}
	
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