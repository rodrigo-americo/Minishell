/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:35:38 by rgregori          #+#    #+#             */
/*   Updated: 2025/10/24 15:44:45 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_whitespace(char *input)
{
	while (*input != '\0' && (*input != ' ' || *input != '\t'))
		input++;
	return (input);
}

t_token	*lexer(char *input)
{
	t_token	*head;

	head = NULL;
	while (*input)
	{
		input = skip_whitespace(input);
		if (!*input)
			break ;
	}
	return (head);	
}

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