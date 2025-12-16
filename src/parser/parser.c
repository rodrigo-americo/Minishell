/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:30:33 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/16 11:16:23 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirection_error(t_list *node)
{
	t_token	*tok;

	if (!node)
		return (0);
	tok = (t_token *)node->content;
	if (tok->type >= TOKEN_REDIR_IN)
	{
		if (node->next == NULL)
		{
			print_error("minishell: syntax error", "unexpected token 'newline'\n");
			return (1);
		}
		if (((t_token *)node->next->content)->type != TOKEN_WORD)
		{
			print_error("minishell: syntax error", "unexpected token near redirection\n");
			return (1);
		}
	}
	return (0);
}

static int	syntax_error(t_list *node, t_cmd *head)
{
	t_token	*tok;

	if (!node)
		return (0);
	tok = (t_token *)node->content;
	if (head == NULL && ft_strcmp(tok->value, "|") == 0)
	{
		print_error("minishell: syntax error", "unexpected token '|'\n");
		return (1); 
	}
	if (ft_strcmp(tok->value, "|") == 0)
	{
		if (node->next == NULL)
		{
			print_error("minishell: syntax error", "unexpected token (EOF)\n");
			return (1);
		}
		else if (ft_strcmp(((t_token *)node->next->content)->value, "|") == 0)
		{
			print_error("minishell: syntax error", "unexpected token '|'\n");
			return (1);
		}
	}
	if (redirection_error(node))
		return (1);
	return (0);
}

static t_cmd	*parse_simple_command(t_list **token)
{
	t_cmd	*cmd;
	t_list	*current_node;
	t_token	*current;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		print_error("minishell: parse error", "malloc Error\n");
		return (NULL);
	}
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	current_node = *token;
	current = current_node ? (t_token *)current_node->content : NULL;
	while (current_node && ft_strcmp(current->value, "|") != 0 )
	{
		if (current->type >= TOKEN_REDIR_IN)
		{
			if (!current_node->next)
			{
				free_cmd(cmd);
				*token = current_node->next;
				return (NULL);
			}
			add_redir_to_end(&cmd->redirs, create_redir(((t_token *)current_node->next->content)->value, current->type));
			((t_token *)current_node->next->content)->value = NULL;
			current_node = current_node->next->next;
			current = current_node ? (t_token *)current_node->content : NULL;
		}
		else
		{
			cmd->args = ft_add_to_array(cmd->args, current->value);
			current->value = NULL;
			current_node = current_node->next;
			current = current_node ? (t_token *)current_node->content : NULL;
		}
		if (!cmd->args && !cmd->redirs)
		{
			free_cmd(cmd);
			*token = current_node;
			return (NULL);
		}
	}
	*token = current_node;
	return (cmd);
}

t_cmd *parser(t_list *tokens)
{
	t_cmd	*head;
	t_cmd	*current_cmd;
	t_list  *current_token;
	t_cmd	*new_cmd;

	head = NULL;
	current_cmd = NULL;
	current_token = tokens;
	while (current_token != NULL)
	{
		if (syntax_error(current_token, head))
		{
			free_commands(head); // Libera os comandos construídos até agora
			return (NULL);
		}
		new_cmd = parse_simple_command(&current_token);
		if (!new_cmd)
		{
			free_commands(head);
			return (NULL);
		}
		if (head == NULL)
		{
			head = new_cmd;
			current_cmd = head;
		}
		else
		{
			current_cmd->next = new_cmd;
			current_cmd = current_cmd->next;
		}
		if (current_token && ft_strcmp(((t_token *)current_token->content)->value, "|") == 0)
			current_token = current_token->next; // Pula o '|'
	}
	return (head);
}
