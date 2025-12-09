/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:17:33 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/02 14:31:41 by rgregori         ###   ########.fr       */
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
/* Note: legacy linked-list helpers were removed during migration to t_list.
 * Use `token_node_new`, `tokens_list_add_back`, and `tokens_list_clear`.
 */

/*
 * New generic helpers using libft's t_list so tokens and env can share list utils.
 * These are non-intrusive: they coexist with the existing t_token linked-list
 * representation and provide a migration path to use t_list throughout the code.
 */

/* Allocate a token (same as create_token but named for clarity) */
t_token *token_new(const char *value, int type)
{
	return (create_token((char *)value, type));
}

/* Deallocator suitable for ft_lstclear */
void token_del(void *p)
{
	t_token *t;

	if (!p)
		return ;
	t = (t_token *)p;
	if (t->value)
		free(t->value);
	free(t);
}

/* Create a t_list node that contains a newly allocated t_token */
t_list *token_node_new(char *value, int type)
{
	t_token *t;
	t_list *node;

	t = token_new(value, type);
	if (!t)
		return (NULL);
	node = ft_lstnew(t);
	if (!node)
		token_del(t);
	return (node);
}

/* Add a token node to a t_list-backed tokens list */
void tokens_list_add_back(t_list **head, t_list *new_node)
{
	if (!new_node)
		return ;
	ft_lstadd_back(head, new_node);
}

/* Clear a t_list-backed tokens list */
void tokens_list_clear(t_list **head)
{
	if (!head)
		return ;
	ft_lstclear(head, token_del);
}
