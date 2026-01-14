/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:30:33 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/14 17:33:09 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_arg(t_cmd *cmd, t_list **current)
{
	t_token	*tok;
	char	**new_args;

	tok = (t_token *)(*current)->content;
	new_args = ft_add_to_array(cmd->args, tok->value);
	if (new_args)
	{
		cmd->args = new_args;
		tok->value = NULL;
	}
	*current = (*current)->next;
}

static int	parse_token(t_cmd *cmd, t_list **token, t_shell *shell)
{
	t_token	*tok;

	tok = (t_token *)(*token)->content;
	if (ft_strcmp(tok->value, "|") == 0)
		return (1);
	if (tok->type >= TOKEN_REDIR_IN)
	{
		if (process_redir(cmd, token, shell) < 0)
			return (-1);
	}
	else
		process_arg(cmd, token);
	return (0);
}

static t_cmd	*parse_block(t_list **token, t_shell *shell)
{
	t_cmd	*cmd;
	int		ret;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (print_error("parser", "malloc error\n"), NULL);
	while (*token)
	{
		ret = parse_token(cmd, token, shell);
		if (ret == 1)
			break ;
		if (ret == -1)
			return (free_cmd(cmd), NULL);
	}
	if (!cmd->args && !cmd->redirs)
		return (free_cmd(cmd), NULL);
	return (cmd);
}

static t_cmd	*handle_parse_err(t_cmd *head)
{
	if (g_signal_received != SIGINT)
		print_error("syntax error", "unexpected token '|'\n");
	return (free_commands(head), NULL);
}

t_cmd	*parser(t_list *tokens, t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*last;
	t_cmd	*new;

	head = NULL;
	last = NULL;
	while (tokens)
	{
		if (check_syntax(tokens, head))
			return (free_commands(head), NULL);
		new = parse_block(&tokens, shell);
		if (!new)
			return (handle_parse_err(head));
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		if (tokens && ft_strcmp(((t_token *)tokens->content)->value, "|") == 0)
			tokens = tokens->next;
	}
	return (head);
}
