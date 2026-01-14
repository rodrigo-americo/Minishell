/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_and_convert(char *str, int *exit_code)
{
	int			i;
	long long	num;
	int			sign;

	init_validation(str, &i, &sign);
	num = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (check_overflow(num, str[i]))
			return (0);
		num = num * 10 + (str[i++] - '0');
	}
	*exit_code = (int)((num * sign) % EXIT_CODE_MAX);
	if (*exit_code < 0)
		*exit_code += EXIT_CODE_MAX;
	return (1);
}

static void	cleanup_and_exit(int code)
{
	int	fd;

	fd = 3;
	while (fd < MAX_FD)
		close(fd++);
	exit(code);
}

static void	handle_invalid_arg(pid_t pid, pid_t main_pid)
{
	if (pid == main_pid)
		ft_putendl_fd("exit", 2);
	ft_putstr_fd("exit :  numeric argument required\n", 2);
	cleanup_and_exit(2);
}

int	builtin_exit(char **args, t_shell *shell)
{
	int		exit_code;
	pid_t	pid;

	pid = getpid();
	if (!args[1])
	{
		if (pid == shell->main_pid)
			ft_putendl_fd("exit", 2);
		cleanup_and_exit(shell->exit_status);
	}
	if (!args[1][0] || (args[1][0] == '-' && !args[1][1])
		|| (args[1][0] == '+' && !args[1][1]))
		handle_invalid_arg(pid, shell->main_pid);
	if (!validate_and_convert(args[1], &exit_code))
		handle_invalid_arg(pid, shell->main_pid);
	if (args[2])
	{
		if (pid == shell->main_pid)
			ft_putendl_fd("exit", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		cleanup_and_exit(1);
	}
	cleanup_and_exit(exit_code);
	return (0);
}
