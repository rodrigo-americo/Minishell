#!/bin/bash

# Master Test Runner for Minishell Bonus
# Executes all bonus test suites and provides comprehensive reporting

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m' # No Color

# Global counters
total_suites=0
passed_suites=0
failed_suites=0
total_tests=0
total_passed=0
total_failed=0

# Array to store failed suites
declare -a failed_suite_names

# Function to run a test suite
run_test_suite() {
    local suite_file="$1"
    local suite_name="$2"

    total_suites=$((total_suites + 1))

    echo ""
    echo -e "${BOLD}${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BOLD}${CYAN}  Running: $suite_name${NC}"
    echo -e "${BOLD}${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""

    # Make executable if not already
    chmod +x "$suite_file" 2>/dev/null

    # Run the suite
    if bash "$suite_file"; then
        passed_suites=$((passed_suites + 1))
        echo -e "${GREEN}${BOLD}✓ Suite passed: $suite_name${NC}"
    else
        failed_suites=$((failed_suites + 1))
        failed_suite_names+=("$suite_name")
        echo -e "${RED}${BOLD}✗ Suite failed: $suite_name${NC}"
    fi
}

# Print master header
echo -e "${BOLD}${BLUE}"
echo "╔════════════════════════════════════════════════════════════════════════╗"
echo "║                                                                        ║"
echo "║              MINISHELL BONUS - EXHAUSTIVE TEST SUITE                  ║"
echo "║                                                                        ║"
echo "║  Testing: Operators (&&, ||), Subshells (), Wildcards (*),            ║"
echo "║          Precedence, Built-ins, Redirections, Combinations,           ║"
echo "║          and Stress Tests                                             ║"
echo "║                                                                        ║"
echo "╚════════════════════════════════════════════════════════════════════════╝"
echo -e "${NC}"

# Check if minishell exists
MINISHELL_PATH="$SCRIPT_DIR/../../minishell"
if [ ! -f "$MINISHELL_PATH" ]; then
    echo -e "${RED}${BOLD}Error: minishell not found at $MINISHELL_PATH${NC}"
    echo -e "${YELLOW}Please run 'make bonus' first${NC}"
    exit 1
fi

echo -e "${GREEN}✓ Found minishell at: $MINISHELL_PATH${NC}"
echo ""

# Start timer
start_time=$(date +%s)

# Run all test suites
run_test_suite "$SCRIPT_DIR/test_operators.sh" "Logical Operators (&&, ||)"
run_test_suite "$SCRIPT_DIR/test_subshells.sh" "Subshells ()"
run_test_suite "$SCRIPT_DIR/test_wildcards.sh" "Wildcards (*)"
run_test_suite "$SCRIPT_DIR/test_precedence.sh" "Operator Precedence"
run_test_suite "$SCRIPT_DIR/test_builtins_advanced.sh" "Advanced Built-ins"
run_test_suite "$SCRIPT_DIR/test_redirects_bonus.sh" "Redirections with Bonus Features"
run_test_suite "$SCRIPT_DIR/test_combinations.sh" "Complex Combinations (Go Crazy)"
run_test_suite "$SCRIPT_DIR/test_stress.sh" "Stress Tests"

# End timer
end_time=$(date +%s)
elapsed=$((end_time - start_time))

# Print final summary
echo ""
echo ""
echo -e "${BOLD}${BLUE}╔════════════════════════════════════════════════════════════════════════╗${NC}"
echo -e "${BOLD}${BLUE}║                         FINAL SUMMARY                                  ║${NC}"
echo -e "${BOLD}${BLUE}╚════════════════════════════════════════════════════════════════════════╝${NC}"
echo ""
echo -e "${BOLD}Test Execution Summary:${NC}"
echo -e "  Total Suites:        $total_suites"
echo -e "  ${GREEN}Passed Suites:${NC}       $passed_suites"
echo -e "  ${RED}Failed Suites:${NC}       $failed_suites"
echo ""
echo -e "  Execution Time:      ${elapsed}s"
echo ""

if [ $failed_suites -eq 0 ]; then
    echo -e "${GREEN}${BOLD}╔════════════════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}${BOLD}║                                                                        ║${NC}"
    echo -e "${GREEN}${BOLD}║                   🎉 ALL TEST SUITES PASSED! 🎉                        ║${NC}"
    echo -e "${GREEN}${BOLD}║                                                                        ║${NC}"
    echo -e "${GREEN}${BOLD}║              Your minishell bonus is working great!                    ║${NC}"
    echo -e "${GREEN}${BOLD}║                                                                        ║${NC}"
    echo -e "${GREEN}${BOLD}╚════════════════════════════════════════════════════════════════════════╝${NC}"
    echo ""
    exit 0
else
    percentage=$(( (passed_suites * 100) / total_suites ))
    echo -e "${YELLOW}${BOLD}╔════════════════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${YELLOW}${BOLD}║                                                                        ║${NC}"
    echo -e "${YELLOW}${BOLD}║                      SOME TESTS FAILED                                 ║${NC}"
    echo -e "${YELLOW}${BOLD}║                                                                        ║${NC}"
    echo -e "${YELLOW}${BOLD}║                    Pass Rate: ${percentage}%                                    ║${NC}"
    echo -e "${YELLOW}${BOLD}║                                                                        ║${NC}"
    echo -e "${YELLOW}${BOLD}╚════════════════════════════════════════════════════════════════════════╝${NC}"
    echo ""
    echo -e "${RED}${BOLD}Failed Test Suites:${NC}"
    for suite in "${failed_suite_names[@]}"; do
        echo -e "  ${RED}✗${NC} $suite"
    done
    echo ""
    echo -e "${YELLOW}Please review the test output above for details on which specific tests failed.${NC}"
    echo ""
    exit 1
fi
