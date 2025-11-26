/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:01:32 by rgregori          #+#    #+#             */
/*   Updated: 2025/11/26 13:48:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_string_content(char *original_str, t_shell *shell)
{
	char	*new_str;
	char	quote_state;
	int		i;

	new_str = ft_strdup("");
	quote_state = 0;
	i = 0;
	while (original_str[i])
	{
		if (original_str[i] == '\'' || original_str[i] == '\"')
		{
			if (original_str[i] == quote_state)
				quote_state = 0;
			else if (quote_state == 0)
				quote_state = original_str[i];
			i++;
			continue;
		}
		if (original_str[i] == '$' && quote_state != '\'')
			i += ft_handle_expansion(&new_str, original_str + i, shell); // ft_handle_expansion avança o índice 'i'
		else
		{
			new_str = ft_strjoin_char(new_str, original_str[i]);
			i++;
		}
	}
	return (new_str);
}

static void expand_and_dequote(t_cmd *cmd, t_shell *shell)
{
	t_redir	*current_redir;
	char	*old_file;
	char	*old_arg;
	int		i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		old_arg = cmd->args[i];
		cmd->args[i] = process_string_content(old_arg, shell); 
		free(old_arg);
		i++;
	}
	current_redir = cmd->redirs;
	while (current_redir)
	{
		old_file = current_redir->file;
		current_redir->file = process_string_content(old_file, shell); 
		free(old_file);
		current_redir = current_redir->next;
	}
}

void	expander(t_cmd *cmds, t_shell *shell)
{
	t_cmd *current;

	current = cmds;
	while (current)
	{
		expand_and_dequote(current, shell); 
		word_splitting(current); 
		current = current->next;
	}
}
