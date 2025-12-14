/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/14 10:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** get_paths - Obtém array de diretórios do PATH
**
** Busca a variável PATH no ambiente, divide por ':' e retorna array.
**
** @shell: ponteiro para estrutura shell com env
**
** Return: Array de strings (paths) NULL-terminated, ou NULL se PATH não existe
*/
char **get_paths(t_shell *shell)
{
    char *path_value;
    char **paths;

    path_value = get_env_value("PATH", shell->env);
    if (!path_value)
        return (NULL);
    paths = ft_split(path_value, ':');
    free(path_value);
    return (paths);
}
/*
** find_command - Procura executável no PATH ou verifica caminho absoluto/relativo
**
** Se cmd contém '/': verifica se é executável diretamente
** Senão: procura em cada diretório do PATH
**
** @cmd: nome do comando ou caminho
** @shell: ponteiro para estrutura shell
**
** Return: Caminho completo do executável (alocado), ou NULL se não encontrado
*/
char	*find_command(char *cmd, t_shell *shell)
{

}
