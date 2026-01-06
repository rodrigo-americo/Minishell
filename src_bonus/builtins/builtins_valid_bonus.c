/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:03:32 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 10:03:47 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
	(void)value;
	if (!key || key[0] == '\0')
	{
		print_error("export", "not a valid identifier");
		return (0);
	}
	return (1);
}
