/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:18:57 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/17 11:18:57 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_expander(char *val, char *key)
{
	if (val || key)
	{
		free(val);
		free(key);
	}
}

static char	*get_pid_str(void)
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

static void	join_and_free(char **str, char *to_add)
{
	char	*temp;

	if (!to_add)
		return ;
	temp = *str;
	*str = ft_strjoin(*str, to_add);
	free(temp);
	free(to_add);
}

static int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

static char	*get_expanded_value(char *str, t_shell *shell, int *len)
{
	char	*key;
	char	*val;
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
	if (env_val)
		val = ft_strdup(env_val);
	else
		val = NULL;
	free_expander(env_val, key);
	return (val);
}

int	ft_handle_expansion(char **new_str, char *str_at_dollar, t_shell *shell)
{
	char	*value;
	int		len;

	len = 0;
	if (!str_at_dollar[1] || str_at_dollar[1] == ' ' || str_at_dollar[1] == '"')
	{
		join_and_free(new_str, ft_strdup("$"));
		return (1);
	}
	value = get_expanded_value(str_at_dollar + 1, shell, &len);
	if (value)
		join_and_free(new_str, value);
	else
	{
		if (len == 0)
		{
			join_and_free(new_str, ft_strdup("$"));
			return (1);
		}
	}
	return (len + 1);
}
