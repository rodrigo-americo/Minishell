/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:18:57 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/03 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	restore_spaces(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args && args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == 0x1F)
				args[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void	restore_spaces_in_redirs(t_redir *redirs)
{
	t_redir	*curr;
	int		j;

	curr = redirs;
	while (curr)
	{
		j = 0;
		while (curr->file && curr->file[j])
		{
			if (curr->file[j] == 0x1F)
				curr->file[j] = ' ';
			j++;
		}
		curr = curr->next;
	}
}

static void	join_and_free(char **str, char *to_add)
{
	char	*temp;

	if (!to_add)
		return ;
	temp = *str;
	*str = ft_strjoin(*str, to_add);
	free(temp);
	free(to_add);
}

int	ft_handle_expansion(char **new_str, char *str_at_dollar, t_shell *shell)
{
	char	*value;
	int		len;

	len = 0;
	if (!str_at_dollar[1] || str_at_dollar[1] == ' '
		|| str_at_dollar[1] == '"')
	{
		join_and_free(new_str, ft_strdup("$"));
		return (1);
	}
	value = get_expanded_value(str_at_dollar + 1, shell, &len);
	if (value)
		join_and_free(new_str, value);
	else
	{
		if (len == 0)
		{
			join_and_free(new_str, ft_strdup("$"));
			return (1);
		}
	}
	return (len + 1);
}
