/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccavalca <ccavalca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:07:53 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/15 15:24:48 by ccavalca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void error_exit(char *msg)
{
  perror(msg);
  exit(1);
}

void print_error(char *cmd, char *msg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}

char *skip_whitespace(char *input)
{
  while (*input != '\0' && (*input == ' ' || *input == '\t'))
    input++;
  return (input);
}

int is_separator(char c)
{
  return ((c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>' ||
           c == '(' || c == ')' || c == '&' || c == '\0'));
}

void free_array(char **arr)
{
  int i;

  i = 0;
  if (!arr)
    return;
  while (arr[i]) {
    if (arr[i])
      free(arr[i]);
    i++;
  }
  free(arr);
}
