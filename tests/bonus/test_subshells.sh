#!/bin/bash

# Test Suite for Subshells () in Minishell Bonus
# Tests subshell grouping, isolation, and nesting

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/../utils/test_helpers.sh"

# Initialize test counters
init_tests

# Check if minishell exists
if ! check_minishell; then
    exit 1
fi

print_test_header "SUBSHELLS () - MINISHELL BONUS"

# ============================================
# NORMAL CASES - Basic Subshells
# ============================================
print_category "NORMAL CASES - BASIC SUBSHELLS"

run_test "(echo test)" \
    "Simple subshell with echo"

run_test "(echo hello && echo world)" \
    "Subshell with AND operator"

run_test "(true)" \
    "Subshell with true command"

run_test "(false)" \
    "Subshell with false command"

run_test "(echo line1 && echo line2 && echo line3)" \
    "Subshell with multiple commands"

# ============================================
# NORMAL CASES - Variable Isolation
# ============================================
print_category "NORMAL CASES - VARIABLE ISOLATION"

run_test "VAR=outer && (VAR=inner && echo \$VAR) && echo \$VAR" \
    "Variable isolation in subshell"

run_test "export TESTVAR=before && (export TESTVAR=inside) && echo \$TESTVAR" \
    "Export in subshell doesn't affect parent"

run_test "(export SUBVAR=test && echo \$SUBVAR) && echo \$SUBVAR" \
    "Subshell variable not visible outside"

# ============================================
# NORMAL CASES - Directory Isolation
# ============================================
print_category "NORMAL CASES - DIRECTORY ISOLATION"

run_test "pwd && (cd /tmp && pwd) && pwd" \
    "cd in subshell doesn't affect parent"

run_test "(cd / && pwd)" \
    "cd to root in subshell"

run_test "(cd /tmp && cd /usr && pwd)" \
    "Multiple cd in subshell"

# ============================================
# NORMAL CASES - Exit Status
# ============================================
print_category "NORMAL CASES - EXIT STATUS PROPAGATION"

run_test "(exit 0) && echo \$?" \
    "Subshell exit 0 propagates"

run_test "(exit 42) || echo exit_was_\$?" \
    "Subshell exit 42 propagates"

run_test "(false) && echo should_not_print" \
    "Subshell false blocks AND"

run_test "(true) && echo success" \
    "Subshell true triggers AND"

# ============================================
# EDGE CASES - Empty and Malformed
# ============================================
print_category "EDGE CASES - EMPTY AND MALFORMED"

run_syntax_test "()" \
    "Syntax error: empty subshell"

run_syntax_test "(  )" \
    "Syntax error: empty subshell with spaces"

run_syntax_test "(   )" \
    "Syntax error: empty subshell with multiple spaces"

run_syntax_test "(echo test" \
    "Syntax error: unclosed left parenthesis"

run_syntax_test "echo test)" \
    "Syntax error: unmatched right parenthesis"

run_syntax_test "((echo test)" \
    "Syntax error: double open, single close"

run_syntax_test "(echo test))" \
    "Syntax error: single open, double close"

# ============================================
# EDGE CASES - Nested Subshells
# ============================================
print_category "EDGE CASES - NESTED SUBSHELLS"

run_test "((echo nested))" \
    "Double nested subshell"

run_test "(((echo triple)))" \
    "Triple nested subshell"

run_test "((((echo quad))))" \
    "Quad nested subshell"

run_test "((echo level2) && echo level1)" \
    "Nested subshell with AND"

run_test "((echo A && echo B) && (echo C && echo D))" \
    "Multiple nested subshells"

# ============================================
# GO CRAZY - Deep Nesting
# ============================================
print_category "GO CRAZY - DEEP NESTING"

run_test "(((((echo five_levels)))))" \
    "Five levels of nesting"

run_test "((((((echo six_levels))))))" \
    "Six levels of nesting"

run_test "(((((((((((echo eleven_levels)))))))))))" \
    "Eleven levels of nesting"

# ============================================
# GO CRAZY - Subshells with Operators
# ============================================
print_category "GO CRAZY - WITH OPERATORS"

run_test "(echo A && echo B) || echo C" \
    "Subshell AND with outer OR"

run_test "(false || echo recovered) && echo success" \
    "Subshell OR with outer AND"

run_test "(true && true) && (true && echo final)" \
    "Two subshells with AND"

run_test "(false && echo no) || (true && echo yes)" \
    "Two subshells with OR between"

run_test "(echo start && (echo nested && echo deep) && echo end)" \
    "Nested subshell within subshell with ANDs"

# ============================================
# GO CRAZY - Subshells with Pipes
# ============================================
print_category "GO CRAZY - WITH PIPES"

run_test "(echo test | cat)" \
    "Pipe inside subshell"

run_test "(echo test) | cat" \
    "Subshell piped to command"

run_test "echo test | (cat)" \
    "Pipe into subshell"

run_test "(echo A | cat) && (echo B | cat)" \
    "Two subshells with pipes and AND"

run_test "((echo data | cat) | cat)" \
    "Nested subshell with chained pipes"

run_test "(echo test | grep test | cat) && echo found" \
    "Multiple pipes in subshell with AND"

# ============================================
# GO CRAZY - Subshells with Redirections
# ============================================
print_category "GO CRAZY - WITH REDIRECTIONS"

run_test "(echo test) > /tmp/sub_test.txt && cat /tmp/sub_test.txt && rm /tmp/sub_test.txt" \
    "Subshell output redirected"

run_test "(echo line1 && echo line2) > /tmp/multi_line.txt && cat /tmp/multi_line.txt && rm /tmp/multi_line.txt" \
    "Subshell with multiple outputs redirected"

run_test "(cat < /dev/null)" \
    "Subshell with input redirection"

run_test "((echo data) > /tmp/nested_out.txt) && cat /tmp/nested_out.txt && rm /tmp/nested_out.txt" \
    "Nested subshell with redirection"

# ============================================
# GO CRAZY - Complex Combinations
# ============================================
print_category "GO CRAZY - COMPLEX COMBINATIONS"

run_test "(cd /tmp && pwd && cd / && pwd)" \
    "Multiple cd commands in subshell"

run_test "(export A=1 && export B=2 && echo \$A \$B)" \
    "Multiple exports in subshell"

run_test "((cd /tmp && pwd) && (cd /usr && pwd))" \
    "Two nested subshells with cd"

run_test "(false || true) && (true && echo result)" \
    "Complex logic in subshells"

run_test "((echo A | cat) && (echo B | cat)) || echo fallback" \
    "Nested subshells with pipes and OR"

run_test "(true && (true && (true && echo deep_logic)))" \
    "Deeply nested logical operations"

# ============================================
# SUMMARY
# ============================================
print_final_summary

# Exit with failure if any tests failed
[ $fail_count -eq 0 ] && exit 0 || exit 1
