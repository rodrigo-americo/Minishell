/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test suite                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:00:00 by test              #+#    #+#             */
/*   Updated: 2025/12/08 00:00:00 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <string.h>

static int g_test_count = 0;
static int g_test_failed = 0;

void print_test_result(const char *test_name, int passed)
{
    g_test_count++;
    if (passed)
        printf("[✓] %s\n", test_name);
    else
    {
        printf("[✗] %s\n", test_name);
        g_test_failed++;
    }
}

/* Helper function to create a minimal shell structure */
t_shell *create_test_shell(void)
{
    t_shell *shell = malloc(sizeof(t_shell));
    if (!shell)
        return (NULL);

    shell->input = NULL;
    shell->tokens = NULL;
    shell->cmds = NULL;
    shell->env = NULL;
    shell->exit_status = 0;
    shell->stdin_backup = -1;
    shell->stdout_backup = -1;

    return (shell);
}

/* Helper to add environment variable */
void add_test_env(t_shell *shell, char *key, char *value)
{
    set_env_value(key, value, &shell->env);
}

/* Test expansion of simple variable */
int test_expander_simple_var(void)
{
    t_shell *shell = create_test_shell();
    if (!shell)
    {
        print_test_result("expander_simple_var - shell creation failed", 0);
        return (1);
    }

    add_test_env(shell, "USER", "testuser");

    char *input = "echo $USER";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("expander_simple_var - parsing failed", 0);
        free_env(shell->env);
        free(shell);
        return (1);
    }

    expander(cmds, shell);

    int passed = (cmds->args != NULL &&
                  cmds->args[1] != NULL &&
                  strcmp(cmds->args[1], "testuser") == 0);

    print_test_result("expander_simple_var", passed);

    free_commands(cmds);
    free_env(shell->env);
    free(shell);
    return (!passed);
}

/* Test expansion of exit status */
int test_expander_exit_status(void)
{
    t_shell *shell = create_test_shell();
    if (!shell)
    {
        print_test_result("expander_exit_status - shell creation failed", 0);
        return (1);
    }

    shell->exit_status = 42;

    char *input = "echo $?";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("expander_exit_status - parsing failed", 0);
        free(shell);
        return (1);
    }

    expander(cmds, shell);

    int passed = (cmds->args != NULL &&
                  cmds->args[1] != NULL &&
                  strcmp(cmds->args[1], "42") == 0);

    print_test_result("expander_exit_status", passed);

    free_commands(cmds);
    free(shell);
    return (!passed);
}

/* Test expansion in double quotes */
int test_expander_double_quotes(void)
{
    t_shell *shell = create_test_shell();
    if (!shell)
    {
        print_test_result("expander_double_quotes - shell creation failed", 0);
        return (1);
    }

    add_test_env(shell, "VAR", "value");

    char *input = "echo \"test $VAR here\"";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("expander_double_quotes - parsing failed", 0);
        free_env(shell->env);
        free(shell);
        return (1);
    }

    expander(cmds, shell);

    int passed = (cmds->args != NULL &&
                  cmds->args[1] != NULL &&
                  strcmp(cmds->args[1], "test value here") == 0);

    print_test_result("expander_double_quotes", passed);

    free_commands(cmds);
    free_env(shell->env);
    free(shell);
    return (!passed);
}

/* Test no expansion in single quotes */
int test_expander_single_quotes(void)
{
    t_shell *shell = create_test_shell();
    if (!shell)
    {
        print_test_result("expander_single_quotes - shell creation failed", 0);
        return (1);
    }

    add_test_env(shell, "VAR", "value");

    char *input = "echo '$VAR'";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("expander_single_quotes - parsing failed", 0);
        free_env(shell->env);
        free(shell);
        return (1);
    }

    expander(cmds, shell);

    int passed = (cmds->args != NULL &&
                  cmds->args[1] != NULL &&
                  strcmp(cmds->args[1], "$VAR") == 0);

    print_test_result("expander_single_quotes", passed);

    free_commands(cmds);
    free_env(shell->env);
    free(shell);
    return (!passed);
}

/* Test expansion of undefined variable */
int test_expander_undefined_var(void)
{
    t_shell *shell = create_test_shell();
    if (!shell)
    {
        print_test_result("expander_undefined_var - shell creation failed", 0);
        return (1);
    }

    char *input = "echo $UNDEFINED";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("expander_undefined_var - parsing failed", 0);
        free(shell);
        return (1);
    }

    expander(cmds, shell);

    int passed = (cmds->args != NULL &&
                  cmds->args[1] != NULL &&
                  strcmp(cmds->args[1], "") == 0);

    print_test_result("expander_undefined_var", passed);

    free_commands(cmds);
    free(shell);
    return (!passed);
}

