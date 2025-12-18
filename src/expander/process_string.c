/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:58:07 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/17 10:58:38 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	get_quote_state(char s, char state)
{
	if (s == state)
		state = 0;
	else if (state == 0)
		state = s;
	return (state);
}

static char	*append_char_safe(char *str, char c, char quote_state)
{
	if (quote_state && (c == ' ' || c == '\t'))
		c = 0x1F;
	return (ft_strjoin_char(str, c));
}

char	*process_string_content(char *str, t_shell *shell)
{
	char	*new_str;
	char	*temp;
	char	quote;
	int		i;

	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = get_quote_state(str[i], quote);
			i++;
		}
		else if (str[i] == '$' && quote != '\'')
			i += ft_handle_expansion(&new_str, str + i, shell);
		else
		{
			temp = append_char_safe(new_str, str[i], quote);
			if (!temp)
				return (free(new_str), NULL);
			new_str = temp;
			i++;
		}
	}
	return (new_str);
}
