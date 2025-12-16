#!/bin/bash

# Master Test Runner for Minishell
# Runs all test suites and provides comprehensive summary

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
BOLD='\033[1m'
NC='\033[0m'

# Track overall results
total_suites=0
passed_suites=0
failed_suites=0

echo -e "${BOLD}=========================================${NC}"
echo -e "${BOLD}     MINISHELL - COMPREHENSIVE TEST SUITE${NC}"
echo -e "${BOLD}=========================================${NC}"
echo ""

# Check if minishell exists
if [ ! -f "../minishell" ]; then
    echo -e "${RED}Error: minishell executable not found!${NC}"
    echo "Please run 'make' in the parent directory first."
    exit 1
fi

echo -e "${BLUE}Minishell found. Starting tests...${NC}"
echo ""

# Function to run a test suite
run_suite() {
    local script="$1"
    local name="$2"

    total_suites=$((total_suites + 1))

    echo -e "${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BOLD}Running: $name${NC}"
    echo -e "${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""

    if [ ! -f "$script" ]; then
        echo -e "${RED}✗ Test script not found: $script${NC}"
        failed_suites=$((failed_suites + 1))
        return 1
    fi

    # Make executable
    chmod +x "$script"

    # Run the test
    if bash "$script"; then
        echo ""
        echo -e "${GREEN}✓ $name: ALL TESTS PASSED${NC}"
        passed_suites=$((passed_suites + 1))
        return 0
    else
        echo ""
        echo -e "${RED}✗ $name: SOME TESTS FAILED${NC}"
        failed_suites=$((failed_suites + 1))
        return 1
    fi
}

# Run all test suites
echo -e "${BOLD}Starting test execution...${NC}"
echo ""
sleep 1

run_suite "test_executor.sh" "Command Execution Tests"
echo ""

run_suite "test_pipes.sh" "Pipe Functionality Tests"
echo ""

run_suite "test_expansion.sh" "Variable Expansion Tests"
echo ""

# Final Summary
echo -e "${BOLD}=========================================${NC}"
echo -e "${BOLD}           FINAL SUMMARY${NC}"
echo -e "${BOLD}=========================================${NC}"
echo ""

echo "Total test suites: $total_suites"
echo -e "${GREEN}Passed: $passed_suites${NC}"

if [ $failed_suites -gt 0 ]; then
    echo -e "${RED}Failed: $failed_suites${NC}"
else
    echo "Failed: $failed_suites"
fi

# Calculate percentage
if [ $total_suites -gt 0 ]; then
    percentage=$((passed_suites * 100 / total_suites))
    echo "Success rate: $percentage%"
fi

echo ""

# Show test suite breakdown
echo -e "${BOLD}Test Suite Breakdown:${NC}"
echo "  - Command Execution Tests (PATH, absolute/relative paths, errors)"
echo "  - Pipe Functionality Tests (simple pipes, multiple pipes, edge cases)"
echo "  - Variable Expansion Tests (\$VAR, \$?, quotes)"

echo ""

# Final verdict
if [ $passed_suites -eq $total_suites ]; then
    echo -e "${GREEN}${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${GREEN}${BOLD}   🎉 ALL TEST SUITES PASSED! 🎉${NC}"
    echo -e "${GREEN}${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""
    echo -e "${GREEN}Your minishell implementation is working correctly!${NC}"
    echo ""
    exit 0
else
    echo -e "${YELLOW}${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${YELLOW}${BOLD}   ⚠️  SOME TESTS FAILED${NC}"
    echo -e "${YELLOW}${BOLD}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""
    echo -e "${YELLOW}Please review the failed tests above and fix the issues.${NC}"
    echo ""
    exit 1
fi