/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/14 10:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** env_to_array - Converte lista encadeada de env para array de strings
**
** Formato necessário para execve(): char *envp[]
** Cada string no formato "KEY=VALUE"
** Array terminado com NULL
**
** @env: lista encadeada de variáveis de ambiente
**
** Return: Array de strings NULL-terminated, ou NULL em erro
**
** Exemplo:
**   Input: env = {USER=john} -> {HOME=/home/john} -> NULL
**   Output: ["USER=john", "HOME=/home/john", NULL]
*/
