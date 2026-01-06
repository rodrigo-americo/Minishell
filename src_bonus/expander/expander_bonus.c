/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:01:32 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/03 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	expand_args(char ***args, t_shell *shell)
{
	char	*tmp;
	char	**expanded;
	int		i;

	i = 0;
	while (*args && (*args)[i])
	{
		tmp = (*args)[i];
		(*args)[i] = process_string_content(tmp, shell);
		free(tmp);
		i++;
	}
	expanded = expand_wildcards(*args);
	if (expanded)
	{
		free_array(*args);
		*args = expanded;
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
	restore_spaces(node->args);
	restore_spaces_in_redirs(node->redirs);
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
