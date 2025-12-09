/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
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

/* Test skip_whitespace function */
int test_skip_whitespace_spaces(void)
{
    char *input = "   hello";
    char *result = skip_whitespace(input);

    int passed = (strcmp(result, "hello") == 0);

    print_test_result("skip_whitespace_spaces", passed);
    return (!passed);
}

int test_skip_whitespace_tabs(void)
{
    char *input = "\t\thello";
    char *result = skip_whitespace(input);

    int passed = (strcmp(result, "hello") == 0);

    print_test_result("skip_whitespace_tabs", passed);
    return (!passed);
}

int test_skip_whitespace_mixed(void)
{
    char *input = " \t \t hello";
    char *result = skip_whitespace(input);

    int passed = (strcmp(result, "hello") == 0);

    print_test_result("skip_whitespace_mixed", passed);
    return (!passed);
}

int test_skip_whitespace_no_whitespace(void)
{
    char *input = "hello";
    char *result = skip_whitespace(input);

    int passed = (strcmp(result, "hello") == 0);

    print_test_result("skip_whitespace_no_whitespace", passed);
    return (!passed);
}

int test_skip_whitespace_empty(void)
{
    char *input = "";
    char *result = skip_whitespace(input);

    int passed = (strcmp(result, "") == 0);

    print_test_result("skip_whitespace_empty", passed);
    return (!passed);
}

/* Test is_separator function */
int test_is_separator_space(void)
{
    int passed = (is_separator(' ') == 1);

    print_test_result("is_separator_space", passed);
    return (!passed);
}

int test_is_separator_tab(void)
{
    int passed = (is_separator('\t') == 1);

    print_test_result("is_separator_tab", passed);
    return (!passed);
}

int test_is_separator_pipe(void)
{
    int passed = (is_separator('|') == 1);

    print_test_result("is_separator_pipe", passed);
    return (!passed);
}

int test_is_separator_less_than(void)
{
    int passed = (is_separator('<') == 1);

    print_test_result("is_separator_less_than", passed);
    return (!passed);
}

int test_is_separator_greater_than(void)
{
    int passed = (is_separator('>') == 1);

    print_test_result("is_separator_greater_than", passed);
    return (!passed);
}

int test_is_separator_null(void)
{
    int passed = (is_separator('\0') == 1);

    print_test_result("is_separator_null", passed);
    return (!passed);
}

int test_is_separator_regular_char(void)
{
    int passed = (is_separator('a') == 0);

    print_test_result("is_separator_regular_char", passed);
    return (!passed);
}

/* Test ft_add_to_array function */
int test_add_to_array_null_array(void)
{
    char **arr = NULL;
    char *new_str = ft_strdup("hello");

    arr = ft_add_to_array(arr, new_str);

    int passed = (arr != NULL &&
                  arr[0] != NULL &&
                  strcmp(arr[0], "hello") == 0 &&
                  arr[1] == NULL);

    print_test_result("add_to_array_null_array", passed);

    if (arr)
        free_array(arr);
    return (!passed);
}

int test_add_to_array_existing_array(void)
{
    char **arr = malloc(sizeof(char *) * 2);
    arr[0] = ft_strdup("first");
    arr[1] = NULL;

    char *new_str = ft_strdup("second");
    arr = ft_add_to_array(arr, new_str);

    int passed = (arr != NULL &&
                  arr[0] != NULL &&
                  arr[1] != NULL &&
                  strcmp(arr[0], "first") == 0 &&
                  strcmp(arr[1], "second") == 0 &&
                  arr[2] == NULL);

    print_test_result("add_to_array_existing_array", passed);

    if (arr)
        free_array(arr);
    return (!passed);
}

int test_add_to_array_null_string(void)
{
    char **arr = malloc(sizeof(char *) * 2);
    arr[0] = ft_strdup("first");
    arr[1] = NULL;

    char **original_arr = arr;
    arr = ft_add_to_array(arr, NULL);

    int passed = (arr == original_arr);

    print_test_result("add_to_array_null_string", passed);

    if (arr)
        free_array(arr);
    return (!passed);
}

/* Test create_redir function */
int test_create_redir_input(void)
{
    char *file = ft_strdup("input.txt");
    t_redir *redir = create_redir(file, TOKEN_REDIR_IN);

    int passed = (redir != NULL &&
                  redir->type == REDIR_IN &&
                  redir->file != NULL &&
                  strcmp(redir->file, "input.txt") == 0 &&
                  redir->next == NULL);

    print_test_result("create_redir_input", passed);

    if (redir)
    {
        if (redir->file)
            free(redir->file);
        free(redir);
    }
    return (!passed);
}

int test_create_redir_output(void)
{
    char *file = ft_strdup("output.txt");
    t_redir *redir = create_redir(file, TOKEN_REDIR_OUT);

    int passed = (redir != NULL &&
                  redir->type == REDIR_OUT &&
                  redir->file != NULL &&
                  strcmp(redir->file, "output.txt") == 0 &&
                  redir->next == NULL);

    print_test_result("create_redir_output", passed);

    if (redir)
    {
        if (redir->file)
            free(redir->file);
        free(redir);
    }
    return (!passed);
}

