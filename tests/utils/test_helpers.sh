#!/bin/bash

# Test Helper Functions for Minishell Bonus Tests

# Source the oracle compare framework
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/oracle_compare.sh"

# Global test counters
test_count=0
pass_count=0
fail_count=0

# Initialize test counters
init_tests() {
    test_count=0
    pass_count=0
    fail_count=0
}

# Run a single oracle test and update counters
run_test() {
    local cmd="$1"
    local description="$2"
    local options="${3:-}"

    test_count=$((test_count + 1))

    if oracle_test "$cmd" "$description" "$options"; then
        pass_count=$((pass_count + 1))
        return 0
    else
        fail_count=$((fail_count + 1))
        return 1
    fi
}

# Run a syntax error test and update counters
run_syntax_test() {
    local cmd="$1"
    local description="$2"

    test_count=$((test_count + 1))

    if expect_syntax_error "$cmd" "$description"; then
        pass_count=$((pass_count + 1))
        return 0
    else
        fail_count=$((fail_count + 1))
        return 1
    fi
}

# Run a file comparison test and update counters
run_file_test() {
    local cmd="$1"
    local description="$2"
    local files="$3"

    test_count=$((test_count + 1))

    if oracle_test_files "$cmd" "$description" "$files"; then
        pass_count=$((pass_count + 1))
        return 0
    else
        fail_count=$((fail_count + 1))
        return 1
    fi
}

# Print final summary
print_final_summary() {
    print_summary "$pass_count" "$fail_count"
}

# Setup test environment with fixture files
setup_test_fixtures() {
    local fixture_dir="$1"
    mkdir -p "$fixture_dir"

    # Create test files for wildcards
    for i in {1..10}; do
        echo "test content $i" > "$fixture_dir/file${i}.txt"
    done

    for i in {1..5}; do
        echo "/* C file $i */" > "$fixture_dir/test${i}.c"
    done

    for i in {1..3}; do
        echo "# Markdown file $i" > "$fixture_dir/readme${i}.md"
    done

    # Create a subdirectory with nested files
    mkdir -p "$fixture_dir/subdir"
    echo "nested content" > "$fixture_dir/subdir/nested.txt"
    echo "nested C" > "$fixture_dir/subdir/nested.c"

    # Create a hidden file
    echo "hidden content" > "$fixture_dir/.hidden"
}

# Cleanup test fixtures
cleanup_test_fixtures() {
    local fixture_dir="$1"
    rm -rf "$fixture_dir"
}

# Check if minishell exists and is executable
check_minishell() {
    local minishell_path="$MINISHELL_PATH"

    if [ ! -f "$minishell_path" ]; then
        echo -e "${RED}Error: minishell not found at $minishell_path${NC}"
        echo "Please run 'make bonus' first"
        return 1
    fi

    if [ ! -x "$minishell_path" ]; then
        echo -e "${RED}Error: minishell is not executable${NC}"
        chmod +x "$minishell_path"
    fi

    return 0
}

# Create a temporary test directory
create_test_dir() {
    mktemp -d -t minishell_testdir.XXXXXX
}

# Export all helper functions
export -f init_tests
export -f run_test
export -f run_syntax_test
export -f run_file_test
export -f print_final_summary
export -f setup_test_fixtures
export -f cleanup_test_fixtures
export -f check_minishell
export -f create_test_dir
