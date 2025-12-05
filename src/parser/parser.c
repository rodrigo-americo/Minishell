/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:30:33 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/02 14:32:09 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirection_error(t_token *token)
{
	if (token->type >= TOKEN_REDIR_IN)
	{
		if (token->next == NULL)
		{
			print_error("minishell: syntax error", "unexpected token 'newline'\n");
			return (1);
		}
		if (token->next->type != TOKEN_WORD)
    	{
			print_error("minishell: syntax error", "unexpected token near redirection\n");
			return (1);
		}
	}
	return (0);
}

static int	syntax_error(t_token *token, t_cmd *head)
{
    if (head == NULL && ft_strcmp(token->value, "|") == 0)
    {
        print_error("minishell: syntax error", "unexpected token '|'\n");
        return (1); 
    }
    if (ft_strcmp(token->value, "|") == 0)
    {
        if (token->next == NULL)
        {
            print_error("minishell: syntax error", "unexpected token (EOF)\n");
            return (1);
        }
        else if (ft_strcmp(token->next->value, "|") == 0)
        {
            print_error("minishell: syntax error", "unexpected token '|'\n");
            return (1);
        }
    }
	if (redirection_error(token))
		return (1);
	return (0);
}

static t_cmd *parse_simple_command(t_token **token)
{
	t_cmd	*cmd;
	t_token	*current;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		print_error("minishell: parse error", "malloc Error\n");
		return (NULL);
	}
	cmd->args = NULL;
	cmd->redirs = NULL;
	current = *token;
	while (current && ft_strcmp(current->value, "|") != 0 )
	{
		if (current->type >= TOKEN_REDIR_IN)
		{
			add_redir_to_end(&cmd->redirs, create_redir(current->next->value, current->type));
			current->next->value = NULL;
			current = current->next->next;
		}
		else
		{
			cmd->args = ft_add_to_array(cmd->args, current->value);
			current->value = NULL;
			current = current->next;
		}
		if (!cmd->args && !cmd->redirs)
		{
			free_cmd(cmd);
			*token = current;
			return (NULL);
		}
	}
	*token = current;
	return (cmd);
}

t_cmd *parser(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current_cmd;
	t_token	*current_token;
	t_cmd	*new_cmd;

	head = NULL;
	current_cmd = NULL;
	current_token = tokens;
	while (current_token != NULL)
	{
		if (syntax_error(current_token, head))
		{
			free_tokens(tokens);
			free_commands(head); // Libera os comandos construídos até agora
			return (NULL);
		}
		new_cmd = parse_simple_command(&current_token);
		if (!new_cmd)
		{
			free_tokens(tokens);
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
		if (current_token && ft_strcmp(current_token->value, "|") == 0)
			current_token = current_token->next; // Pula o '|'
	}
	free_tokens(tokens);
	return (head);
}
