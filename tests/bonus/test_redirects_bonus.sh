#!/bin/bash

# Test Suite for Redirections with Bonus Features in Minishell Bonus
# Tests redirections combined with operators, subshells, wildcards

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/../utils/test_helpers.sh"

# Initialize test counters
init_tests

# Check if minishell exists
if ! check_minishell; then
    exit 1
fi

print_test_header "REDIRECTIONS WITH BONUS FEATURES - MINISHELL BONUS"

# ============================================
# NORMAL CASES - Basic Redirections
# ============================================
print_category "NORMAL CASES - BASIC REDIRECTIONS"

run_test "echo test > /tmp/redir1.txt && cat /tmp/redir1.txt && rm /tmp/redir1.txt" \
    "Output redirection"

run_test "echo line1 > /tmp/redir2.txt && echo line2 >> /tmp/redir2.txt && cat /tmp/redir2.txt && rm /tmp/redir2.txt" \
    "Append redirection"

run_test "cat < /dev/null" \
    "Input redirection from /dev/null"

run_test "echo data > /tmp/redir3.txt && cat < /tmp/redir3.txt && rm /tmp/redir3.txt" \
    "Input redirection from file"

# ============================================
# REDIRECTIONS - With AND Operator
# ============================================
print_category "REDIRECTIONS - WITH AND OPERATOR"

run_test "echo test > /tmp/and1.txt && cat /tmp/and1.txt && rm /tmp/and1.txt" \
    "Redirect then AND cat"

run_test "echo data > /tmp/and2.txt && grep data /tmp/and2.txt && rm /tmp/and2.txt" \
    "Redirect then AND grep"

run_test "true && echo success > /tmp/and3.txt && cat /tmp/and3.txt && rm /tmp/and3.txt" \
    "AND then redirect"

run_test "echo test > /tmp/and4.txt && cat /tmp/and4.txt && echo done && rm /tmp/and4.txt" \
    "Redirect with multiple ANDs"

# ============================================
# REDIRECTIONS - With OR Operator
# ============================================
print_category "REDIRECTIONS - WITH OR OPERATOR"

run_test "cat /nonexistent 2>/dev/null || echo not_found" \
    "Failed cat with OR"

run_test "cat /nonexistent 2>/dev/null || echo error > /tmp/or1.txt && cat /tmp/or1.txt && rm /tmp/or1.txt" \
    "OR with redirect"

run_test "false || echo fallback > /tmp/or2.txt && cat /tmp/or2.txt && rm /tmp/or2.txt" \
    "False OR redirect"

# ============================================
# REDIRECTIONS - In Subshells
# ============================================
print_category "REDIRECTIONS - IN SUBSHELLS"

run_test "(echo subshell) > /tmp/sub1.txt && cat /tmp/sub1.txt && rm /tmp/sub1.txt" \
    "Subshell output redirected"

run_test "(echo line1 && echo line2) > /tmp/sub2.txt && cat /tmp/sub2.txt && rm /tmp/sub2.txt" \
    "Subshell with multiple outputs"

run_test "((echo nested)) > /tmp/sub3.txt && cat /tmp/sub3.txt && rm /tmp/sub3.txt" \
    "Nested subshell redirected"

run_test "(cat < /dev/null)" \
    "Subshell with input redirection"

# ============================================
# REDIRECTIONS - With Pipes
# ============================================
print_category "REDIRECTIONS - WITH PIPES"

run_test "echo test > /tmp/pipe1.txt && cat /tmp/pipe1.txt | cat && rm /tmp/pipe1.txt" \
    "Redirect then pipe"

run_test "echo test | cat > /tmp/pipe2.txt && cat /tmp/pipe2.txt && rm /tmp/pipe2.txt" \
    "Pipe then redirect"

run_test "cat < /dev/null | cat" \
    "Input redirect piped"

run_test "echo data | cat > /tmp/pipe3.txt && cat /tmp/pipe3.txt | cat && rm /tmp/pipe3.txt" \
    "Pipe, redirect, pipe"

# ============================================
# REDIRECTIONS - Multiple Per Command
# ============================================
print_category "REDIRECTIONS - MULTIPLE PER COMMAND"

run_test "echo test > /tmp/multi1.txt > /tmp/multi2.txt && cat /tmp/multi2.txt && rm /tmp/multi1.txt /tmp/multi2.txt 2>/dev/null" \
    "Multiple output redirects (last wins)"

run_test "echo data > /tmp/multi3.txt && cat < /tmp/multi3.txt > /tmp/multi4.txt && cat /tmp/multi4.txt && rm /tmp/multi3.txt /tmp/multi4.txt" \
    "Input and output redirect"

# ============================================
# HEREDOC - With Operators
# ============================================
print_category "HEREDOC - WITH OPERATORS"

run_test "cat << EOF && echo done
line1
line2
EOF" \
    "Heredoc with AND"

run_test "cat << EOF | wc -l
line1
line2
line3
EOF" \
    "Heredoc piped to wc"

run_test "cat << EOF | grep line2
line1
line2
line3
EOF" \
    "Heredoc piped to grep"

# ============================================
# GO CRAZY - Complex Combinations
# ============================================
print_category "GO CRAZY - COMPLEX COMBINATIONS"

run_test "(echo test > /tmp/crazy1.txt) && cat /tmp/crazy1.txt | cat && rm /tmp/crazy1.txt" \
    "Subshell redirect, AND, pipe"

run_test "echo data | cat > /tmp/crazy2.txt && (cat /tmp/crazy2.txt) && rm /tmp/crazy2.txt" \
    "Pipe, redirect, subshell cat"

run_test "true && (echo success > /tmp/crazy3.txt) && cat /tmp/crazy3.txt || echo failed && rm /tmp/crazy3.txt 2>/dev/null" \
    "AND, subshell redirect, OR"

run_test "(echo A && echo B) > /tmp/crazy4.txt && cat /tmp/crazy4.txt | wc -l && rm /tmp/crazy4.txt" \
    "Subshell multi-cmd redirect"

run_test "cat << EOF > /tmp/crazy5.txt && cat /tmp/crazy5.txt && rm /tmp/crazy5.txt
heredoc line 1
heredoc line 2
EOF" \
    "Heredoc with output redirect"

# ============================================
# GO CRAZY - With All Features
# ============================================
print_category "GO CRAZY - ALL FEATURES COMBINED"

run_test "((echo nested > /tmp/all1.txt)) && cat /tmp/all1.txt && rm /tmp/all1.txt" \
    "Nested subshell with redirect"

run_test "(echo test | cat) > /tmp/all2.txt && cat /tmp/all2.txt | cat && rm /tmp/all2.txt" \
    "Subshell with pipe, redirected"

run_test "true && (echo data) > /tmp/all3.txt && cat /tmp/all3.txt || echo failed && rm /tmp/all3.txt 2>/dev/null" \
    "Operators, subshell, redirect"

run_test "(cat << EOF
test data
EOF
) > /tmp/all4.txt && cat /tmp/all4.txt && rm /tmp/all4.txt" \
    "Heredoc in subshell redirected"

# ============================================
# SUMMARY
# ============================================
print_final_summary

# Exit with failure if any tests failed
[ $fail_count -eq 0 ] && exit 0 || exit 1
