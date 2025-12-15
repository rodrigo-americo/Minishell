/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:54:24 by rgregori          #+#    #+#             */
/*   Updated: 2025/12/15 18:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Variável global para armazenar número do último sinal recebido
** Única variável global permitida pelo subject
*/
volatile sig_atomic_t	g_signal_received = 0;

/*
** signal_handler_interactive - Handler para sinais no modo interativo (prompt)
**
** SIGINT (Ctrl-C): Exibe nova linha e novo prompt
** Comportamento: readline é notificado, linha é limpa, prompt é redesenhado
*/
static void	signal_handler_interactive(int signum)
{
	g_signal_received = signum;
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
** signal_handler_executing - Handler para sinais durante execução de comandos
**
** SIGINT (Ctrl-C): Apenas registra o sinal, o processo filho será interrompido
** SIGQUIT (Ctrl-\): Apenas registra o sinal, imprime "Quit" no child
*/
static void	signal_handler_executing(int signum)
{
	g_signal_received = signum;
	if (signum == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (signum == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}

/*
** setup_signals_interactive - Configura sinais para modo interativo (prompt)
**
** SIGINT: Handler customizado (nova linha + novo prompt)
** SIGQUIT: Ignorado (SIG_IGN)
*/
void	setup_signals_interactive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = signal_handler_interactive;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("minishell: sigaction SIGINT");
		exit(1);
	}
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("minishell: sigaction SIGQUIT");
		exit(1);
	}
}

/*
** setup_signals_executing - Configura sinais durante execução de comandos
**
** SIGINT: Handler customizado (permite que filho receba sinal)
** SIGQUIT: Handler customizado (imprime "Quit")
**
** Esses handlers permitem que os processos filhos recebam os sinais,
** mas também atualizam a variável global para tracking
*/
void	setup_signals_executing(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = signal_handler_executing;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("minishell: sigaction SIGINT");
		exit(1);
	}
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sa_quit.sa_handler = signal_handler_executing;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("minishell: sigaction SIGQUIT");
		exit(1);
	}
}

/*
** setup_signals_child - Configura sinais para processos filhos
**
** Restaura handlers padrão (SIG_DFL) para que os filhos se comportem
** como programas normais (podem ser interrompidos por Ctrl-C, etc)
*/
void	setup_signals_child(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/*
** setup_signals - Wrapper para configurar sinais no modo interativo
**
** Chamada no início do programa (main)
*/
void	setup_signals(void)
{
	setup_signals_interactive();
}
