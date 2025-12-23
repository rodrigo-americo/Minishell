/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:01:00 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/23 17:51:12 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_var_char(char c)
{
	int	result;

	result = 0;
	if (c >= 'a' && c <= 'z')
		result = 1;
	else if (c >= 'A' && c <= 'Z')
		result = 1;
	else if (c >= '0' && c <= '9')
		result = 1;
	else if (c == '_')
		result = 1;
	return (result);
}

static int	is_valid_var_start(char c)
{
	int	result;

	result = 0;
	if (c >= 'a' && c <= 'z')
		result = 1;
	else if (c >= 'A' && c <= 'Z')
		result = 1;
	else if (c == '_')
		result = 1;
	return (result);
}

int	is_assignment(char *str)
{
	int	i;
	int	result;

	result = 0;
	if (!str || !*str)
		return (0);
	if (!is_valid_var_start(*str))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!is_valid_var_char(str[i]))
			return (0);
		i++;
	}
	if (str[i] == '=')
		result = 1;
	return (result);
}

int	process_assignment(char *assignment, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*eq_pos;

	eq_pos = ft_strchr(assignment, '=');
	if (!eq_pos)
		return (0);
	key = ft_substr(assignment, 0, (eq_pos - assignment));
	if (!key)
		return (0);
	value = ft_strdup(eq_pos + 1);
	if (!value)
	{
		free(key);
		return (0);
	}
	set_env_value(key, value, &shell->env);
	free_expander(value, key);
	return (0);
}

int	process_all_assignments(char **args, t_shell *shell)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i] && is_assignment(args[i]))
	{
		process_assignment(args[i], shell);
		i++;
	}
	return (i);
}
