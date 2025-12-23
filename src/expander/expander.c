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

static void	restore_spaces_in_redirs(t_redir *redirs)
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

void	expander(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		expand_and_dequote(current, shell);
		word_splitting(current);
		restore_spaces(current->args);
		restore_spaces_in_redirs(current->redirs);
		current = current->next;
	}
}
