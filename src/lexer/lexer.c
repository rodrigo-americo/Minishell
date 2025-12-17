/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:35:38 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/17 15:33:41 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*try_match_operator(char **input, t_operator *op)
{
	int	i;

	i = 0;
	while (i < op->len)
	{
		if ((*input)[i] != op->symbol[i])
			return (NULL);
		i++;
	}
	*input += op->len;
	return (token_node_new(op->symbol, op->type));
}

t_list	*extract_operator_token(char **input)
{
	t_operator	operators[6];
	t_list		*result;
	int			i;

	init_operators(operators);
	i = 0;
	while (operators[i].symbol)
	{
		result = try_match_operator(input, &operators[i]);
		if (result)
			return (result);
		i++;
	}
	return (NULL);
}

static int	get_word_len(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i] && !is_separator(input[i]))
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (-1);
		}
		i++;
	}
	return (i);
}

static t_list	*extract_word_token(char **input)
{
	int		len;
	char	*value;

	len = get_word_len(*input);
	if (len == -1)
	{
		print_error("minishell", "syntax error: unclosed quotes\n");
		return (NULL);
	}
	value = ft_substr(*input, 0, len);
	*input += len;
	return (token_node_new(value, TOKEN_WORD));
}

t_list	*lexer(char *input)
{
	t_list	*head;
	t_list	*new_node;

	head = NULL;
	while (*input)
	{
		input = skip_whitespace(input);
		if (!*input)
			break ;
		if (is_operator_start(*input))
			new_node = extract_operator_token(&input);
		else
			new_node = extract_word_token(&input);
		if (!new_node)
		{
			tokens_list_clear(&head);
			return (NULL);
		}
		tokens_list_add_back(&head, new_node);
	}
	return (head);
}
