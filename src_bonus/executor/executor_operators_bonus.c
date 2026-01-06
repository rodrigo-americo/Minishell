/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	execute_and(t_ast_node *node, t_shell *shell)
{
	int	exit_left;

	exit_left = executor(node->left, shell);
	if (exit_left == 0)
		return (executor(node->right, shell));
	return (exit_left);
}

int	execute_or(t_ast_node *node, t_shell *shell)
{
	int	exit_left;

	exit_left = executor(node->left, shell);
	if (exit_left != 0)
		return (executor(node->right, shell));
	return (exit_left);
}
