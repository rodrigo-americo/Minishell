/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:43:34 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 00:26:10 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_redir(char *file_name, t_redir_type type)
{
	t_redir	*redir;

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
	redir->hrdc_fd = -1;
	redir->next = NULL;
	return (redir);
}

void	add_redir_to_end(t_redir **head, t_redir *new_redir)
{
	t_redir	*current;

	if (!new_redir)
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
