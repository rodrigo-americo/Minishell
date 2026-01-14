/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:58:07 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 17:55:19 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	get_quote_state(char s, char state)
{
	if (s == state)
		state = 0;
	else if (state == 0 && (s == '\'' || s == '\"'))
		return (s);
	return (state);
}

static char	*append_char_safe(char *str, char c, char quote_state)
{
	char	*new_str;

	if (quote_state && (c == ' ' || c == '\t'))
		c = 0x1F;
	if (quote_state && c == '*')
		c = 0x1E;
	new_str = ft_strjoin_char(str, c);
	if (str)
		free(str);
	return (new_str);
}

static void	handle_quote_char(char **new_str, char c, char *quote)
{
	if (*quote == '\"' && c == '\'')
		*new_str = append_char_safe(*new_str, c, *quote);
	else if (*quote == '\'' && c == '\"')
		*new_str = append_char_safe(*new_str, c, *quote);
	else
		*quote = get_quote_state(c, *quote);
}

char	*process_string_content(char *str, t_shell *shell)
{
	char	*new_str;
	char	quote;
	int		i;

	new_str = ft_strdup("");
	quote = 0;
	i = 0;
	while (new_str && str[i])
	{
		if (str[i] == '$' && quote != '\'')
			i += ft_handle_expansion(&new_str, str + i, shell);
		else if (str[i] == '\\' && str[i + 1] && quote != '\'')
		{
			if (str[i + 1] == '*')
				new_str = append_char_safe(new_str, 0x1E, 0);
			else
				new_str = append_char_safe(new_str, str[i + 1], quote);
			i += 2;
		}
		else
		{
			if (str[i] == '\'' || str[i] == '\"')
				handle_quote_char(&new_str, str[i], &quote);
			else
				new_str = append_char_safe(new_str, str[i], quote);
			i++;
		}
	}
	return (new_str);
}
