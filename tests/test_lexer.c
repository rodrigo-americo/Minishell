/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
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

/* Test simple word tokenization */
int test_lexer_simple_word(void)
{
    char *input = "echo";
    t_list *tokens = lexer(input);

    if (!tokens)
    {
        print_test_result("lexer_simple_word - NULL returned", 0);
        return (1);
    }

    int size = ft_lstsize(tokens);
    t_token *tok = (t_token *)tokens->content;

    int passed = (size == 1 &&
                  tok->type == TOKEN_WORD &&
                  strcmp(tok->value, "echo") == 0);

    print_test_result("lexer_simple_word", passed);
    tokens_list_clear(&tokens);
    return (!passed);
}

/* Test multiple words */
int test_lexer_multiple_words(void)
{
    char *input = "echo hello world";
    t_list *tokens = lexer(input);

    if (!tokens)
    {
        print_test_result("lexer_multiple_words - NULL returned", 0);
        return (1);
    }

    int size = ft_lstsize(tokens);
    int passed = (size == 3);

    if (passed)
    {
        t_token *t1 = (t_token *)tokens->content;
        t_token *t2 = (t_token *)tokens->next->content;
        t_token *t3 = (t_token *)tokens->next->next->content;

        passed = (strcmp(t1->value, "echo") == 0 &&
                  strcmp(t2->value, "hello") == 0 &&
                  strcmp(t3->value, "world") == 0 &&
                  t1->type == TOKEN_WORD &&
                  t2->type == TOKEN_WORD &&
                  t3->type == TOKEN_WORD);
    }

    print_test_result("lexer_multiple_words", passed);
    tokens_list_clear(&tokens);
    return (!passed);
}

/* Test pipe operator */
int test_lexer_pipe(void)
{
    char *input = "ls | grep test";
    t_list *tokens = lexer(input);

    if (!tokens)
    {
        print_test_result("lexer_pipe - NULL returned", 0);
        return (1);
    }

    int size = ft_lstsize(tokens);
    int passed = (size == 4);

    if (passed)
    {
        t_token *t1 = (t_token *)tokens->content;
        t_token *t2 = (t_token *)tokens->next->content;
        t_token *t3 = (t_token *)tokens->next->next->content;
        t_token *t4 = (t_token *)tokens->next->next->next->content;

        passed = (t1->type == TOKEN_WORD &&
                  t2->type == TOKEN_PIPE &&
                  t3->type == TOKEN_WORD &&
                  t4->type == TOKEN_WORD &&
                  strcmp(t2->value, "|") == 0);
    }

    print_test_result("lexer_pipe", passed);
    tokens_list_clear(&tokens);
    return (!passed);
}

/* Test input redirection */
int test_lexer_redir_in(void)
{
    char *input = "cat < file.txt";
    t_list *tokens = lexer(input);

    if (!tokens)
    {
        print_test_result("lexer_redir_in - NULL returned", 0);
        return (1);
    }

    int size = ft_lstsize(tokens);
    int passed = (size == 3);

    if (passed)
    {
        t_token *t1 = (t_token *)tokens->content;
        t_token *t2 = (t_token *)tokens->next->content;
        t_token *t3 = (t_token *)tokens->next->next->content;

        passed = (t1->type == TOKEN_WORD &&
                  t2->type == TOKEN_REDIR_IN &&
                  t3->type == TOKEN_WORD &&
                  strcmp(t2->value, "<") == 0);
    }

    print_test_result("lexer_redir_in", passed);
    tokens_list_clear(&tokens);
    return (!passed);
}

/* Test output redirection */
int test_lexer_redir_out(void)
{
    char *input = "echo test > output.txt";
    t_list *tokens = lexer(input);

    if (!tokens)
    {
        print_test_result("lexer_redir_out - NULL returned", 0);
        return (1);
    }

    int size = ft_lstsize(tokens);
    int passed = (size == 4);

    if (passed)
    {
        t_list *node = tokens->next->next;
        t_token *tok = (t_token *)node->content;

        passed = (tok->type == TOKEN_REDIR_OUT &&
                  strcmp(tok->value, ">") == 0);
    }

    print_test_result("lexer_redir_out", passed);
    tokens_list_clear(&tokens);
    return (!passed);
}

/* Test append redirection */
int test_lexer_redir_append(void)
{
    char *input = "echo test >> output.txt";
    t_list *tokens = lexer(input);

    if (!tokens)
    {
        print_test_result("lexer_redir_append - NULL returned", 0);
        return (1);
    }

    int size = ft_lstsize(tokens);
    int passed = (size == 4);

    if (passed)
    {
        t_list *node = tokens->next->next;
        t_token *tok = (t_token *)node->content;

        passed = (tok->type == TOKEN_REDIR_APPEND &&
                  strcmp(tok->value, ">>") == 0);
    }

    print_test_result("lexer_redir_append", passed);
    tokens_list_clear(&tokens);
    return (!passed);
}

