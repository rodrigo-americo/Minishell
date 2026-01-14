/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:47:32 by rgregori          #+#    #+#             */
/*   Updated: 2026/01/03 00:00:00 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void handle_signal_status(t_shell *shell) {
  if (g_signal_received == SIGINT) {
    g_signal_received = 0;
    shell->exit_status = 130;
  }
}

static int get_input(t_shell *shell) {
  shell->input = read_with_continuation("minishell> ");
  if (!shell->input)
    return (0);
  if (*shell->input)
    add_history(shell->input);
  return (1);
}

static t_ast_node *parse_input(t_shell *shell) {
  t_list *tokens;
  t_ast_node *ast;

  tokens = lexer(shell->input);
  if (!tokens)
    return (NULL);
  ast = parser(tokens, shell);
  tokens_list_clear(&tokens);
  return (ast);
}

void main_loop(t_shell *shell) {
  while (1) {
	  if (!get_input(shell))
      break;
	handle_signal_status(shell);
    if (*shell->input) {
      shell->ast = parse_input(shell);
      if (shell->ast) {
        executor(shell->ast, shell);
        free_ast(shell->ast);
        shell->ast = NULL;
      } else
        shell->exit_status = 2;
    }
    free(shell->input);
    shell->input = NULL;
  }
  ft_putendl_fd("exit", 1);
}

int main(int argc, char **argv, char **envp) {
  t_shell *shell;
  int exit_code;

  (void)argc;
  (void)argv;
  setup_signals();
  shell = shell_init(envp);
  main_loop(shell);
  exit_code = shell->exit_status;
  rl_clear_history();
  free_env(shell->env);
  if (shell->stdin_backup != -1)
    close(shell->stdin_backup);
  if (shell->stdout_backup != -1)
    close(shell->stdout_backup);
  free(shell);
  return (exit_code);
}
