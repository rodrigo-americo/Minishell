#!/bin/bash

# Test Suite for Advanced Built-in Commands in Minishell Bonus
# Tests: echo, cd, pwd, export, unset, env, exit

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/../utils/test_helpers.sh"

# Initialize test counters
init_tests

# Check if minishell exists
if ! check_minishell; then
    exit 1
fi

print_test_header "ADVANCED BUILT-IN COMMANDS - MINISHELL BONUS"

# ============================================
# ECHO - Normal Cases
# ============================================
print_category "ECHO - NORMAL CASES"

run_test "echo hello" \
    "echo: simple text"

run_test "echo hello world" \
    "echo: multiple words"

run_test "echo -n test" \
    "echo: -n flag (no newline)"

run_test "echo -nnn test" \
    "echo: multiple n flags"

run_test "echo" \
    "echo: no arguments"

# ============================================
# ECHO - Edge Cases
# ============================================
print_category "ECHO - EDGE CASES"

run_test "echo -n -n -n test" \
    "echo: multiple -n flags separated"

run_test "echo -nnnnnnnn" \
    "echo: many n flags only"

run_test "echo '  spaces  '" \
    "echo: preserve spaces in quotes"

run_test "echo \"double quotes\"" \
    "echo: double quotes"

run_test "echo \$NONEXISTENT" \
    "echo: non-existent variable"

run_test "export VAR=value && echo \$VAR" \
    "echo: expand variable"

# ============================================
# PWD - Normal Cases
# ============================================
print_category "PWD - NORMAL CASES"

run_test "pwd" \
    "pwd: print working directory"

run_test "pwd | cat" \
    "pwd: piped to cat"

run_test "cd / && pwd" \
    "pwd: after cd to root"

run_test "cd /tmp && pwd && cd - >/dev/null && pwd" \
    "pwd: after cd and back"

# ============================================
# PWD - Edge Cases
# ============================================
print_category "PWD - EDGE CASES"

run_test "(cd /tmp && pwd)" \
    "pwd: in subshell doesn't affect parent"

run_test "pwd && pwd && pwd" \
    "pwd: multiple calls"

run_test "cd /tmp && pwd && cd /usr && pwd && cd / && pwd" \
    "pwd: after multiple cd commands"

# ============================================
# CD - Normal Cases
# ============================================
print_category "CD - NORMAL CASES"

run_test "cd / && pwd" \
    "cd: to root"

run_test "cd /tmp && pwd" \
    "cd: to /tmp"

run_test "cd /tmp && cd / && pwd" \
    "cd: change directories twice"

run_test "cd .. && pwd" \
    "cd: to parent directory"

# ============================================
# CD - Edge Cases
# ============================================
print_category "CD - EDGE CASES"

run_test "cd /nonexistent 2>&1" \
    "cd: non-existent directory (should error)"

run_test "cd /tmp && cd - >/dev/null && pwd" \
    "cd: with dash (OLDPWD)"

run_test "cd /tmp && cd - >/dev/null && cd - >/dev/null && pwd" \
    "cd: toggle with dash twice"

run_test "(cd /tmp && pwd) && pwd" \
    "cd: in subshell isolation"

run_test "cd /tmp && cd /usr && cd / && pwd" \
    "cd: multiple directory changes"

run_test "cd /../tmp && pwd" \
    "cd: with parent reference"

run_test "cd /./tmp && pwd" \
    "cd: with current directory reference"

# ============================================
# EXPORT - Normal Cases
# ============================================
print_category "EXPORT - NORMAL CASES"

run_test "export TESTVAR=hello && echo \$TESTVAR" \
    "export: set and echo variable"

run_test "export VAR1=a && export VAR2=b && echo \$VAR1 \$VAR2" \
    "export: multiple variables"

run_test "export EMPTY=" \
    "export: empty value"

run_test "export QUOTED=\"hello world\" && echo \$QUOTED" \
    "export: quoted value"

# ============================================
# EXPORT - Edge Cases
# ============================================
print_category "EXPORT - EDGE CASES"

run_test "export 123VAR=invalid 2>&1" \
    "export: invalid name starting with digit"

run_test "export =value 2>&1" \
    "export: missing variable name"

run_test "export VAR && echo \$VAR" \
    "export: without value"

run_test "(export SUBVAR=test && echo \$SUBVAR) && echo \$SUBVAR" \
    "export: in subshell doesn't affect parent"

run_test "export A=1 && export A=2 && echo \$A" \
    "export: overwrite variable"

# ============================================
# UNSET - Normal Cases
# ============================================
print_category "UNSET - NORMAL CASES"

run_test "export VAR=test && unset VAR && echo \$VAR" \
    "unset: remove variable"

run_test "export A=1 && export B=2 && unset A && echo \$A \$B" \
    "unset: remove one of multiple"

run_test "unset NONEXISTENT" \
    "unset: non-existent variable (should succeed silently)"

# ============================================
# UNSET - Edge Cases
# ============================================
print_category "UNSET - EDGE CASES"

run_test "export VAR=test && unset VAR && export VAR=new && echo \$VAR" \
    "unset: then re-export"

run_test "unset 123INVALID 2>&1" \
    "unset: invalid variable name"

