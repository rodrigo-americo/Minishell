/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/03 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	handle_heredoc_redir(t_redir *redir, t_shell *shell)
{
	if (redir->type == REDIR_HEREDOC)
	{
		if (process_heredoc_at_parse_time(redir, shell) < 0)
			return (-1);
	}
	return (0);
}

t_redir	*parse_redirection(t_list **tokens, t_shell *shell)
{
	t_token	*redir_tok;
	t_token	*file_tok;
	t_redir	*redir;

	redir_tok = peek_token(*tokens);
	consume_token(tokens);
	file_tok = peek_token(*tokens);
	if (!file_tok || file_tok->type != TOKEN_WORD)
		return (print_error("syntax error", "unexpected token\n"), NULL);
	redir = create_redir(file_tok->value, redir_tok->type);
	if (!redir)
		return (NULL);
	file_tok->value = NULL;
	consume_token(tokens);
	if (handle_heredoc_redir(redir, shell) < 0)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}
