/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:08:29 by ccavalca          #+#    #+#             */
/*   Updated: 2025/12/19 01:05:52 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir(t_redir *redir, t_shell *shell)
{
	int	fd;
	
	(void)shell;
	fd = -1;
	if (redir->type == REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == REDIR_HEREDOC)
		fd = redir->hrdc_fd;
	if (fd == -1)
		print_error(redir->file, "Error opening file\n");
	return (fd);
}

int	setup_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*current;
	int		fd;

	current = cmd->redirs;
	while (current)
	{
		fd = open_redir(current, shell);
		if (fd == -1)
		{
			perror(current->file);
			return (-1);
		}
		if (current->type == REDIR_IN || current->type == REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		current = current->next;
	}
	return (0);
}

// int setup_redirections_parent(t_cmd *cmd, t_shell *shell)
// {
//     int stdin_backup = dup(STDIN_FILENO);  // Salva o teclado
//     int stdout_backup = dup(STDOUT_FILENO); // Salva a tela

//     if (setup_redirections(cmd, shell) == -1)
//     {
//         // Se falhar, restaura e sai
//         dup2(stdin_backup, STDIN_FILENO);
//         dup2(stdout_backup, STDOUT_FILENO);
//         close(stdin_backup);
//         close(stdout_backup);
//         return (-1);
//     }
    
//     // EXECUTA O BUILT-IN AQUI NO PAI
    
//     // Restaura o terminal original após o comando
//     dup2(stdin_backup, STDIN_FILENO);
//     dup2(stdout_backup, STDOUT_FILENO);
//     close(stdin_backup);
//     close(stdout_backup);
//     return (0);
// }