run_test "(export VAR=test && unset VAR) && echo \$VAR" \
    "unset: in subshell doesn't affect parent"

# ============================================
# ENV - Normal Cases
# ============================================
print_category "ENV - NORMAL CASES"

run_test "export ENVTEST=value && env | grep ENVTEST" \
    "env: show exported variable"

run_test "env | grep -c '=' | grep -v '^0$'" \
    "env: has variables"

run_test "export A=1 && export B=2 && env | grep -E '^(A|B)=' | wc -l" \
    "env: multiple exported variables"

# ============================================
# ENV - Edge Cases
# ============================================
print_category "ENV - EDGE CASES"

run_test "env | cat | wc -l | grep -v '^0$'" \
    "env: piped through cat"

run_test "(export SUBENV=test && env | grep SUBENV)" \
    "env: in subshell shows subshell vars"

# ============================================
# EXIT - Normal Cases (in subshells)
# ============================================
print_category "EXIT - NORMAL CASES"

run_test "(exit 0) && echo \$?" \
    "exit: status 0"

run_test "(exit 1) || echo \$?" \
    "exit: status 1"

run_test "(exit 42) || echo exit_\$?" \
    "exit: status 42"

run_test "(exit 255) || echo exit_\$?" \
    "exit: status 255"

# ============================================
# EXIT - Edge Cases
# ============================================
print_category "EXIT - EDGE CASES"

run_test "(exit -1) || echo exit_\$?" \
    "exit: negative number"

run_test "(exit 256) || echo exit_\$?" \
    "exit: modulo 256 (should be 0)"

run_test "(exit 257) || echo exit_\$?" \
    "exit: modulo 256 (should be 1)"

run_test "(exit 1000) || echo exit_\$?" \
    "exit: large number"

# Note: These syntax error tests won't work in subshells
# They would terminate the whole script
# We test them differently by checking error messages

# ============================================
# BUILT-INS - With Operators
# ============================================
print_category "BUILT-INS - WITH OPERATORS"

run_test "cd /tmp && pwd && cd - >/dev/null" \
    "cd with AND operators"

run_test "export VAR=test && echo \$VAR || echo failed" \
    "export with AND/OR"

run_test "(cd /nonexistent 2>/dev/null) || echo cd_failed" \
    "cd fails, OR executes"

run_test "pwd && pwd && pwd" \
    "pwd chained with AND"

run_test "echo test && echo test2 || echo fallback" \
    "echo with AND/OR"

# ============================================
# BUILT-INS - With Pipes
# ============================================
print_category "BUILT-INS - WITH PIPES"

run_test "echo test | cat" \
    "echo piped to cat"

run_test "pwd | cat" \
    "pwd piped to cat"

run_test "env | grep PATH | cat" \
    "env piped through grep and cat"

run_test "echo hello | cat | cat | cat" \
    "echo through multiple pipes"

run_test "export VAR=test && echo \$VAR | cat" \
    "export then echo piped"

# ============================================
# BUILT-INS - With Redirections
# ============================================
print_category "BUILT-INS - WITH REDIRECTIONS"

run_test "echo test > /tmp/builtin_test.txt && cat /tmp/builtin_test.txt && rm /tmp/builtin_test.txt" \
    "echo with output redirection"

run_test "pwd > /tmp/pwd_out.txt && cat /tmp/pwd_out.txt && rm /tmp/pwd_out.txt" \
    "pwd with redirection"

run_test "env > /tmp/env_out.txt && grep -c '=' /tmp/env_out.txt && rm /tmp/env_out.txt" \
    "env with redirection"

# ============================================
# BUILT-INS - In Subshells
# ============================================
print_category "BUILT-INS - IN SUBSHELLS"

run_test "(echo subshell)" \
    "echo in subshell"

run_test "(cd /tmp) && pwd" \
    "cd in subshell doesn't affect parent"

run_test "(export VAR=sub) && echo \$VAR" \
    "export in subshell doesn't affect parent"

run_test "((cd / && pwd))" \
    "cd in nested subshell"

run_test "(pwd && cd /tmp && pwd)" \
    "multiple built-ins in subshell"

run_test "((export A=1 && echo \$A))" \
    "export in nested subshell"

# ============================================
# BUILT-INS - Complex Combinations
# ============================================
print_category "BUILT-INS - COMPLEX COMBINATIONS"

run_test "cd /tmp && export VAR=tmpdir && echo \$VAR && cd - >/dev/null" \
    "cd, export, echo, cd back"

run_test "export A=1 && export B=2 && export C=3 && echo \$A \$B \$C" \
    "multiple exports then echo"

run_test "(cd /tmp && pwd) && (cd /usr && pwd) && pwd" \
    "multiple subshells with cd and pwd"

run_test "echo start && (cd /tmp && pwd) && echo end" \
    "echo, subshell cd, echo"

run_test "export VAR=test && (echo \$VAR | cat) && unset VAR" \
    "export, subshell echo piped, unset"

# ============================================
# SUMMARY
# ============================================
print_final_summary

# Exit with failure if any tests failed
[ $fail_count -eq 0 ] && exit 0 || exit 1
