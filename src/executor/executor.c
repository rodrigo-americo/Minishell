/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:00:00 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/14 10:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** execute_simple_command - Executa um comando simples (sem pipes)
**
** Algoritmo:
** 1. Valida cmd e cmd->args[0]
** 2. Se builtin: executa e retorna
** 3. Busca executável com find_command()
** 4. Fork + execve
** 5. Aguarda filho e retorna exit status
**
** @cmd: estrutura do comando a executar
** @shell: ponteiro para estrutura shell
**
** Return: Exit status do comando (0-255, ou 127 se não encontrado)
*/

/*
** executor - Ponto de entrada principal da execução
**
** Por enquanto executa apenas o primeiro comando (sem pipes).
**
** @cmds: lista encadeada de comandos
** @shell: ponteiro para estrutura shell
*/
