/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/19 01:22:02 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int handle_input_redir(char *file)
{
    int fd;
    
    if (!file)
        return (-1);

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror(file);
        return (-1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (0);
}

static int	handle_output_redir(char *file)
{
    int fd;
    
    if (!file)
        return (-1);
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror(file);
        return (-1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}

static int	handle_append_redir(char *file)
{
    int fd;
    
    if (!file)
        return (-1);
    fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror(file);
        return (-1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}

int handle_heredoc(char *delimiter)
{
    int     pipefd[2];
    char    *line;
    
    if (pipe(pipefd) < 0)
        return (perror("pipe"), -1);
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    return (0);
}

/*
** setup_redirections - Aplica todos os redirecionamentos de um comando
**
** Itera pela lista encadeada de redirecionamentos e aplica cada um
** chamando a função apropriada (handle_input_redir, handle_output_redir,
** handle_append_redir ou handle_heredoc) baseado no tipo.
**
** IMPORTANTE: Deve ser chamado DEPOIS de fazer fork() mas ANTES de execve().
** Se múltiplos redirecionamentos do mesmo tipo existirem, o último prevalece.
**
** @redirs: lista encadeada de redirecionamentos
**
** Return: 0 em sucesso, -1 em erro
*/
int	setup_redirections(t_redir *redirs)
{
	t_redir	*curr;

	curr = redirs;
	while (curr)
	{
		if (curr->type == REDIR_IN)
		{
			if (handle_input_redir(curr->file) < 0)
				return (-1);
		}
		else if (curr->type == REDIR_OUT)
		{
			if (handle_output_redir(curr->file) < 0)
				return (-1);
		}
		else if (curr->type == REDIR_APPEND)
		{
			if (handle_append_redir(curr->file) < 0)
				return (-1);
		}
		else if (curr->type == REDIR_HEREDOC)
		{
			if (handle_heredoc(curr->file) < 0)
				return (-1);
		}
		curr = curr->next;
	}
	return (0);
}
