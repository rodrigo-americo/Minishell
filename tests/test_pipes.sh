#!/bin/bash

# Test Suite for Pipes in Minishell
# Tests all variations of pipe functionality

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Counters
test_count=0
pass_count=0
fail_count=0

# Test function
test_pipe() {
    test_count=$((test_count + 1))
    local cmd="$1"
    local description="$2"
    local expected_contains="$3"  # Optional: text that should appear in output

    echo -e "${YELLOW}Test $test_count: $description${NC}"
    echo "Command: $cmd"

    # Execute in bash
    bash_output=$(bash -c "$cmd" 2>&1)
    bash_exit=$?

    # Execute in minishell
    minishell_output=$(printf "%s\nexit\n" "$cmd" | timeout 2 ../minishell 2>&1 | grep -v "^minishell>" | grep -v "^Built-in" | grep -v "^exit$" | sed '/^$/d')
    minishell_exit=0

    # Compare outputs (remove empty lines and trim whitespace)
    bash_clean=$(echo "$bash_output" | sed '/^$/d' | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
    minishell_clean=$(echo "$minishell_output" | sed '/^$/d' | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')

    # Check if output matches or contains expected text
    if [ -n "$expected_contains" ]; then
        if echo "$minishell_clean" | grep -q "$expected_contains"; then
            echo -e "${GREEN}✓ PASSED${NC}"
            pass_count=$((pass_count + 1))
        else
            echo -e "${RED}✗ FAILED${NC}"
            echo "  Expected to contain: '$expected_contains'"
            echo "  Got: '$minishell_clean'"
            fail_count=$((fail_count + 1))
        fi
    elif [ "$bash_clean" = "$minishell_clean" ]; then
        echo -e "${GREEN}✓ PASSED${NC}"
        pass_count=$((pass_count + 1))
    else
        echo -e "${RED}✗ FAILED${NC}"
        echo "  Bash output:      '$bash_clean'"
        echo "  Minishell output: '$minishell_clean'"
        fail_count=$((fail_count + 1))
    fi
    echo ""
}

echo "========================================="
echo "    PIPE TESTS - MINISHELL"
echo "========================================="
echo ""

# Check if minishell exists
if [ ! -f "../minishell" ]; then
    echo -e "${RED}Error: minishell executable not found!${NC}"
    echo "Please run 'make' in the parent directory first."
    exit 1
fi

echo "=== BASIC PIPES ==="
echo ""

test_pipe "ls | /usr/bin/head -1" "Simple pipe: ls to head"
test_pipe "/bin/echo hello | /bin/cat" "Echo to cat" "hello"
test_pipe "/bin/echo test123 | grep test" "Echo to grep (match)" "test123"
test_pipe "/bin/echo foo | grep bar" "Echo to grep (no match)" ""

echo "=== PIPES WITH ARGUMENTS ==="
echo ""

test_pipe "/bin/echo one two three | /usr/bin/wc -w" "Count words in pipe" "3"
test_pipe "/bin/echo HELLO | /usr/bin/tr 'A-Z' 'a-z'" "Case conversion" "hello"
test_pipe "ls -1 | /usr/bin/wc -l" "Count lines from ls"

echo "=== MULTIPLE PIPES (3+ commands) ==="
echo ""

test_pipe "/bin/echo hello | /bin/cat | /bin/cat" "3 commands: echo -> cat -> cat" "hello"
test_pipe "/usr/bin/printf 'abc\\ndef\\nghi\\n' | /usr/bin/sort" "3 commands with sort"
test_pipe "ls | /usr/bin/head -5 | /usr/bin/tail -1" "3 commands: ls -> head -> tail"

echo "=== PIPES WITH MULTIPLE ARGUMENTS ==="
echo ""

test_pipe "/bin/echo one two three four five | grep -o 'three'" "Grep with flag" "three"
test_pipe "/bin/echo line1 line2 line3 | /usr/bin/head -n 2" "Head with -n flag"

echo "=== EDGE CASES ==="
echo ""

# Test empty output through pipe
test_pipe "/bin/echo '' | /bin/cat" "Empty string through pipe"

# Test multiple spaces
test_pipe "/bin/echo 'a    b' | /bin/cat" "Multiple spaces preserved"

echo "========================================="
echo "           SUMMARY"
echo "========================================="
echo ""
echo "Total tests: $test_count"
echo -e "${GREEN}Passed: $pass_count${NC}"
if [ $fail_count -gt 0 ]; then
    echo -e "${RED}Failed: $fail_count${NC}"
else
    echo "Failed: $fail_count"
fi

# Calculate percentage
if [ $test_count -gt 0 ]; then
    percentage=$((pass_count * 100 / test_count))
    echo "Success rate: $percentage%"
fi

echo ""

if [ $pass_count -eq $test_count ]; then
    echo -e "${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
    exit 0
else
    echo -e "${YELLOW}Some tests failed. Please review above.${NC}"
    exit 1
fi
