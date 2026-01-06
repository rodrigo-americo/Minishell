/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:04:46 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/17 15:08:56 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	tokens_list_add_back(t_list **head, t_list *new_node)
{
	if (!new_node)
		return ;
	ft_lstadd_back(head, new_node);
}

void	tokens_list_clear(t_list **tokens)
{
	if (!tokens || !*tokens)
		return ;
	ft_lstclear(tokens, token_del);
}

int	skip_quotes(char *str, int i)
{
	char	quote;

	if (str[i] != '\'' && str[i] != '\"')
		return (i);
	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}
