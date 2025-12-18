/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:44:37 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/17 17:33:51 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_export(char **args, t_shell *shell)
{
	(void)args;
	(void)shell;
	return (0);
}

int		builtin_unset(char **args, t_shell *shell)
{
	(void)args;
	(void)shell;
	return (0);
}

int		builtin_env(t_shell *shell)
{
	t_env	*tmp;

	if (!shell || !shell->env)
		return (1);
	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int		builtin_exit(char **args, t_shell *shell)
{
	(void)args;
	(void)shell;
	return (0);
}
