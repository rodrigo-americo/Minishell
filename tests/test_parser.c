/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
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

/* Test simple command parsing */
int test_parser_simple_command(void)
{
    char *input = "echo hello";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("parser_simple_command - NULL returned", 0);
        return (1);
    }

    int passed = (cmds->args != NULL &&
                  cmds->args[0] != NULL &&
                  strcmp(cmds->args[0], "echo") == 0 &&
                  cmds->args[1] != NULL &&
                  strcmp(cmds->args[1], "hello") == 0 &&
                  cmds->args[2] == NULL &&
                  cmds->redirs == NULL &&
                  cmds->next == NULL);

    print_test_result("parser_simple_command", passed);
    free_commands(cmds);
    return (!passed);
}

/* Test command with multiple arguments */
int test_parser_multiple_args(void)
{
    char *input = "ls -la /home";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("parser_multiple_args - NULL returned", 0);
        return (1);
    }

    int passed = (cmds->args != NULL &&
                  cmds->args[0] != NULL &&
                  strcmp(cmds->args[0], "ls") == 0 &&
                  cmds->args[1] != NULL &&
                  strcmp(cmds->args[1], "-la") == 0 &&
                  cmds->args[2] != NULL &&
                  strcmp(cmds->args[2], "/home") == 0 &&
                  cmds->args[3] == NULL);

    print_test_result("parser_multiple_args", passed);
    free_commands(cmds);
    return (!passed);
}

/* Test pipeline with two commands */
int test_parser_pipeline_two(void)
{
    char *input = "ls | wc";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("parser_pipeline_two - NULL returned", 0);
        return (1);
    }

    int passed = (cmds->args != NULL &&
                  strcmp(cmds->args[0], "ls") == 0 &&
                  cmds->next != NULL &&
                  cmds->next->args != NULL &&
                  strcmp(cmds->next->args[0], "wc") == 0 &&
                  cmds->next->next == NULL);

    print_test_result("parser_pipeline_two", passed);
    free_commands(cmds);
    return (!passed);
}

/* Test pipeline with three commands */
int test_parser_pipeline_three(void)
{
    char *input = "cat file.txt | grep test | wc -l";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("parser_pipeline_three - NULL returned", 0);
        return (1);
    }

    int passed = (cmds != NULL &&
                  cmds->next != NULL &&
                  cmds->next->next != NULL &&
                  cmds->next->next->next == NULL);

    if (passed)
    {
        passed = (strcmp(cmds->args[0], "cat") == 0 &&
                  strcmp(cmds->next->args[0], "grep") == 0 &&
                  strcmp(cmds->next->next->args[0], "wc") == 0);
    }

    print_test_result("parser_pipeline_three", passed);
    free_commands(cmds);
    return (!passed);
}

/* Test input redirection */
int test_parser_redir_in(void)
{
    char *input = "cat < input.txt";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("parser_redir_in - NULL returned", 0);
        return (1);
    }

    int passed = (cmds->args != NULL &&
                  strcmp(cmds->args[0], "cat") == 0 &&
                  cmds->redirs != NULL &&
                  cmds->redirs->type == REDIR_IN &&
                  strcmp(cmds->redirs->file, "input.txt") == 0);

    print_test_result("parser_redir_in", passed);
    free_commands(cmds);
    return (!passed);
}

/* Test output redirection */
int test_parser_redir_out(void)
{
    char *input = "echo hello > output.txt";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("parser_redir_out - NULL returned", 0);
        return (1);
    }

    int passed = (cmds->args != NULL &&
                  strcmp(cmds->args[0], "echo") == 0 &&
                  cmds->redirs != NULL &&
                  cmds->redirs->type == REDIR_OUT &&
                  strcmp(cmds->redirs->file, "output.txt") == 0);

    print_test_result("parser_redir_out", passed);
    free_commands(cmds);
    return (!passed);
}

/* Test append redirection */
int test_parser_redir_append(void)
{
    char *input = "echo hello >> output.txt";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("parser_redir_append - NULL returned", 0);
        return (1);
    }

    int passed = (cmds->args != NULL &&
                  strcmp(cmds->args[0], "echo") == 0 &&
                  cmds->redirs != NULL &&
                  cmds->redirs->type == REDIR_APPEND &&
                  strcmp(cmds->redirs->file, "output.txt") == 0);

    print_test_result("parser_redir_append", passed);
    free_commands(cmds);
    return (!passed);
}

