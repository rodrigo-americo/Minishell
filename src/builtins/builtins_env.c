/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:44:37 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/18 11:25:25 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_export_arg(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	if (is_valid_identifier(key))
		set_env_value(key, value, &shell->env);
	else
		print_error("export", "not a valid identifier");
	free(key);
	free(value);
}

int	builtin_export(char **args, t_shell *shell)
{
	int	i;

	if (!args[1])
	{
		list_sorted_env(shell->env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		process_export_arg(args[i], shell);
		i++;
	}
    return (0);
}

int	builtin_unset(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	if (!args[i])
		return (0);
	while (args[i])
	{
	if (is_valid_identifier(args[i]))
		{
			unset_env_value(args[i], &shell->env);
		}
		else
		{
			print_error("unset", "not a valid identifier");        }
		i++;
	}
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

int	builtin_exit(char **args, t_shell *shell)
{
	int i;

	ft_putendl_fd("exit", 2);
	if (args[1])
	{
		i = (args[1][0] == '-' || args[1][0] == '+') ? 1 : 0;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				print_error("exit", "numeric argument required");
				exit(255);
			}
			i++;
		}
		if (args[2])
		{
			print_error("exit", "too many arguments");
			return (1);
		}
		exit(ft_atoi(args[1]));
	}
	exit(shell->exit_status);
}
