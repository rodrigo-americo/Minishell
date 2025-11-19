/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:07:53 by rgregori          #+#    #+#             */
/*   Updated: 2025/10/27 10:53:14 by rgregori         ###   ########.fr       */
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
	printf("%s : %s",cmd, msg);
}
char	**ft_split(char *str, char delimiter);

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}