/* Test heredoc */
int test_parser_heredoc(void)
{
    char *input = "cat << EOF";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("parser_heredoc - NULL returned", 0);
        return (1);
    }

    int passed = (cmds->args != NULL &&
                  strcmp(cmds->args[0], "cat") == 0 &&
                  cmds->redirs != NULL &&
                  cmds->redirs->type == REDIR_HEREDOC &&
                  strcmp(cmds->redirs->file, "EOF") == 0);

    print_test_result("parser_heredoc", passed);
    free_commands(cmds);
    return (!passed);
}

/* Test multiple redirections */
int test_parser_multiple_redirs(void)
{
    char *input = "cat < in.txt > out.txt";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("parser_multiple_redirs - NULL returned", 0);
        return (1);
    }

    int passed = (cmds->args != NULL &&
                  strcmp(cmds->args[0], "cat") == 0 &&
                  cmds->redirs != NULL &&
                  cmds->redirs->next != NULL);

    if (passed)
    {
        t_redir *r1 = cmds->redirs;
        t_redir *r2 = cmds->redirs->next;

        passed = (r1->type == REDIR_IN &&
                  strcmp(r1->file, "in.txt") == 0 &&
                  r2->type == REDIR_OUT &&
                  strcmp(r2->file, "out.txt") == 0);
    }

    print_test_result("parser_multiple_redirs", passed);
    free_commands(cmds);
    return (!passed);
}

/* Test command with redirection after argument */
int test_parser_redir_after_arg(void)
{
    char *input = "echo hello > output.txt world";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("parser_redir_after_arg - NULL returned", 0);
        return (1);
    }

    int passed = (cmds->args != NULL &&
                  strcmp(cmds->args[0], "echo") == 0 &&
                  strcmp(cmds->args[1], "hello") == 0 &&
                  strcmp(cmds->args[2], "world") == 0 &&
                  cmds->redirs != NULL);

    print_test_result("parser_redir_after_arg", passed);
    free_commands(cmds);
    return (!passed);
}

/* Test syntax error: pipe at start */
int test_parser_syntax_error_pipe_start(void)
{
    char *input = "| echo hello";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    int passed = (cmds == NULL);

    print_test_result("parser_syntax_error_pipe_start", passed);
    if (cmds)
        free_commands(cmds);
    return (!passed);
}

/* Test syntax error: pipe at end */
int test_parser_syntax_error_pipe_end(void)
{
    char *input = "echo hello |";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    int passed = (cmds == NULL);

    print_test_result("parser_syntax_error_pipe_end", passed);
    if (cmds)
        free_commands(cmds);
    return (!passed);
}

/* Test syntax error: double pipe */
int test_parser_syntax_error_double_pipe(void)
{
    char *input = "echo hello || world";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    int passed = (cmds == NULL);

    print_test_result("parser_syntax_error_double_pipe", passed);
    if (cmds)
        free_commands(cmds);
    return (!passed);
}

/* Test syntax error: redirection without file */
int test_parser_syntax_error_redir_no_file(void)
{
    char *input = "echo hello >";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    int passed = (cmds == NULL);

    print_test_result("parser_syntax_error_redir_no_file", passed);
    if (cmds)
        free_commands(cmds);
    return (!passed);
}

/* Test complex command */
int test_parser_complex(void)
{
    char *input = "cat < in.txt | grep test | wc -l > out.txt";
    t_list *tokens = lexer(input);
    t_cmd *cmds = parser(tokens);

    if (!cmds)
    {
        print_test_result("parser_complex - NULL returned", 0);
        return (1);
    }

    int passed = (cmds != NULL &&
                  cmds->next != NULL &&
                  cmds->next->next != NULL &&
                  cmds->redirs != NULL &&
                  cmds->next->next->redirs != NULL);

    print_test_result("parser_complex", passed);
    free_commands(cmds);
    return (!passed);
}

int main(void)
{
    printf("\n========== PARSER TESTS ==========\n\n");

    test_parser_simple_command();
    test_parser_multiple_args();
    test_parser_pipeline_two();
    test_parser_pipeline_three();
    test_parser_redir_in();
    test_parser_redir_out();
    test_parser_redir_append();
    test_parser_heredoc();
    test_parser_multiple_redirs();
    test_parser_redir_after_arg();
    test_parser_syntax_error_pipe_start();
    test_parser_syntax_error_pipe_end();
    test_parser_syntax_error_double_pipe();
    test_parser_syntax_error_redir_no_file();
    test_parser_complex();

    printf("\n=================================\n");
    printf("Total: %d tests\n", g_test_count);
    printf("Passed: %d\n", g_test_count - g_test_failed);
    printf("Failed: %d\n", g_test_failed);
    printf("=================================\n\n");

    return (g_test_failed > 0 ? 1 : 0);
}
