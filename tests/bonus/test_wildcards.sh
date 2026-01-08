#!/bin/bash

# Test Suite for Wildcards (*) in Minishell Bonus
# Tests wildcard expansion with various patterns

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/../utils/test_helpers.sh"

# Initialize test counters
init_tests

# Check if minishell exists
if ! check_minishell; then
    exit 1
fi

# Setup fixture files
FIXTURE_DIR="$SCRIPT_DIR/../fixtures/files"
setup_test_fixtures "$FIXTURE_DIR"

print_test_header "WILDCARDS (*) - MINISHELL BONUS"

# ============================================
# NORMAL CASES - Simple Patterns
# ============================================
print_category "NORMAL CASES - SIMPLE PATTERNS"

run_test "cd $FIXTURE_DIR && echo *.txt" \
    "Match all .txt files"

run_test "cd $FIXTURE_DIR && echo *.c" \
    "Match all .c files"

run_test "cd $FIXTURE_DIR && echo *.md" \
    "Match all .md files"

run_test "cd $FIXTURE_DIR && echo file*.txt" \
    "Match files with prefix"

run_test "cd $FIXTURE_DIR && echo *1.txt" \
    "Match files with suffix pattern"

run_test "cd $FIXTURE_DIR && ls *.txt 2>&1 | wc -l" \
    "Count .txt files with ls"

# ============================================
# NORMAL CASES - No Matches
# ============================================
print_category "NORMAL CASES - NO MATCHES"

run_test "cd $FIXTURE_DIR && echo *.xyz" \
    "No match: should print literal pattern"

run_test "cd $FIXTURE_DIR && echo nonexistent*.txt" \
    "No match: with prefix"

run_test "cd $FIXTURE_DIR && echo *.nonexistent" \
    "No match: with extension"

# ============================================
# EDGE CASES - Wildcard Alone
# ============================================
print_category "EDGE CASES - WILDCARD PATTERNS"

run_test "cd $FIXTURE_DIR && echo *" \
    "Wildcard matches everything (non-hidden)"

run_test "cd $FIXTURE_DIR && echo * | grep -c file" \
    "Count matches with wildcard"

run_test "cd $FIXTURE_DIR && echo *.* | wc -w" \
    "Double extension pattern"

# ============================================
# EDGE CASES - Quoted Wildcards
# ============================================
print_category "EDGE CASES - QUOTED WILDCARDS"

run_test "cd $FIXTURE_DIR && echo '*.txt'" \
    "Single quoted: should not expand"

run_test "cd $FIXTURE_DIR && echo \"*.txt\"" \
    "Double quoted: should not expand"

run_test "cd $FIXTURE_DIR && echo \\*.txt" \
    "Escaped wildcard: should not expand"

# ============================================
# EDGE CASES - Multiple Wildcards
# ============================================
print_category "EDGE CASES - MULTIPLE WILDCARDS"

run_test "cd $FIXTURE_DIR && echo *.txt *.c" \
    "Two wildcard patterns"

run_test "cd $FIXTURE_DIR && echo *.txt *.md *.c" \
    "Three wildcard patterns"

run_test "cd $FIXTURE_DIR && echo file*.txt test*.c" \
    "Mixed wildcard patterns"

# ============================================
# EDGE CASES - Hidden Files
# ============================================
print_category "EDGE CASES - HIDDEN FILES"

run_test "cd $FIXTURE_DIR && echo .* | grep -v '^\\.\\. \\.$' | wc -w" \
    "Dotfiles pattern (complex handling)"

run_test "cd $FIXTURE_DIR && echo .hidden*" \
    "Match hidden files explicitly"

# ============================================
# GO CRAZY - Wildcards with Operators
# ============================================
print_category "GO CRAZY - WITH OPERATORS"

run_test "cd $FIXTURE_DIR && ls *.txt >/dev/null && echo found_txt || echo not_found" \
    "Wildcard with AND/OR"

run_test "cd $FIXTURE_DIR && echo *.txt >/dev/null && echo success" \
    "Wildcard with AND operator"

run_test "cd $FIXTURE_DIR && ls *.xyz 2>/dev/null || echo no_xyz_files" \
    "No match wildcard with OR"

