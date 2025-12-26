/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:44:37 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/19 10:15:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_export_arg(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;
	int		result;

	key = NULL;
	value = NULL;
	extract_key_value(arg, &key, &value);
	if (!validate_export_key(key, value))
		return (0);
	if (is_valid_identifier(key))
	{
		set_env_value(key, value, &shell->env);
		result = 1;
	}
	else
	{
		print_error("export", "not a valid identifier");
		result = 0;
	}
	free(key);
	if (value)
		free(value);
	return (result);
}

int	builtin_export(char **args, t_shell *shell)
{
	int	i;
	int	status;

	if (!args[1])
	{
		list_sorted_env(shell->env);
		return (0);
	}
	status = 0;
	i = 1;
	while (args[i])
	{
		if (!process_export_arg(args[i], shell))
			status = 1;
		i++;
	}
	return (status);
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
			unset_env_value(args[i], &shell->env);
		else
			print_error("unset", "not a valid identifier");
		i++;
	}
	return (0);
}

int	builtin_env(t_shell *shell)
{
	t_env	*tmp;

	if (!shell || !shell->env)
		return (0);
	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

static int	validate_and_convert(char *str, int *exit_code)
{
	int			i;
	long long	num;
	int			sign;

	i = 0;
	sign = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign = -1;
		i++;
	}
	num = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		num = num * 10 + (str[i++] - '0');
		if (num > 9223372036854775807LL / 10)
			return (0);
	}
	*exit_code = (int)((num * sign) % 256);
	if (*exit_code < 0)
		*exit_code += 256;
	return (1);
}

static void	cleanup_and_exit(int code)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
		close(fd++);
	exit(code);
}

int	builtin_exit(char **args, t_shell *shell)
{
	int	exit_code;

	ft_putendl_fd("exit", 2);
	if (!args[1])
		cleanup_and_exit(shell->exit_status);
	if (!args[1][0] || (args[1][0] == '-' && !args[1][1])
		|| (args[1][0] == '+' && !args[1][1]))
	{
		ft_putstr_fd("exit :  numeric argument required\n", 2);
		cleanup_and_exit(2);
	}
	if (!validate_and_convert(args[1], &exit_code))
	{
		ft_putstr_fd("exit :  numeric argument required\n", 2);
		cleanup_and_exit(2);
	}
	if (args[2])
		return (print_error("exit", "too many arguments"), 1);
	cleanup_and_exit(exit_code);
	return (0);
}
