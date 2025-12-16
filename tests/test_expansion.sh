#!/bin/bash

# Test Suite for Variable Expansion in Minishell
# Tests $VAR, $?, and expansion in different contexts

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Counters
test_count=0
pass_count=0
fail_count=0

test_expansion() {
    test_count=$((test_count + 1))
    local cmd="$1"
    local description="$2"
    local expected="$3"

    echo -e "${YELLOW}Test $test_count: $description${NC}"
    echo "Command: $cmd"

    # Execute in minishell
    output=$(printf "%s\nexit\n" "$cmd" | timeout 2 ../minishell 2>&1 | grep -v "^minishell>" | grep -v "^Built-in" | grep -v "^exit$" | grep -v "command not found" | sed '/^$/d' | tr -d '\n' | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')

    if [ "$output" = "$expected" ]; then
        echo -e "${GREEN}✓ PASSED${NC}"
        pass_count=$((pass_count + 1))
    else
        echo -e "${RED}✗ FAILED${NC}"
        echo "  Expected: '$expected'"
        echo "  Got:      '$output'"
        fail_count=$((fail_count + 1))
    fi
    echo ""
}

echo "========================================="
echo "  VARIABLE EXPANSION TESTS - MINISHELL"
echo "========================================="
echo ""

# Check if minishell exists
if [ ! -f "../minishell" ]; then
    echo -e "${RED}Error: minishell executable not found!${NC}"
    echo "Please run 'make' in the parent directory first."
    exit 1
fi

echo "=== BASIC VARIABLE EXPANSION ==="
echo ""

# Test $USER expansion
test_expansion "/bin/echo \$USER" "Expand \$USER" "$USER"

# Test $HOME expansion
test_expansion "/bin/echo \$HOME" "Expand \$HOME" "$HOME"

# Test $PATH expansion (just check it expands to something)
echo -e "${YELLOW}Test $((test_count + 1)): Expand \$PATH (non-empty check)${NC}"
test_count=$((test_count + 1))
output=$(printf "/bin/echo \$PATH\nexit\n" | timeout 2 ../minishell 2>&1 | grep -v "^minishell>" | grep -v "^Built-in" | grep -v "^exit$" | sed '/^$/d')
if [ -n "$output" ]; then
    echo -e "${GREEN}✓ PASSED${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAILED${NC}"
    echo "  \$PATH should expand to something"
    fail_count=$((fail_count + 1))
fi
echo ""

echo "=== EXIT STATUS (\$?) ==="
echo ""

# Test $? after successful command
# Note: Since echo is a builtin stub, we use /bin/echo
test_expansion "/bin/echo hello
/bin/echo \$?" "Exit status after successful command" "hello0"

# Test $? after command not found
test_expansion "commandthatdoesnotexist123
/bin/echo \$?" "Exit status after command not found" "127"

echo "=== EXPANSION IN QUOTES ==="
echo ""

# Test expansion in double quotes
test_expansion "/bin/echo \"\$USER\"" "Expand in double quotes" "$USER"

# Test NO expansion in single quotes
test_expansion "/bin/echo '\$USER'" "No expansion in single quotes" "\$USER"

# Test mixed quotes
test_expansion "/bin/echo '\$USER' \"\$USER\"" "Mixed quotes" "\$USER $USER"

echo "=== UNDEFINED VARIABLES ==="
echo ""

# Test undefined variable (should expand to empty)
test_expansion "/bin/echo \$NONEXISTENT_VAR_12345" "Undefined variable" ""

# Test undefined variable with text
test_expansion "/bin/echo before\$NONEXISTENT_VAR_12345""after" "Undefined var with text" "beforeafter"

echo "=== MULTIPLE EXPANSIONS ==="
echo ""

# Test multiple variables in one command
test_expansion "/bin/echo \$USER \$HOME" "Multiple variables" "$USER $HOME"

# Test same variable multiple times
test_expansion "/bin/echo \$USER \$USER \$USER" "Same variable thrice" "$USER $USER $USER"

echo "=== SPECIAL CASES ==="
echo ""

# Test $$ (should expand to PID or similar)
echo -e "${YELLOW}Test $((test_count + 1)): \$\$ expansion (non-empty check)${NC}"
test_count=$((test_count + 1))
output=$(printf "/bin/echo \$\$\nexit\n" | timeout 2 ../minishell 2>&1 | grep -v "^minishell>" | grep -v "^Built-in" | grep -v "^exit$" | sed '/^$/d')
if [ -n "$output" ] && [ "$output" != "$$" ]; then
    echo -e "${GREEN}✓ PASSED${NC}"
    pass_count=$((pass_count + 1))
else
    echo -e "${RED}✗ FAILED${NC}"
    echo "  \$\$ should expand to process ID"
    fail_count=$((fail_count + 1))
fi
echo ""

# Test lone $ (should print literal $)
test_expansion "/bin/echo \$" "Lone dollar sign" "\$"

# Test $followed by non-alphanumeric
test_expansion "/bin/echo \$@" "Dollar with @ (should expand or print)" "\$@"

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