/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:20:41 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/02 13:18:34 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strjoin_char(char *s, char c)
{
	char	*new_s;
	int		len;

	if (!s)
		len = 0;
	else
		len = ft_strlen(s);
	new_s = malloc(len + 2);
	if (!new_s)
		return (NULL);
	if (s)
		ft_memcpy(new_s, s, len);
	new_s[len] = c;
	new_s[len + 1] = '\0';
	if (s)
		free(s);
	return (new_s);
}

static char *get_pid_str(void)
{
	int		fd;
	int		i;
	char	buf[64];
	ssize_t	n;

	fd = open("/proc/self/stat",O_RDONLY);
	if (fd < 0)
		return (ft_strdup("0"));
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (n <= 0)
		return (ft_strdup("0"));
	buf[n] = '\0';
	i = 0;
	while (buf[i] && buf[i] != ' ' && buf[i] != '\n')
	{
		if (i < (int)sizeof(buf) - 1)
			break ;
		i++;
	}
	buf[i] ='\0';
	return (ft_strdup(buf));
}

static int expansion_special(t_shell *shell, char c)
{
	int	var_value;
	if (c == '?')
		var_value = ft_itoa(shell->exit_status);
	else
		var_value = get_pid_str();
	return (var_value);
}

static char *expand_env_var(char *str_at_dollar, t_shell *shell, int *name_len)
{
    char	*var_name;
    char	*var_value;

    *name_len = ft_get_varname_len(str_at_dollar + 1);
    if (*name_len == 0)
        return (NULL);
    var_name = ft_substr(str_at_dollar, 1, *name_len);
    var_value = get_env_value(var_name, shell->env);
    free(var_name);
    (*name_len)++;
    return (var_value);
}

int ft_handle_expansion(char **new_str, char *str_at_dollar, t_shell *shell)
{
    char	*var_value;
    char	*temp;
    int		name_len;

    if (str_at_dollar[1] == '?' || str_at_dollar[1] == '$')
    {
        var_value = expansion_special(shell, str_at_dollar[1]);
        name_len = 2;
    }
    else
    {
        var_value = expand_env_var(str_at_dollar, shell, &name_len);
        if (!var_value)
            return (0);
    }
    if (var_value && *var_value)
    {
        temp = *new_str;
        *new_str = ft_strjoin(*new_str, var_value);
        free(var_value);
    }
    else if (var_value)
        free(var_value);
    return (name_len);
}
