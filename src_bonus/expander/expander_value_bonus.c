/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_value_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*get_pid_str(void)
{
	int		fd;
	int		i;
	char	buf[64];
	ssize_t	n;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("0"));
	ft_bzero(buf, 64);
	n = read(fd, buf, 63);
	close(fd);
	if (n <= 0)
		return (ft_strdup("0"));
	i = 0;
	while (buf[i] && buf[i] != ' ')
		i++;
	buf[i] = '\0';
	return (ft_strdup(buf));
}

int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*get_expanded_value(char *str, t_shell *shell, int *len)
{
	char	*key;
	char	*env_val;

	if (str[0] == '?')
	{
		*len = 1;
		return (ft_itoa(shell->exit_status));
	}
	if (str[0] == '$')
	{
		*len = 1;
		return (get_pid_str());
	}
	*len = get_var_len(str);
	if (*len == 0)
		return (NULL);
	key = ft_substr(str, 0, *len);
	env_val = get_env_value(key, shell->env);
	free(key);
	return (env_val);
}
