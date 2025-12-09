#include "../includes/minishell.h"
#include <stdio.h>

static int test_token_node_and_list(void)
{
    t_list *head = NULL;
    t_list *node1;
    t_list *node2;
    t_list *node3;

    node1 = token_node_new("ls", TOKEN_WORD);
    node2 = token_node_new("|", TOKEN_PIPE);
    node3 = token_node_new("wc", TOKEN_WORD);
    if (!node1 || !node2 || !node3)
    {
        printf("[FAIL] token_node_new returned NULL\n");
        tokens_list_clear(&head);
        return (1);
    }
    tokens_list_add_back(&head, node1);
    tokens_list_add_back(&head, node2);
    tokens_list_add_back(&head, node3);

    if (ft_lstsize(head) != 3)
    {
        printf("[FAIL] expected list size 3, got %d\n", ft_lstsize(head));
        tokens_list_clear(&head);
        return (1);
    }

    // Verify values and types
    t_token *t0 = (t_token *)head->content;
    t_token *t1 = (t_token *)head->next->content;
    t_token *t2 = (t_token *)head->next->next->content;
    if (ft_strcmp(t0->value, "ls") != 0 || t0->type != TOKEN_WORD)
    {
        printf("[FAIL] first token mismatch\n");
        tokens_list_clear(&head);
        return (1);
    }
    if (ft_strcmp(t1->value, "|") != 0 || t1->type != TOKEN_PIPE)
    {
        printf("[FAIL] second token mismatch\n");
        tokens_list_clear(&head);
        return (1);
    }
    if (ft_strcmp(t2->value, "wc") != 0 || t2->type != TOKEN_WORD)
    {
        printf("[FAIL] third token mismatch\n");
        tokens_list_clear(&head);
        return (1);
    }

    tokens_list_clear(&head);
    if (head != NULL)
    {
        printf("[FAIL] tokens_list_clear did not set head to NULL\n");
        return (1);
    }
    return (0);
}

static int test_lexer_basic(void)
{
    char *input = "echo hello | wc";
    t_list *tokens = lexer(input);
    if (!tokens)
    {
        printf("[FAIL] lexer returned NULL\n");
        return (1);
    }
    if (ft_lstsize(tokens) < 3)
    {
        printf("[FAIL] lexer returned too few tokens: %d\n", ft_lstsize(tokens));
        tokens_list_clear(&tokens);
        return (1);
    }
    // Simple checks: first token is 'echo', second contains 'hello' or part
    t_token *t0 = (t_token *)tokens->content;
    if (ft_strcmp(t0->value, "echo") != 0)
    {
        printf("[FAIL] lexer first token expected 'echo', got '%s'\n", t0->value);
        tokens_list_clear(&tokens);
        return (1);
    }
    tokens_list_clear(&tokens);
    return (0);
}

int main(void)
{
    int failed = 0;

    printf("Running token/lexer tests...\n");
    failed += test_token_node_and_list();
    failed += test_lexer_basic();

    if (failed)
    {
        printf("Some tests failed (%d).\n", failed);
        return (1);
    }
    printf("All tests passed.\n");
    return (0);
}
