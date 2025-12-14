/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:53:02 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/02 15:02:49 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *create_env_node(char *key, char *value)
{
	
    // Aloca t_env
    // Copia key e value
    // Retorna o nó
}

t_env *create_env(char **envp)
{
    t_env *env;
    t_env *new;

    int    i;
	if (!*envp || envp[0] == NULL)
        return (NULL);
    env = malloc(sizeof(t_env));
    if (!env)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        new = create_env_node();
        if (!new)
        {
            //libera todos os nós já feito
            return (NULL);
        }
        i++;
    }
    return (env);
}
