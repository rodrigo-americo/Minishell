/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:03:32 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/23 19:00:59 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	extract_key_value(char *arg, char **key, char **value)
{
	char	*eq_sign;

	eq_sign = ft_strchr(arg, '=');
	if (eq_sign)
	{
		*key = ft_substr(arg, 0, eq_sign - arg);
		*value = ft_strdup(eq_sign + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
}

int	validate_export_key(char *key, char *value)
{
	int	result;

	result = 0;
	if (!key || key[0] == '\0')
	{
		print_error("export", "not a valid identifier");
		free(key);
		if (value)
			free(value);
		result = 0;
	}
	else
		result = 1;
	return (result);
}
