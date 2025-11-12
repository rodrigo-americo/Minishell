/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:35:38 by rgregori          #+#    #+#             */
/*   Updated: 2025/11/12 15:12:45 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_whitespace(char *input)
{
	while (*input != '\0' && (*input == ' ' || *input == '\t'))
		input++;
	return (input);
}

int	is_operator_start(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_token *extract_operator_token(char **input)
{
	if (**input == '>' && *(*input + 1) == '>')
	{
		*input += 2;
		return (create_token(">>", TOKEN_REDIR_APPEND));
	}
	else if (**input == '<' && *(*input + 1) == '<')
	{
		*input += 2;
		return (create_token("<<", TOKEN_REDIR_HEREDOC));
	}
	else if (**input == '>')
	{
		*input += 1;
		return (create_token(">", TOKEN_REDIR_OUT));
	}
	else if (**input == '<')
	{
		*input += 1;
		return (create_token("<", TOKEN_REDIR_IN));
	}
	else if (**input == '|')
	{
		*input += 1;
		return (create_token("|", TOKEN_PIPE));
	}
}

t_token *extract_word_token(char **input)
{
	char *start;

	start = *input;
	if (**input == '\'')
	{
		if (ft_strchr(*(*input + 1), '\''))
		{
			
		}
		else 
			create_token(input, TOKEN_WORD);
	}
	else if (**input == '\"')
	{
		if (ft_strchr(*input, '\"'))
		{
			
		}
		else 
			create_token(input, TOKEN_WORD);
	}
	else
	{
		if (ft_strchr(*input, ' '))
		{
			
		}
		else 
			create_token(strdup(input), TOKEN_WORD);
	}
	return ();
}


t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*new_token;

	head = NULL;
	while (*input)
	{
		input = skip_whitespace(input);
		if (!*input)
			break ;
		if (is_operator_start(*input))
			new_token = extract_operator_token(&input);
		else
			new_token = extract_word_token(&input);
		if (!new_token) 
		{
			free_tokens(head);
			return (NULL);
		}
		add_token_to_end(&head, new_token); 
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