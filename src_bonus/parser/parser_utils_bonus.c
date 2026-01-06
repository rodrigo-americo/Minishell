/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:06:07 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/17 15:15:54 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	**ft_realloc_array(char **old, int len, char *new_str)
{
	char	**new_arr;
	int		i;

	new_arr = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_arr[i] = old[i];
		i++;
	}
	new_arr[i] = new_str;
	new_arr[i + 1] = NULL;
	if (old)
		free(old);
	return (new_arr);
}

char	**ft_add_to_array(char **arr, char *new_str)
{
	int	len;

	len = 0;
	if (arr)
	{
		while (arr[len])
			len++;
	}
	return (ft_realloc_array(arr, len, new_str));
}

void	free_cmd(t_cmd *cmd)
{
	t_redir	*redir;
	t_redir	*next;

	if (!cmd)
		return ;
	if (cmd->args)
		free_array(cmd->args);
	redir = cmd->redirs;
	while (redir)
	{
		next = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = next;
	}
	free(cmd);
}

void	free_commands(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmds;
	while (current)
	{
		next = current->next;
		free_cmd(current);
		current = next;
	}
}