int test_create_redir_append(void)
{
    char *file = ft_strdup("append.txt");
    t_redir *redir = create_redir(file, TOKEN_REDIR_APPEND);

    int passed = (redir != NULL &&
                  redir->type == REDIR_APPEND &&
                  redir->file != NULL &&
                  strcmp(redir->file, "append.txt") == 0 &&
                  redir->next == NULL);

    print_test_result("create_redir_append", passed);

    if (redir)
    {
        if (redir->file)
            free(redir->file);
        free(redir);
    }
    return (!passed);
}

int test_create_redir_heredoc(void)
{
    char *file = ft_strdup("EOF");
    t_redir *redir = create_redir(file, TOKEN_REDIR_HEREDOC);

    int passed = (redir != NULL &&
                  redir->type == REDIR_HEREDOC &&
                  redir->file != NULL &&
                  strcmp(redir->file, "EOF") == 0 &&
                  redir->next == NULL);

    print_test_result("create_redir_heredoc", passed);

    if (redir)
    {
        if (redir->file)
            free(redir->file);
        free(redir);
    }
    return (!passed);
}

/* Test add_redir_to_end function */
int test_add_redir_to_end_empty_list(void)
{
    t_redir *head = NULL;
    t_redir *new_redir = create_redir(ft_strdup("file.txt"), TOKEN_REDIR_IN);

    add_redir_to_end(&head, new_redir);

    int passed = (head != NULL &&
                  head == new_redir &&
                  head->next == NULL);

    print_test_result("add_redir_to_end_empty_list", passed);

    if (head)
    {
        if (head->file)
            free(head->file);
        free(head);
    }
    return (!passed);
}

int test_add_redir_to_end_existing_list(void)
{
    t_redir *head = create_redir(ft_strdup("file1.txt"), TOKEN_REDIR_IN);
    t_redir *new_redir = create_redir(ft_strdup("file2.txt"), TOKEN_REDIR_OUT);

    add_redir_to_end(&head, new_redir);

    int passed = (head != NULL &&
                  head->next != NULL &&
                  head->next == new_redir &&
                  head->next->next == NULL);

    print_test_result("add_redir_to_end_existing_list", passed);

    if (head)
    {
        t_redir *tmp = head->next;
        if (head->file)
            free(head->file);
        free(head);
        if (tmp)
        {
            if (tmp->file)
                free(tmp->file);
            free(tmp);
        }
    }
    return (!passed);
}

int test_add_redir_to_end_null_redir(void)
{
    t_redir *head = create_redir(ft_strdup("file.txt"), TOKEN_REDIR_IN);
    t_redir *original_head = head;

    add_redir_to_end(&head, NULL);

    int passed = (head == original_head && head->next == NULL);

    print_test_result("add_redir_to_end_null_redir", passed);

    if (head)
    {
        if (head->file)
            free(head->file);
        free(head);
    }
    return (!passed);
}

/* Test create_token function */
int test_create_token_word(void)
{
    t_token *token = create_token("echo", TOKEN_WORD);

    int passed = (token != NULL &&
                  token->value != NULL &&
                  strcmp(token->value, "echo") == 0 &&
                  token->type == TOKEN_WORD);

    print_test_result("create_token_word", passed);

    if (token)
    {
        if (token->value)
            free(token->value);
        free(token);
    }
    return (!passed);
}

int test_create_token_pipe(void)
{
    t_token *token = create_token("|", TOKEN_PIPE);

    int passed = (token != NULL &&
                  token->value != NULL &&
                  strcmp(token->value, "|") == 0 &&
                  token->type == TOKEN_PIPE);

    print_test_result("create_token_pipe", passed);

    if (token)
    {
        if (token->value)
            free(token->value);
        free(token);
    }
    return (!passed);
}

int main(void)
{
    printf("\n========== UTILS TESTS ==========\n\n");

    printf("--- skip_whitespace ---\n");
    test_skip_whitespace_spaces();
    test_skip_whitespace_tabs();
    test_skip_whitespace_mixed();
    test_skip_whitespace_no_whitespace();
    test_skip_whitespace_empty();

    printf("\n--- is_separator ---\n");
    test_is_separator_space();
    test_is_separator_tab();
    test_is_separator_pipe();
    test_is_separator_less_than();
    test_is_separator_greater_than();
    test_is_separator_null();
    test_is_separator_regular_char();

    printf("\n--- ft_add_to_array ---\n");
    test_add_to_array_null_array();
    test_add_to_array_existing_array();
    test_add_to_array_null_string();

    printf("\n--- create_redir ---\n");
    test_create_redir_input();
    test_create_redir_output();
    test_create_redir_append();
    test_create_redir_heredoc();

    printf("\n--- add_redir_to_end ---\n");
    test_add_redir_to_end_empty_list();
    test_add_redir_to_end_existing_list();
    test_add_redir_to_end_null_redir();

    printf("\n--- create_token ---\n");
    test_create_token_word();
    test_create_token_pipe();

    printf("\n=================================\n");
    printf("Total: %d tests\n", g_test_count);
    printf("Passed: %d\n", g_test_count - g_test_failed);
    printf("Failed: %d\n", g_test_failed);
    printf("=================================\n\n");

    return (g_test_failed > 0 ? 1 : 0);
}
