#!/bin/bash

# Oracle Testing Framework for Minishell Bonus
# Compares minishell behavior with bash (the oracle)

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Path to minishell executable
# Get the absolute path by going up from the utils directory
SCRIPT_DIR_ABS="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
MINISHELL_PATH="$(cd "$SCRIPT_DIR_ABS/../.." && pwd)/minishell"

# Filter minishell prompts and exit command from output
filter_minishell_output() {
    local original_cmd="$1"
    perl -e '
        my $cmd = shift;
        my $content = do { local $/; <> };

        # Remove all "minishell> " prompts
        $content =~ s/minishell> //g;
        # Remove continuation prompt
        $content =~ s/^> //mg;

        # Remove the echoed command (at the start only)
        my $quoted_cmd = quotemeta($cmd);
        $content =~ s/^$quoted_cmd\n//;

        # Remove "exit\n" patterns
        $content =~ s/exit\n//g;
        # Remove standalone "exit" at end
        $content =~ s/\nexit$//;

        # Clean up blank lines
        $content =~ s/\n\n+/\n/g;
        $content =~ s/^\n+//;
        $content =~ s/\n+$//;

        print $content;
    ' "$original_cmd"
}

# Filter bash prompts from output
filter_bash_output() {
    # Remove bash prompts and empty lines
    sed '/^$/d'
}

# Normalize output for comparison (trim whitespace, sort if needed)
normalize_output() {
    # Remove leading and trailing whitespace from each line, and empty lines
    sed -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//' -e '/^$/d'
}

# Execute command in bash (oracle)
execute_in_bash() {
    local cmd="$1"
    local test_dir="$2"

    (
        cd "$test_dir" 2>/dev/null || exit 1
        eval "$cmd" 2>&1
    )
}

# Execute command in minishell
execute_in_minishell() {
    local cmd="$1"
    local test_dir="$2"

    (
        cd "$test_dir" 2>/dev/null || exit 1
        # Capture both output and exit code
        local output
        local exit_code
        output=$(printf "%s\nexit\n" "$cmd" | timeout 5 "$MINISHELL_PATH" 2>&1)
        exit_code=$?
        echo "$output" | filter_minishell_output "$cmd"
        exit $exit_code
    )
}

# Compare outputs from bash and minishell
compare_outputs() {
    local bash_out="$1"
    local mini_out="$2"
    local bash_exit="$3"
    local mini_exit="$4"
    local test_name="$5"
    local ignore_output="${6:-no}"

    local passed=1
    local details=""

    # Compare exit codes (always checked)
    if [ "$bash_exit" -ne "$mini_exit" ]; then
        passed=0
        details+="\n  Exit code mismatch: bash=$bash_exit, minishell=$mini_exit"
    fi

    # Compare stdout (unless ignored)
    if [ "$ignore_output" != "yes" ]; then
        local bash_norm=$(echo "$bash_out" | normalize_output)
        local mini_norm=$(echo "$mini_out" | normalize_output)

        if [ "$bash_norm" != "$mini_norm" ]; then
            passed=0
            details+="\n  Output mismatch:"
            details+="\n    Bash: $bash_out"
            details+="\n    Mini: $mini_out"
        fi
    fi

    if [ $passed -eq 1 ]; then
        echo -e "${GREEN}✓${NC} $test_name"
        return 0
    else
        echo -e "${RED}✗${NC} $test_name"
        echo -e "$details"
        return 1
    fi
}

# Main oracle test function
oracle_test() {
    local cmd="$1"
    local test_name="$2"
    local options="${3:-}"

    # Create isolated test environment
    local test_dir=$(mktemp -d -t minishell_test.XXXXXX)

    # Execute in bash
    bash_output=$(execute_in_bash "$cmd" "$test_dir" 2>&1)
    bash_exit=$?

    # Execute in minishell
    mini_output=$(execute_in_minishell "$cmd" "$test_dir" 2>&1)
    mini_exit=$?

    # Compare results
    compare_outputs "$bash_output" "$mini_output" "$bash_exit" "$mini_exit" "$test_name" "$options"
    local result=$?

    # Cleanup
    rm -rf "$test_dir"

    return $result
}

# Test that expects a syntax error
expect_syntax_error() {
    local cmd="$1"
    local test_name="$2"

    local test_dir=$(mktemp -d -t minishell_test.XXXXXX)

    # Execute in minishell
    mini_output=$(execute_in_minishell "$cmd" "$test_dir" 2>&1)
    mini_exit=$?

    # Cleanup
    rm -rf "$test_dir"

    # Check if it failed (non-zero exit)
    if [ $mini_exit -ne 0 ]; then
        echo -e "${GREEN}✓${NC} $test_name (syntax error detected)"
        return 0
    else
        echo -e "${RED}✗${NC} $test_name (should have failed with syntax error)"
        return 1
    fi
}

# Oracle test with file comparison
oracle_test_files() {
    local cmd="$1"
    local test_name="$2"
    local files_to_compare="$3"

    # Create two test environments
    local bash_dir=$(mktemp -d -t bash_test.XXXXXX)
    local mini_dir=$(mktemp -d -t mini_test.XXXXXX)

    # Execute in bash
    bash_output=$(execute_in_bash "$cmd" "$bash_dir" 2>&1)
    bash_exit=$?

    # Execute in minishell
    mini_output=$(execute_in_minishell "$cmd" "$mini_dir" 2>&1)
    mini_exit=$?

    local passed=1
    local details=""

    # Compare exit codes
    if [ "$bash_exit" -ne "$mini_exit" ]; then
        passed=0
        details+="\n  Exit code mismatch: bash=$bash_exit, minishell=$mini_exit"
    fi

    # Compare files
    for file in $files_to_compare; do
        if [ -f "$bash_dir/$file" ] && [ -f "$mini_dir/$file" ]; then
            if ! diff -q "$bash_dir/$file" "$mini_dir/$file" >/dev/null 2>&1; then
                passed=0
                details+="\n  File $file differs"
            fi
        elif [ -f "$bash_dir/$file" ] || [ -f "$mini_dir/$file" ]; then
            passed=0
            details+="\n  File $file exists in only one environment"
        fi
    done

    # Cleanup
    rm -rf "$bash_dir" "$mini_dir"

    if [ $passed -eq 1 ]; then
        echo -e "${GREEN}✓${NC} $test_name"
        return 0
    else
        echo -e "${RED}✗${NC} $test_name"
        echo -e "$details"
        return 1
    fi
}

# Print test suite header
print_test_header() {
    local suite_name="$1"
    echo ""
    echo -e "${BLUE}=========================================${NC}"
    echo -e "${BLUE}  $suite_name${NC}"
    echo -e "${BLUE}=========================================${NC}"
    echo ""
}

# Print test category header
print_category() {
    local category="$1"
    echo ""
    echo -e "${YELLOW}=== $category ===${NC}"
    echo ""
}

# Print summary statistics
print_summary() {
    local passed="$1"
    local failed="$2"
    local total=$((passed + failed))

    echo ""
    echo -e "${BLUE}=========================================${NC}"
    echo -e "${BLUE}  SUMMARY${NC}"
    echo -e "${BLUE}=========================================${NC}"
    echo -e "Total tests: $total"
    echo -e "${GREEN}Passed: $passed${NC}"
    echo -e "${RED}Failed: $failed${NC}"

    if [ $failed -eq 0 ]; then
        echo -e "${GREEN}All tests passed!${NC}"
    else
        local percentage=$(( (passed * 100) / total ))
        echo -e "${YELLOW}Pass rate: ${percentage}%${NC}"
    fi
    echo ""
}
