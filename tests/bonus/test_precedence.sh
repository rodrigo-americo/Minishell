#!/bin/bash

# Test Suite for Operator Precedence in Minishell Bonus
# Tests precedence: OR < AND < PIPE

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/../utils/test_helpers.sh"

# Initialize test counters
init_tests

# Check if minishell exists
if ! check_minishell; then
    exit 1
fi

print_test_header "OPERATOR PRECEDENCE - MINISHELL BONUS"

# ============================================
# NORMAL CASES - OR vs AND
# ============================================
print_category "NORMAL CASES - OR vs AND (AND has higher precedence)"

run_test "true || false && echo and_wins" \
    "true || false && echo: AND binds tighter"

run_test "false && echo no || echo yes" \
    "false && echo || echo: evaluates left to right"

run_test "true && echo A || echo B" \
    "true && echo || echo: AND succeeds, OR skipped"

run_test "false || true && echo success" \
    "false || true && echo: OR then AND"

run_test "true || echo A && echo B" \
    "true || echo && echo: first OR succeeds"

# ============================================
# NORMAL CASES - AND vs PIPE
# ============================================
print_category "NORMAL CASES - AND/OR vs PIPE"

run_test "echo test | cat && echo success" \
    "Pipe then AND: pipe succeeds, AND executes"

run_test "echo test | grep test && echo found" \
    "Pipe with grep then AND"

run_test "echo test | grep nonexistent || echo not_found" \
    "Pipe fails, OR executes"

run_test "false | cat || echo pipe_failed" \
    "false piped, OR executes"

# ============================================
# NORMAL CASES - All Three Operators
# ============================================
print_category "NORMAL CASES - ALL THREE OPERATORS"

run_test "echo test | cat && echo yes || echo no" \
    "PIPE && echo || echo"

run_test "false | cat || echo A && echo B" \
    "PIPE || echo && echo"

run_test "echo data | grep data && echo found || echo not_found" \
    "Pipe with grep, AND, and OR"

run_test "true && echo test | cat || echo failed" \
    "AND then PIPE then OR"

# ============================================
# EDGE CASES - Parentheses Override Precedence
# ============================================
print_category "EDGE CASES - PARENTHESES OVERRIDE"

run_test "(true || false) && echo grouped" \
    "Parentheses force OR before AND"

run_test "true || (false && echo never)" \
    "Parentheses group AND, but OR short-circuits"

run_test "(false || true) && echo result" \
    "OR in parens, then AND"

run_test "(true && true) || echo fallback" \
    "AND in parens, then OR"

run_test "((true || false) && true) && echo final" \
    "Nested parentheses with operators"

# ============================================
# EDGE CASES - Complex Chains
# ============================================
print_category "EDGE CASES - COMPLEX CHAINS"

run_test "true && echo A || echo B && echo C" \
    "AND-OR-AND chain"

run_test "false || echo A && echo B || echo C" \
    "OR-AND-OR chain"

run_test "true && true && false || echo recovered" \
    "Multiple ANDs then OR"

run_test "false || false || true && echo final" \
    "Multiple ORs then AND"

# ============================================
# GO CRAZY - Deep Precedence Testing
# ============================================
print_category "GO CRAZY - DEEP PRECEDENCE"

run_test "false && echo A || true && echo B || echo C" \
    "Complex: AND-OR-AND-OR"

run_test "true || echo A && false || echo B && echo C" \
    "Complex: OR-AND-OR-AND"

run_test "echo test | cat && echo A || echo B && echo C" \
    "PIPE-AND-OR-AND"

run_test "false | cat || echo A && echo B | cat" \
    "PIPE-OR-AND-PIPE"

run_test "true && echo test | grep test && echo found || echo not_found" \
    "AND-PIPE-AND-OR chain"

# ============================================
# GO CRAZY - With Subshells
# ============================================
print_category "GO CRAZY - WITH SUBSHELLS"

run_test "(echo test | cat) && echo piped_in_subshell" \
    "Pipe in subshell with AND"

run_test "(false || echo A) && echo B" \
    "OR in subshell with outer AND"

run_test "(true && echo A | cat) || echo B" \
    "AND and PIPE in subshell with OR"

run_test "((echo test | cat) && echo A) || echo B" \
    "Nested subshell with PIPE-AND-OR"

run_test "(false || (true && echo nested))" \
    "Nested subshells with OR and AND"

run_test "((false || true) && (true | cat)) && echo final" \
    "Complex nested with all operators"

# ============================================
# GO CRAZY - Long Mixed Chains
# ============================================
print_category "GO CRAZY - LONG MIXED CHAINS"

run_test "true && true && false || true && echo result" \
    "Long: AND-AND-OR-AND"

run_test "false || false || true && true && echo success" \
    "Long: OR-OR-AND-AND"

run_test "echo a | cat && echo b | cat && echo c" \
    "Multiple PIPEs with ANDs"

run_test "echo test | grep test && echo A || echo B | cat" \
    "PIPE-AND-OR-PIPE"

run_test "true && (echo test | cat) && (echo data | cat) || echo failed" \
    "ANDs with piped subshells and OR"

# ============================================
# GO CRAZY - Precedence with Redirections
# ============================================
print_category "GO CRAZY - WITH REDIRECTIONS"

run_test "echo test > /tmp/prec1.txt && cat /tmp/prec1.txt | cat && rm /tmp/prec1.txt" \
    "Redirect-AND-PIPE-AND"

run_test "cat /nonexistent 2>/dev/null || echo failed | cat" \
    "Failed cat-OR-echo-PIPE"

run_test "(echo data > /tmp/prec2.txt) && cat /tmp/prec2.txt || echo failed && rm /tmp/prec2.txt 2>/dev/null" \
    "Complex redirect with operators"

# ============================================
# GO CRAZY - Edge Case Combinations
# ============================================
print_category "GO CRAZY - EDGE COMBINATIONS"

run_test "false && echo A || true && echo B || echo C && echo D" \
    "Very long mixed chain"

run_test "(true && true) || (false && echo no) || echo yes" \
    "Multiple subshells with ORs"

run_test "echo test | cat | cat && echo A || echo B | cat" \
    "Multiple pipes with AND-OR"

run_test "((true || false) && (echo test | cat)) && echo final" \
    "Nested logic with pipe"

run_test "true && (false || (true && (echo nested | cat)))" \
    "Deep nesting with all operators"

# ============================================
# GO CRAZY - Real-World-Like Scenarios
# ============================================
print_category "GO CRAZY - REAL-WORLD SCENARIOS"

run_test "ls / >/dev/null && echo found || echo not_found" \
    "Check directory exists"

run_test "echo test | grep test >/dev/null && echo match || echo no_match" \
    "Grep check pattern"

run_test "(cd /tmp && ls) >/dev/null || echo cd_failed" \
    "cd and ls in subshell"

run_test "true && echo start | cat && echo middle && echo end" \
    "Multi-step command chain"

# ============================================
# SUMMARY
# ============================================
print_final_summary

# Exit with failure if any tests failed
[ $fail_count -eq 0 ] && exit 0 || exit 1
