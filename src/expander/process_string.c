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

#include "minishell.h"

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
	new_str = ft_strjoin_char(str, c);
	if (str)
		free(str);
	return (new_str);
}

static int	handle_quote_char(char **new_str, char c, char *quote)
{
	char	*temp;

	if (*quote == '\"' && c == '\'')
	{
		temp = append_char_safe(*new_str, c, *quote);
		if (!temp)
			return (0);
		*new_str = temp;
	}
	else if (*quote == '\'' && c == '\"')
	{
		temp = append_char_safe(*new_str, c, *quote);
		if (!temp)
			return (0);
		*new_str = temp;
	}
	else
		*quote = get_quote_state(c, *quote);
	return (1);
}

static int	process_char(char **new_str, char *str, t_proc *p, t_shell *sh)
{
	char	*temp;

	if (str[p->i] == '$' && p->quote != '\'')
		p->i += ft_handle_expansion(new_str, str + p->i, sh) - 1;
	else if (str[p->i] == '\'' || str[p->i] == '\"')
	{
		if (!handle_quote_char(new_str, str[p->i], &p->quote))
			return (0);
	}
	else
	{
		temp = append_char_safe(*new_str, str[p->i], p->quote);
		if (!temp)
			return (0);
		*new_str = temp;
	}
	if (!*new_str)
		return (0);
	return (1);
}

char	*process_string_content(char *str, t_shell *shell)
{
	char	*new_str;
	t_proc	p;

	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	p.quote = 0;
	p.i = -1;
	while (str[++p.i])
	{
		if (!process_char(&new_str, str, &p, shell))
			return (free(new_str), NULL);
	}
	return (new_str);
}
