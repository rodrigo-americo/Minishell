/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:04:46 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/17 12:06:13 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_list_add_back(t_list **head, t_list *new_node)
{
	if (!new_node)
		return ;
	ft_lstadd_back(head, new_node);
}

void	tokens_list_clear(t_list **head)
{
	if (!head)
		return ;
	ft_lstclear(head, token_del);
}