/* Test multiple expansions */
int test_expander_multiple_vars(void)
{
    t_shell *shell = create_test_shell();
    if (!shell)
    {
        print_test_result("expander_multiple_vars - shell creation failed", 0);
        return (1);
    }

    add_test_env(shell, "VAR1", "hello");
    add_test_env(shell, "VAR2", "world");

    char *input = "echo $VAR1 $VAR2";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("expander_multiple_vars - parsing failed", 0);
        free_env(shell->env);
        free(shell);
        return (1);
    }

    expander(cmds, shell);

    int passed = (cmds->args != NULL &&
                  cmds->args[1] != NULL &&
                  cmds->args[2] != NULL &&
                  strcmp(cmds->args[1], "hello") == 0 &&
                  strcmp(cmds->args[2], "world") == 0);

    print_test_result("expander_multiple_vars", passed);

    free_commands(cmds);
    free_env(shell->env);
    free(shell);
    return (!passed);
}

/* Test expansion in redirections */
int test_expander_redir(void)
{
    t_shell *shell = create_test_shell();
    if (!shell)
    {
        print_test_result("expander_redir - shell creation failed", 0);
        return (1);
    }

    add_test_env(shell, "FILE", "output.txt");

    char *input = "echo hello > $FILE";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("expander_redir - parsing failed", 0);
        free_env(shell->env);
        free(shell);
        return (1);
    }

    expander(cmds, shell);

    int passed = (cmds->redirs != NULL &&
                  cmds->redirs->file != NULL &&
                  strcmp(cmds->redirs->file, "output.txt") == 0);

    print_test_result("expander_redir", passed);

    free_commands(cmds);
    free_env(shell->env);
    free(shell);
    return (!passed);
}

/* Test quote removal */
int test_expander_quote_removal(void)
{
    t_shell *shell = create_test_shell();
    if (!shell)
    {
        print_test_result("expander_quote_removal - shell creation failed", 0);
        return (1);
    }

    char *input = "echo \"hello\" 'world'";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("expander_quote_removal - parsing failed", 0);
        free(shell);
        return (1);
    }

    expander(cmds, shell);

    int passed = (cmds->args != NULL &&
                  cmds->args[1] != NULL &&
                  cmds->args[2] != NULL &&
                  strcmp(cmds->args[1], "hello") == 0 &&
                  strcmp(cmds->args[2], "world") == 0);

    print_test_result("expander_quote_removal", passed);

    free_commands(cmds);
    free(shell);
    return (!passed);
}

/* Test expansion with special characters */
int test_expander_special_chars(void)
{
    t_shell *shell = create_test_shell();
    if (!shell)
    {
        print_test_result("expander_special_chars - shell creation failed", 0);
        return (1);
    }

    add_test_env(shell, "PATH", "/usr/bin:/bin");

    char *input = "echo $PATH";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("expander_special_chars - parsing failed", 0);
        free_env(shell->env);
        free(shell);
        return (1);
    }

    expander(cmds, shell);

    int passed = (cmds->args != NULL &&
                  cmds->args[1] != NULL &&
                  strcmp(cmds->args[1], "/usr/bin:/bin") == 0);

    print_test_result("expander_special_chars", passed);

    free_commands(cmds);
    free_env(shell->env);
    free(shell);
    return (!passed);
}

/* Test variable followed by text */
int test_expander_var_with_text(void)
{
    t_shell *shell = create_test_shell();
    if (!shell)
    {
        print_test_result("expander_var_with_text - shell creation failed", 0);
        return (1);
    }

    add_test_env(shell, "VAR", "value");

    char *input = "echo ${VAR}text";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("expander_var_with_text - parsing failed", 0);
        free_env(shell->env);
        free(shell);
        return (1);
    }

    expander(cmds, shell);

    int passed = (cmds->args != NULL && cmds->args[1] != NULL);

    print_test_result("expander_var_with_text", passed);

    free_commands(cmds);
    free_env(shell->env);
    free(shell);
    return (!passed);
}

int main(void)
{
    printf("\n========== EXPANDER TESTS ==========\n\n");

    test_expander_simple_var();
    test_expander_exit_status();
    test_expander_double_quotes();
    test_expander_single_quotes();
    test_expander_undefined_var();
    test_expander_multiple_vars();
    test_expander_redir();
    test_expander_quote_removal();
    test_expander_special_chars();
    test_expander_var_with_text();

    printf("\n====================================\n");
    printf("Total: %d tests\n", g_test_count);
    printf("Passed: %d\n", g_test_count - g_test_failed);
    printf("Failed: %d\n", g_test_failed);
    printf("====================================\n\n");

    return (g_test_failed > 0 ? 1 : 0);
}
