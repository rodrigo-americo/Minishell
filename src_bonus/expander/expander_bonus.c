/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:01:32 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/06 14:22:30 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	expand_args(char ***args, t_shell *shell)
{
	char	*tmp;
	int		i;

	i = 0;
	while (*args && (*args)[i])
	{
		tmp = (*args)[i];
		(*args)[i] = process_string_content(tmp, shell);
		free(tmp);
		i++;
	}
}

static void	expand_redirs(t_redir *redirs, t_shell *shell)
{
	t_redir	*curr;
	char	*tmp;

	curr = redirs;
	while (curr)
	{
		if (curr->type != REDIR_HEREDOC)
		{
			tmp = curr->file;
			curr->file = process_string_content(tmp, shell);
			free(tmp);
		}
		curr = curr->next;
	}
}

static void	expand_command_node(t_ast_node *node, t_shell *shell)
{
	expand_args(&node->args, shell);
	expand_redirs(node->redirs, shell);
	word_splitting_ast(node);
}

void	expander(t_ast_node *node, t_shell *shell)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
		expand_command_node(node, shell);
	expander(node->left, shell);
	expander(node->right, shell);
}