/* Test heredoc */
int test_lexer_heredoc(void)
{
    char *input = "cat << EOF";
    t_list *tokens = lexer(input);

    if (!tokens)
    {
        print_test_result("lexer_heredoc - NULL returned", 0);
        return (1);
    }

    int size = ft_lstsize(tokens);
    int passed = (size == 3);

    if (passed)
    {
        t_list *node = tokens->next;
        t_token *tok = (t_token *)node->content;

        passed = (tok->type == TOKEN_REDIR_HEREDOC &&
                  strcmp(tok->value, "<<") == 0);
    }

    print_test_result("lexer_heredoc", passed);
    tokens_list_clear(&tokens);
    return (!passed);
}

/* Test single quotes */
int test_lexer_single_quotes(void)
{
    char *input = "echo 'hello world'";
    t_list *tokens = lexer(input);

    if (!tokens)
    {
        print_test_result("lexer_single_quotes - NULL returned", 0);
        return (1);
    }

    int size = ft_lstsize(tokens);
    int passed = (size == 2);

    if (passed)
    {
        t_token *t2 = (t_token *)tokens->next->content;
        passed = (strcmp(t2->value, "'hello world'") == 0 &&
                  t2->type == TOKEN_WORD);
    }

    print_test_result("lexer_single_quotes", passed);
    tokens_list_clear(&tokens);
    return (!passed);
}

/* Test double quotes */
int test_lexer_double_quotes(void)
{
    char *input = "echo \"hello world\"";
    t_list *tokens = lexer(input);

    if (!tokens)
    {
        print_test_result("lexer_double_quotes - NULL returned", 0);
        return (1);
    }

    int size = ft_lstsize(tokens);
    int passed = (size == 2);

    if (passed)
    {
        t_token *t2 = (t_token *)tokens->next->content;
        passed = (strcmp(t2->value, "\"hello world\"") == 0 &&
                  t2->type == TOKEN_WORD);
    }

    print_test_result("lexer_double_quotes", passed);
    tokens_list_clear(&tokens);
    return (!passed);
}

/* Test unclosed quotes error */
int test_lexer_unclosed_quotes(void)
{
    char *input = "echo 'hello";
    t_list *tokens = lexer(input);

    int passed = (tokens == NULL);

    print_test_result("lexer_unclosed_quotes", passed);
    if (tokens)
        tokens_list_clear(&tokens);
    return (!passed);
}

/* Test whitespace handling */
int test_lexer_whitespace(void)
{
    char *input = "  echo   hello   world  ";
    t_list *tokens = lexer(input);

    if (!tokens)
    {
        print_test_result("lexer_whitespace - NULL returned", 0);
        return (1);
    }

    int size = ft_lstsize(tokens);
    int passed = (size == 3);

    print_test_result("lexer_whitespace", passed);
    tokens_list_clear(&tokens);
    return (!passed);
}

/* Test complex command */
int test_lexer_complex(void)
{
    char *input = "cat < in.txt | grep \"test\" | wc > out.txt";
    t_list *tokens = lexer(input);

    if (!tokens)
    {
        print_test_result("lexer_complex - NULL returned", 0);
        return (1);
    }

    int size = ft_lstsize(tokens);
    int passed = (size == 11);

    if (passed)
    {
        t_token *t2 = (t_token *)tokens->next->content;
        t_token *t4 = (t_token *)tokens->next->next->next->content;
        t_token *t8 = (t_token *)tokens->next->next->next->next->next->next->next->content;

        passed = (t2->type == TOKEN_REDIR_IN &&
                  t4->type == TOKEN_PIPE &&
                  t8->type == TOKEN_PIPE);
    }

    print_test_result("lexer_complex", passed);
    tokens_list_clear(&tokens);
    return (!passed);
}

/* Test empty input */
int test_lexer_empty(void)
{
    char *input = "";
    t_list *tokens = lexer(input);

    int passed = (tokens == NULL);

    print_test_result("lexer_empty", passed);
    if (tokens)
        tokens_list_clear(&tokens);
    return (!passed);
}

/* Test only whitespace */
int test_lexer_only_whitespace(void)
{
    char *input = "   \t  \t   ";
    t_list *tokens = lexer(input);

    int passed = (tokens == NULL);

    print_test_result("lexer_only_whitespace", passed);
    if (tokens)
        tokens_list_clear(&tokens);
    return (!passed);
}

int main(void)
{
    printf("\n========== LEXER TESTS ==========\n\n");

    test_lexer_simple_word();
    test_lexer_multiple_words();
    test_lexer_pipe();
    test_lexer_redir_in();
    test_lexer_redir_out();
    test_lexer_redir_append();
    test_lexer_heredoc();
    test_lexer_single_quotes();
    test_lexer_double_quotes();
    test_lexer_unclosed_quotes();
    test_lexer_whitespace();
    test_lexer_complex();
    test_lexer_empty();
    test_lexer_only_whitespace();

    printf("\n=================================\n");
    printf("Total: %d tests\n", g_test_count);
    printf("Passed: %d\n", g_test_count - g_test_failed);
    printf("Failed: %d\n", g_test_failed);
    printf("=================================\n\n");

    return (g_test_failed > 0 ? 1 : 0);
}
