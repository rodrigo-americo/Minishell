/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:07:53 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/23 16:41:37 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void	print_error(char *cmd, char *msg)
{
	fprintf(stderr, "%s: %s\n", cmd, msg);
}

char	*skip_whitespace(char *input)
{
	while (*input != '\0' && (*input == ' ' || *input == '\t'))
		input++;
	return (input);
}

int	is_separator(char c)
{
	return ((c == ' ' || c == '\t' || c == '|'
			|| c == '<' || c == '>' || c == '\0'));
}
