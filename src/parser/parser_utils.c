/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:06:07 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/02 14:41:30 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir *create_redir(char *file_name, t_redir_type type)
{
	t_redir *redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = file_name;
	if (type == TOKEN_REDIR_IN)
		redir->type = REDIR_IN;
	else if (type == TOKEN_REDIR_OUT)
		redir->type = REDIR_OUT;
	else if (type == TOKEN_REDIR_APPEND)
		redir->type = REDIR_APPEND;
	else if (type == TOKEN_REDIR_HEREDOC)
		redir->type = REDIR_HEREDOC;
	redir->next = NULL;
	return (redir);
}

void add_redir_to_end(t_redir **head, t_redir *new_redir)
{
	t_redir *current;

	if(!new_redir)
		return ;
	if (!*head)
	{
		*head = new_redir;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

static char **ft_coop_arry(char **arr, int len, char *new_str)
{
	int 	i;
	char	**new_arr;

	i = -1;
	new_arr = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	while (++i < len)
		new_arr[i] = arr[i];
	new_arr[len] = new_str;
	new_arr[len + 1] = NULL;
	return (new_arr);	
}

char **ft_add_to_array(char **arr, char *new_str)
{
	int		len;
	char	**new_arr;

	if (!new_str)
		return (arr);
	len = 0;
	if (arr)
	{
		while (arr[len])
			len++;
	}
	new_arr = ft_coop_arry(arr, len, new_str);
	if (!new_arr)
	{
		if (arr)
			free_array(arr);
		return (NULL);	
	}
	if (arr)
		free(arr);
	return (new_arr);	
}

void	free_cmd(t_cmd *cmd)
{
	t_redir	*redir;
	t_redir	*next;

	if (!cmd)
		return;
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
void free_commands(t_cmd *cmds)
{
    t_cmd *current;
    t_cmd *next;

    current = cmds;
    while (current)
    {
        next = current->next;
        free_cmd(current);
        current = next;
    }
}