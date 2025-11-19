/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:17:33 by rgregori          #+#    #+#             */
/*   Updated: 2025/11/19 15:18:08 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		return (NULL);
	}
	token->value = strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}
void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current  = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		current = next;	
	}	
}

void	add_token_to_end(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}
