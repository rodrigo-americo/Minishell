#!/bin/bash

# Test Suite for Logical Operators (&& and ||) in Minishell Bonus
# Tests AND, OR operators with various combinations

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/../utils/test_helpers.sh"

# Initialize test counters
init_tests

# Check if minishell exists
if ! check_minishell; then
    exit 1
fi

print_test_header "LOGICAL OPERATORS (&&, ||) - MINISHELL BONUS"

# ============================================
# NORMAL CASES - AND Operator
# ============================================
print_category "NORMAL CASES - AND OPERATOR (&&)"

run_test "true && echo success" \
    "AND: both commands succeed"

run_test "echo first && echo second" \
    "AND: chain two echo commands"

run_test "/bin/ls / >/dev/null && echo ls_worked" \
    "AND: command with path succeeds"

run_test "false && echo should_not_print" \
    "AND: first command fails"

run_test "exit 1 && echo should_not_print" \
    "AND: explicit exit failure"

run_test "true && true && echo third" \
    "AND: chain of three"

run_test "true && true && true && echo fourth" \
    "AND: chain of four"

# ============================================
# NORMAL CASES - OR Operator
# ============================================
print_category "NORMAL CASES - OR OPERATOR (||)"

run_test "false || echo fallback" \
    "OR: first command fails, second runs"

run_test "exit 1 || echo recovered" \
    "OR: explicit exit failure triggers OR"

run_test "true || echo should_not_print" \
    "OR: first command succeeds"

run_test "echo success || echo fallback" \
    "OR: successful echo doesn't trigger OR"

run_test "false || false || echo last_resort" \
    "OR: chain of three"

run_test "false || false || false || echo finally" \
    "OR: chain of four"

# ============================================
# NORMAL CASES - Mixed AND/OR
# ============================================
print_category "NORMAL CASES - MIXED AND/OR"

run_test "true && false || echo recovered" \
    "Mixed: AND fails, OR succeeds"

run_test "false || true && echo success" \
    "Mixed: OR succeeds, then AND"

run_test "true && echo A || echo B" \
    "Mixed: AND succeeds, OR skipped"

run_test "false && echo A || echo B" \
    "Mixed: AND fails, OR executes"

# ============================================
# EDGE CASES - Syntax Errors
# ============================================
print_category "EDGE CASES - SYNTAX ERRORS"

run_syntax_test "&&" \
    "Syntax error: AND without left operand"

run_syntax_test "|| echo test" \
    "Syntax error: OR without left operand"

run_syntax_test "echo test &&" \
    "Syntax error: AND without right operand"

run_syntax_test "echo test ||" \
    "Syntax error: OR without right operand"

run_syntax_test "&& &&" \
    "Syntax error: consecutive operators"

run_syntax_test "|| ||" \
    "Syntax error: consecutive OR operators"

# ============================================
# EDGE CASES - Exit Status
# ============================================
print_category "EDGE CASES - EXIT STATUS"

run_test "(exit 0) && echo zero" \
    "Exit status 0 triggers AND"

run_test "(exit 1) && echo should_not_print" \
    "Exit status 1 blocks AND"

run_test "(exit 42) && echo should_not_print" \
    "Exit status 42 blocks AND"

run_test "(exit 1) || echo non_zero" \
    "Exit status 1 triggers OR"

run_test "(exit 127) || echo command_not_found_status" \
    "Exit status 127 triggers OR"

# ============================================
# GO CRAZY - Long Chains
# ============================================
print_category "GO CRAZY - LONG CHAINS"

run_test "true && true && true && true && true && echo chain_5" \
    "Long AND chain (5 operators)"

run_test "true && true && true && true && true && true && true && true && true && true && echo chain_10" \
    "Long AND chain (10 operators)"

run_test "false || false || false || false || false || true && echo mixed_long" \
    "Long OR chain leading to AND"

run_test "true && true && false || echo recovered_from_chain" \
    "Long chain with recovery"

# ============================================
# GO CRAZY - With Other Features
# ============================================
print_category "GO CRAZY - WITH PIPES"

run_test "echo test | cat && echo pipe_and_success" \
    "Pipe with AND operator"

run_test "echo test | grep test && echo found" \
    "Pipe with grep and AND"

run_test "echo test | grep nonexistent || echo not_found" \
    "Pipe failure with OR"

run_test "echo data | cat | cat && echo multi_pipe_and" \
    "Multiple pipes with AND"

# ============================================
# GO CRAZY - With Redirections
# ============================================
print_category "GO CRAZY - WITH REDIRECTIONS"

run_test "echo test > /tmp/test_op.txt && cat /tmp/test_op.txt && rm /tmp/test_op.txt" \
    "Redirection with AND chain"

run_test "cat /nonexistent 2>/dev/null || echo file_not_found" \
    "Failed cat with error redirect and OR"

run_test "echo data > /tmp/data.txt && cat /tmp/data.txt || echo failed && rm /tmp/data.txt" \
    "Complex redirection with operators"

# ============================================
# GO CRAZY - Complex Precedence
# ============================================
print_category "GO CRAZY - COMPLEX PRECEDENCE"

run_test "false && echo A || echo B && echo C" \
    "Complex precedence: AND-OR-AND"

run_test "true || echo A && echo B || echo C" \
    "Complex precedence: OR-AND-OR"

run_test "true && true && false || true && echo final" \
    "Long mixed chain with precedence"

run_test "false || true && false || true && echo result" \
    "Alternating OR-AND chain"

# ============================================
# SUMMARY
# ============================================
print_final_summary

# Exit with failure if any tests failed
[ $fail_count -eq 0 ] && exit 0 || exit 1