run_test "cd $FIXTURE_DIR && (echo *.txt) && echo after_subshell" \
    "Wildcard in subshell"

# ============================================
# GO CRAZY - Wildcards with Pipes
# ============================================
print_category "GO CRAZY - WITH PIPES"

run_test "cd $FIXTURE_DIR && echo *.txt | wc -w" \
    "Wildcard output piped to wc"

run_test "cd $FIXTURE_DIR && ls *.c 2>&1 | cat" \
    "ls with wildcard piped to cat"

run_test "cd $FIXTURE_DIR && echo *.md | cat | cat" \
    "Wildcard through multiple pipes"

run_test "cd $FIXTURE_DIR && (echo *.txt | cat)" \
    "Wildcard in subshell with pipe"

# ============================================
# GO CRAZY - Wildcards with Redirections
# ============================================
print_category "GO CRAZY - WITH REDIRECTIONS"

run_test "cd $FIXTURE_DIR && cat *.md > /tmp/combined_md.txt && wc -l /tmp/combined_md.txt && rm /tmp/combined_md.txt" \
    "Cat wildcard files and redirect"

run_test "cd $FIXTURE_DIR && echo *.txt > /tmp/txt_list.txt && cat /tmp/txt_list.txt && rm /tmp/txt_list.txt" \
    "Echo wildcard to file"

run_test "cd $FIXTURE_DIR && ls *.c > /tmp/c_files.txt 2>&1 && cat /tmp/c_files.txt && rm /tmp/c_files.txt" \
    "ls wildcard with redirection"

# ============================================
# GO CRAZY - Nested Directories
# ============================================
print_category "GO CRAZY - NESTED PATTERNS"

run_test "cd $FIXTURE_DIR && echo */*.txt" \
    "Wildcard in subdirectory"

run_test "cd $FIXTURE_DIR && echo subdir/*" \
    "All files in subdirectory"

run_test "cd $FIXTURE_DIR && echo subdir/*.c" \
    "Specific pattern in subdirectory"

# ============================================
# GO CRAZY - Complex Patterns
# ============================================
print_category "GO CRAZY - COMPLEX PATTERNS"

run_test "cd $FIXTURE_DIR && echo test* | wc -w" \
    "Prefix pattern count"

run_test "cd $FIXTURE_DIR && echo *test* 2>/dev/null | wc -w" \
    "Infix pattern count"

run_test "cd $FIXTURE_DIR && echo *.txt *.c *.md | wc -w" \
    "All document types"

run_test "cd $FIXTURE_DIR && (echo *.txt && echo *.c) | wc -l" \
    "Multiple wildcard commands in subshell"

# ============================================
# GO CRAZY - Wildcards with Commands
# ============================================
print_category "GO CRAZY - WITH VARIOUS COMMANDS"

run_test "cd $FIXTURE_DIR && wc -l *.txt 2>&1 | tail -1" \
    "wc with wildcard"

run_test "cd $FIXTURE_DIR && cat *.md 2>&1 | grep '#' | wc -l" \
    "cat wildcard with grep"

run_test "cd $FIXTURE_DIR && ls -l *.c 2>&1 | wc -l" \
    "ls -l with wildcard"

# ============================================
# GO CRAZY - Edge Combinations
# ============================================
print_category "GO CRAZY - EDGE COMBINATIONS"

run_test "cd $FIXTURE_DIR && echo *.txt && echo *.c && echo *.md" \
    "Sequential wildcard echoes"

run_test "cd $FIXTURE_DIR && (echo *.txt) || echo no_files" \
    "Wildcard with OR operator"

run_test "cd $FIXTURE_DIR && echo *.txt | cat | cat | cat" \
    "Wildcard through many pipes"

run_test "cd $FIXTURE_DIR && true && echo *.c || echo failed" \
    "Wildcard in AND/OR chain"

# Cleanup fixtures
cleanup_test_fixtures "$FIXTURE_DIR"

# ============================================
# SUMMARY
# ============================================
print_final_summary

# Exit with failure if any tests failed
[ $fail_count -eq 0 ] && exit 0 || exit 1
