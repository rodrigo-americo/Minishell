/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:17:33 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/17 14:02:29 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		return (NULL);
	}
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	return (token);
}

t_token	*token_new(const char *value, int type)
{
	return (create_token((char *)value, type));
}


void    token_del(void *content)
{
    t_token *token;

    token = (t_token *)content;
    if (!token)
        return ;
    if (token->value)
    {
        free(token->value);
        token->value = NULL;
    }
    free(token);
}

t_list	*token_node_new(char *value, int type)
{
	t_token	*t;
	t_list	*node;

	t = token_new(value, type);
	if (!t)
		return (NULL);
	node = ft_lstnew(t);
	if (!node)
		token_del(t);
	return (node);
}
