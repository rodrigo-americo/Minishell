#!/bin/bash

# Test Suite for Stress Tests in Minishell Bonus
# Tests limits, edge cases, and stress scenarios

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/../utils/test_helpers.sh"

# Initialize test counters
init_tests

# Check if minishell exists
if ! check_minishell; then
    exit 1
fi

print_test_header "STRESS TESTS - MINISHELL BONUS"

# ============================================
# STRESS 1 - Long Pipe Chains
# ============================================
print_category "STRESS 1 - LONG PIPE CHAINS"

run_test "echo test | cat | cat | cat | cat | cat" \
    "5 pipes"

run_test "echo test | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat" \
    "10 pipes"

run_test "echo data | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat" \
    "15 pipes"

run_test "echo long | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat" \
    "20 pipes"

# ============================================
# STRESS 2 - Deep Subshell Nesting
# ============================================
print_category "STRESS 2 - DEEP SUBSHELL NESTING"

run_test "((((echo four))))" \
    "4 levels of nesting"

run_test "(((((echo five)))))" \
    "5 levels of nesting"

run_test "((((((echo six))))))" \
    "6 levels of nesting"

run_test "(((((((echo seven)))))))" \
    "7 levels of nesting"

run_test "((((((((echo eight))))))))" \
    "8 levels of nesting"

run_test "(((((((((echo nine)))))))))" \
    "9 levels of nesting"

run_test "((((((((((echo ten))))))))))" \
    "10 levels of nesting"

# ============================================
# STRESS 3 - Long Operator Chains
# ============================================
print_category "STRESS 3 - LONG OPERATOR CHAINS"

run_test "true && true && true && true && true && echo chain_5" \
    "5 AND operators"

run_test "true && true && true && true && true && true && true && true && true && true && echo chain_10" \
    "10 AND operators"

run_test "false || false || false || false || false || true && echo or_chain_5" \
    "5 OR operators then AND"

run_test "true && true && true && false || true && true && echo mixed_chain" \
    "Mixed long chain"

run_test "true && true && true && true && true && true && true && true && true && true && true && true && true && true && true && echo chain_15" \
    "15 AND operators"

# ============================================
# STRESS 4 - Many Arguments
# ============================================
print_category "STRESS 4 - MANY ARGUMENTS"

run_test "echo a b c d e f g h i j" \
    "10 arguments"

run_test "echo 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20" \
    "20 arguments"

run_test "echo arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9 arg10 arg11 arg12 arg13 arg14 arg15 arg16 arg17 arg18 arg19 arg20 arg21 arg22 arg23 arg24 arg25" \
    "25 arguments"

# ============================================
# STRESS 5 - Long Command Lines
# ============================================
print_category "STRESS 5 - LONG COMMAND LINES"

run_test "echo this is a very long command with many many words to test the command line parsing capabilities of the minishell" \
    "Long echo command"

run_test "echo word word word word word word word word word word word word word word word word word word word word" \
    "Repeated words (20 times)"

run_test "true && echo A && echo B && echo C && echo D && echo E && echo F && echo G && echo H && echo I && echo J" \
    "Long AND chain with echoes"

# ============================================
# STRESS 6 - Many Variables
# ============================================
print_category "STRESS 6 - MANY VARIABLES"

run_test "export A=1 && export B=2 && export C=3 && export D=4 && export E=5 && echo \$A \$B \$C \$D \$E" \
    "5 exports and echo"

run_test "export V1=a && export V2=b && export V3=c && export V4=d && export V5=e && export V6=f && export V7=g && export V8=h && echo \$V1 \$V2 \$V3" \
    "8 exports"

run_test "export X1=1 && export X2=2 && export X3=3 && export X4=4 && export X5=5 && export X6=6 && export X7=7 && export X8=8 && export X9=9 && export X10=10 && echo \$X1 \$X10" \
    "10 exports"

# ============================================
# STRESS 7 - Nested Directory Operations
# ============================================
print_category "STRESS 7 - NESTED PATHS"

run_test "cd / && cd tmp && cd .. && cd tmp && pwd" \
    "Multiple cd operations"

run_test "cd / && pwd && cd tmp && pwd && cd / && pwd" \
    "cd with pwd tracking"

run_test "(cd / && (cd tmp && (cd / && pwd)))" \
    "Nested subshells with cd"

# ============================================
# STRESS 8 - Complex Precedence Chains
# ============================================
print_category "STRESS 8 - COMPLEX PRECEDENCE"

run_test "true && false || true && false || true && echo final" \
    "Long precedence chain"

run_test "false || true && false || true && false || true && echo result" \
    "Alternating OR-AND chain"

run_test "(true && true) || (false && false) || (true && true) && echo end" \
    "Subshells with operators"

run_test "true && (false || true) && (true || false) && echo done" \
    "Nested precedence"

# ============================================
# STRESS 9 - Many Subshells in Sequence
# ============================================
print_category "STRESS 9 - MANY SUBSHELLS"

run_test "(echo A) && (echo B) && (echo C) && (echo D) && (echo E)" \
    "5 subshells with ANDs"

run_test "(true) && (true) && (true) && (true) && (true) && echo success" \
    "5 true subshells"

run_test "((echo A)) && ((echo B)) && ((echo C))" \
    "3 double-nested subshells"

run_test "(((echo A))) && (((echo B))) && (((echo C)))" \
    "3 triple-nested subshells"

# ============================================
# STRESS 10 - Mixed Complexity
# ============================================
print_category "STRESS 10 - MIXED COMPLEXITY"

run_test "(echo test | cat | cat | cat) && (echo data | cat | cat) && echo done" \
    "Subshells with pipes and ANDs"

run_test "((((echo A | cat)))) && echo B" \
    "Quad nested pipe with AND"

run_test "true && true && (true && (true && (true && echo deep))) || echo fallback" \
    "Deep nesting with OR fallback"

run_test "(echo A && echo B && echo C) | cat | cat && echo piped" \
    "Subshell ANDs piped with AND"

run_test "((echo test | cat) && (echo data | cat)) || ((echo A | cat) && (echo B | cat))" \
    "Complex nested pipes with OR"

# ============================================
# STRESS 11 - Heredoc Stress
# ============================================
print_category "STRESS 11 - HEREDOC STRESS"

run_test "cat << EOF
line1
line2
line3
line4
line5
EOF" \
    "5-line heredoc"

run_test "cat << EOF | cat
line1
line2
line3
line4
line5
line6
line7
line8
line9
line10
EOF" \
    "10-line heredoc piped"

run_test "cat << EOF && echo after
heredoc line 1
heredoc line 2
heredoc line 3
EOF" \
    "Heredoc with AND"

# ============================================
# STRESS 12 - Exit Status Chains
# ============================================
print_category "STRESS 12 - EXIT STATUS CHAINS"

run_test "(exit 0) && (exit 0) && (exit 0) && echo all_zero" \
    "Chain of exit 0"

run_test "(exit 1) || (exit 2) || (exit 3) || echo exits" \
    "Chain of different exits"

run_test "(exit 42) || (exit 43) || (exit 44) || (exit 0) && echo recovered" \
    "Exit recovery chain"

# ============================================
# SUMMARY
# ============================================
print_final_summary

# Exit with failure if any tests failed
[ $fail_count -eq 0 ] && exit 0 || exit 1
