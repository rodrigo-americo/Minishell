/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:35:38 by rgregori          #+#    #+#             */
/*   Updated: 2025/11/25 11:25:33 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (NULL);
}

/*
** Retorna o tamanho da palavra até o próximo separador ou fim da string.
** Retorna -1 se encontrar aspas não fechadas (Erro Léxico).
*/
static int get_word_len(char *input)
{
    int i;
    char quote;

    i = 0;
    while (input[i] && !is_separator(input[i]))
    {
        if (input[i] == '\'' || input[i] == '\"')
        {
            quote = input[i++]; // Guarda qual aspa abriu
            while (input[i] && input[i] != quote)
                i++;
            if (!input[i]) // Chegou ao fim sem fechar
                return (-1); // Código de erro
        }
        i++;
    }
    return (i);
}

static t_token *extract_word_token(char **input)
{
    int     len;
    char    *value;

    len = get_word_len(*input);
    if (len == -1)
    {
        print_error("minishell", "syntax error: unclosed quotes\n");
        return (NULL); 
    }
    value = ft_substr(*input, 0, len);
    *input += len;
    return (create_token(value, TOKEN_WORD));
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
