#!/bin/bash

# Test Suite for Complex Combinations in Minishell Bonus
# "GO CRAZY" - Kitchen sink tests combining ALL bonus features

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/../utils/test_helpers.sh"

# Initialize test counters
init_tests

# Check if minishell exists
if ! check_minishell; then
    exit 1
fi

# Setup fixtures for wildcard tests
FIXTURE_DIR="$SCRIPT_DIR/../fixtures/files"
setup_test_fixtures "$FIXTURE_DIR"

print_test_header "COMPLEX COMBINATIONS (GO CRAZY) - MINISHELL BONUS"

# ============================================
# CATEGORY 1 - Operators + Subshells + Pipes
# ============================================
print_category "CATEGORY 1 - OPERATORS + SUBSHELLS + PIPES"

run_test "(echo test | cat) && echo success" \
    "Subshell pipe with AND"

run_test "(echo test | grep test) && echo found || echo not_found" \
    "Subshell pipe with AND/OR"

run_test "((echo data | cat) && echo step2) || echo failed" \
    "Nested subshell pipe AND OR"

run_test "(echo A | cat) && (echo B | cat) && echo final" \
    "Two subshell pipes with ANDs"

run_test "(false | cat) || (echo recovered | cat)" \
    "Two subshell pipes with OR"

run_test "((echo test | cat | cat)) && echo piped_nested" \
    "Nested subshell with multiple pipes"

run_test "echo test | (cat && echo in_subshell)" \
    "Pipe into subshell with AND"

run_test "(echo data) | cat | cat && echo success" \
    "Subshell piped multiple times with AND"

# ============================================
# CATEGORY 2 - Operators + Redirections
# ============================================
print_category "CATEGORY 2 - OPERATORS + REDIRECTIONS"

run_test "echo test > /tmp/comb1.txt && cat /tmp/comb1.txt | cat && rm /tmp/comb1.txt" \
    "Redirect, AND, pipe"

run_test "(echo data > /tmp/comb2.txt) && cat /tmp/comb2.txt || echo failed && rm /tmp/comb2.txt 2>/dev/null" \
    "Subshell redirect with AND/OR"

run_test "echo A > /tmp/comb3.txt && echo B >> /tmp/comb3.txt && cat /tmp/comb3.txt && rm /tmp/comb3.txt" \
    "Multiple redirects with ANDs"

run_test "cat /nonexistent 2>/dev/null || echo error > /tmp/comb4.txt && cat /tmp/comb4.txt && rm /tmp/comb4.txt" \
    "OR with redirect"

run_test "(cat << EOF
line1
line2
EOF
) | grep line1 && echo found" \
    "Heredoc in subshell piped with AND"

# ============================================
# CATEGORY 3 - Wildcards + Operators
# ============================================
print_category "CATEGORY 3 - WILDCARDS + OPERATORS"

run_test "cd $FIXTURE_DIR && echo *.txt >/dev/null && echo found_txt" \
    "Wildcard with AND"

run_test "cd $FIXTURE_DIR && ls *.xyz 2>/dev/null || echo no_xyz" \
    "No-match wildcard with OR"

run_test "cd $FIXTURE_DIR && (echo *.txt) | wc -w" \
    "Wildcard in subshell piped"

run_test "cd $FIXTURE_DIR && echo *.txt && echo *.c || echo failed" \
    "Multiple wildcards with operators"

run_test "cd $FIXTURE_DIR && (ls *.txt 2>&1) && (ls *.c 2>&1)" \
    "Wildcards in two subshells with AND"

run_test "cd $FIXTURE_DIR && cat *.md >/dev/null 2>&1 && echo success" \
    "Cat wildcard with redirect and AND"

# ============================================
# CATEGORY 4 - Built-ins + All Features
# ============================================
print_category "CATEGORY 4 - BUILT-INS + ALL FEATURES"

run_test "(cd /tmp && pwd) && (cd /usr && pwd)" \
    "cd in subshells with AND"

run_test "export VAR=test && (echo \$VAR | cat) && echo \$VAR" \
    "export, subshell echo piped, echo"

run_test "(export SUBVAR=value && echo \$SUBVAR) | cat" \
    "export in subshell piped"

run_test "cd /tmp && pwd && export DIR=\$(pwd) && cd - >/dev/null && echo \$DIR" \
    "cd, pwd, export with command substitution"

run_test "echo test | cat && pwd && echo done" \
    "Pipe, AND, pwd, AND"

run_test "(cd / && pwd) || echo failed" \
    "cd pwd in subshell with OR"

run_test "export A=1 && export B=2 && (echo \$A \$B | cat)" \
    "Multiple exports, subshell echo piped"

# ============================================
# CATEGORY 5 - Deep Nesting Everything
# ============================================
print_category "CATEGORY 5 - DEEP NESTING"

run_test "(((echo nested)))" \
    "Triple nested subshell"

run_test "((echo a && echo b) && (echo c && echo d))" \
    "Nested subshells with ANDs"

run_test "(((echo test | cat)))" \
    "Triple nested with pipe"

run_test "((echo data | cat) && (echo more | cat))" \
    "Nested pairs with pipes"

run_test "(((echo A && echo B) || echo C))" \
    "Triple nested with AND/OR"

run_test "((((echo very_deep))))" \
    "Quad nested subshell"

# ============================================
# CATEGORY 6 - Precedence + Complexity
# ============================================
print_category "CATEGORY 6 - PRECEDENCE + COMPLEXITY"

