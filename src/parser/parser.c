/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:30:33 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 16:43:40 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_redir(t_cmd *cmd, t_list **current)
{
	t_token	*redir_tok;
	t_token	*file_tok;
	t_redir	*new_redir;

	redir_tok = (t_token *)(*current)->content;
	file_tok = (t_token *)(*current)->next->content;
	new_redir = create_redir(file_tok->value, redir_tok->type);
	if (new_redir)
	{
		add_redir_to_end(&cmd->redirs, new_redir);
		file_tok->value = NULL;
	}
	*current = (*current)->next->next;
}

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

static t_cmd	*parse_block(t_list **token)
{
	t_cmd	*cmd;
	t_token	*tok;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (print_error("parser", "malloc error\n"), NULL);
	while (*token)
	{
		tok = (t_token *)(*token)->content;
		if (ft_strcmp(tok->value, "|") == 0)
		{
			printf("%s", ERR_SYNTAX);
			return (NULL);
		}
		if (tok->type >= TOKEN_REDIR_IN)
			process_redir(cmd, token);
		else
			process_arg(cmd, token);
	}
	if (!cmd->args && !cmd->redirs)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

t_cmd	*parser(t_list *tokens)
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
		new = parse_block(&tokens);
		if (!new)
			return (free_commands(head), NULL);
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
