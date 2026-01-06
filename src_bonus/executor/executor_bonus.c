/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	executor(t_ast_node *node, t_shell *shell)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		shell->exit_status = execute_command(node, shell);
	else if (node->type == NODE_PIPE)
		shell->exit_status = execute_pipe(node, shell);
	else if (node->type == NODE_AND)
		shell->exit_status = execute_and(node, shell);
	else if (node->type == NODE_OR)
		shell->exit_status = execute_or(node, shell);
	else if (node->type == NODE_SUBSHELL)
		shell->exit_status = execute_subshell(node, shell);
	return (shell->exit_status);
}