run_test "(echo test | cat) && echo A || echo B && echo C" \
    "Subshell pipe with complex operators"

run_test "true && (echo A | cat) || (echo B | cat) && echo C" \
    "AND, subshell pipes, OR, AND"

run_test "false || (echo recovered | cat) && echo success" \
    "OR, subshell pipe, AND"

run_test "(true && true) || (false && echo no) && echo yes" \
    "Subshells with complex logic"

run_test "echo test | cat && (echo mid | cat) && echo end || echo failed" \
    "Pipe, AND, subshell pipe, AND, OR"

# ============================================
# CATEGORY 7 - Real-World-Like Complex Commands
# ============================================
print_category "CATEGORY 7 - REAL-WORLD SCENARIOS"

run_test "(cd /tmp && ls >/dev/null) && echo dir_ok || echo dir_failed" \
    "Check directory and list"

run_test "export PATH=/tmp && echo \$PATH | grep tmp && unset PATH" \
    "Export, echo piped, unset"

run_test "(cat /dev/null | cat) && echo empty_ok" \
    "Pipe /dev/null in subshell"

run_test "cd / && (cd tmp && pwd) && pwd" \
    "cd, subshell cd, pwd isolation"

run_test "echo start && (echo middle | cat | cat) && echo end" \
    "Echo, subshell multi-pipe, echo"

# ============================================
# CATEGORY 8 - Mixed Redirections + Pipes + Operators
# ============================================
print_category "CATEGORY 8 - REDIRECTIONS + PIPES + OPERATORS"

run_test "(echo data > /tmp/mix1.txt) && cat /tmp/mix1.txt | cat && rm /tmp/mix1.txt" \
    "Subshell redirect, AND, pipes"

run_test "echo test | cat > /tmp/mix2.txt && cat /tmp/mix2.txt && rm /tmp/mix2.txt" \
    "Pipe, redirect, AND"

run_test "(echo A && echo B) > /tmp/mix3.txt && cat /tmp/mix3.txt | wc -l && rm /tmp/mix3.txt" \
    "Subshell multi-cmd redirect, pipe"

run_test "cat << EOF | cat > /tmp/mix4.txt && cat /tmp/mix4.txt && rm /tmp/mix4.txt
heredoc data
EOF" \
    "Heredoc piped, redirected"

run_test "(cat << EOF
line1
line2
EOF
) > /tmp/mix5.txt && cat /tmp/mix5.txt && rm /tmp/mix5.txt" \
    "Heredoc in subshell redirected"

# ============================================
# CATEGORY 9 - Everything Together (Kitchen Sink)
# ============================================
print_category "CATEGORY 9 - KITCHEN SINK"

run_test "(export VAR=test && echo \$VAR | cat) && echo outside_\$VAR" \
    "Export in subshell, pipe, echo outside"

run_test "cd $FIXTURE_DIR && (echo *.txt | cat) && cd - >/dev/null" \
    "cd, wildcard in subshell piped, cd back"

run_test "(cd /tmp && echo *.txt 2>/dev/null | cat) || echo no_txt" \
    "Subshell cd wildcard pipe with OR"

run_test "((echo test > /tmp/sink1.txt)) && cat /tmp/sink1.txt | cat && rm /tmp/sink1.txt" \
    "Nested subshell redirect, pipes"

run_test "export A=1 && (export B=2 && echo \$A \$B | cat) && echo \$A \$B" \
    "Exports, nested export echo pipe, echo"

run_test "(cd /tmp && pwd > /tmp/sink2.txt) && cat /tmp/sink2.txt && rm /tmp/sink2.txt" \
    "Subshell cd pwd redirect"

run_test "true && (echo A | cat > /tmp/sink3.txt) && cat /tmp/sink3.txt || echo failed && rm /tmp/sink3.txt 2>/dev/null" \
    "AND, subshell pipe redirect, cat, OR, AND"

run_test "((echo data | cat) && (cat << EOF | cat
test
EOF
)) || echo failed" \
    "Nested: pipe AND heredoc pipe, OR"

# ============================================
# CATEGORY 10 - Extreme Complexity
# ============================================
print_category "CATEGORY 10 - EXTREME COMPLEXITY"

run_test "(((echo L3 | cat) && echo L2) && echo L1) && echo L0" \
    "Triple nested with pipes and ANDs"

run_test "((cd / && pwd) && (cd /tmp && pwd)) && pwd" \
    "Nested subshells with cds"

run_test "(export X=a && (export Y=b && echo \$X \$Y))" \
    "Nested exports"

run_test "echo start && ((echo mid | cat) && (echo end | cat)) || echo failed" \
    "Echo, nested subshells with pipes, OR"

run_test "(cd $FIXTURE_DIR && cat *.md 2>/dev/null | wc -l) && echo counted" \
    "Subshell cd cat wildcard pipe with AND"

run_test "((echo A > /tmp/ext1.txt) && (echo B > /tmp/ext2.txt)) && cat /tmp/ext1.txt /tmp/ext2.txt && rm /tmp/ext1.txt /tmp/ext2.txt" \
    "Nested redirects, AND, cat both"

run_test "(true && (true && (true && echo deep)))" \
    "Deep AND nesting"

run_test "((((echo test | cat | cat | cat))))" \
    "Quad nested with triple pipe"

# Cleanup fixtures
cleanup_test_fixtures "$FIXTURE_DIR"

# ============================================
# SUMMARY
# ============================================
print_final_summary

# Exit with failure if any tests failed
[ $fail_count -eq 0 ] && exit 0 || exit 1
