/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:01:32 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/02 11:35:28 by rgregori         ###   ########.fr       */
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
			new_str = append_char_safe(new_str, str[i], quote);
			i++;
		}
	}
	return (new_str);
}

static void	expand_and_dequote(t_cmd *cmd, t_shell *shell)
{
	t_redir	*curr;
	char	*tmp;
	int		i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		tmp = cmd->args[i];
		cmd->args[i] = process_string_content(tmp, shell);
		free(tmp);
		i++;
	}
	curr = cmd->redirs;
	while (curr)
	{
		tmp = curr->file;
		curr->file = process_string_content(tmp, shell);
		free(tmp);
		curr = curr->next;
	}
}

static void	restore_spaces(char **args)
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

void	expander(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		expand_and_dequote(current, shell);
		word_splitting(current);
		restore_spaces(current->args);
		current = current->next;
	}
}
