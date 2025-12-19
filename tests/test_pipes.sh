#!/bin/bash

# Script de testes para pipes no Minishell
# Execute: bash test_pipes.sh

echo "======================================"
echo "  TESTES DE PIPES - MINISHELL"
echo "======================================"
echo ""

# Cores para output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Função para executar teste
run_test() {
    local test_num=$1
    local description=$2
    local command=$3

    echo -e "${YELLOW}Teste $test_num:${NC} $description"
    echo "Comando: $command"
    echo ""

    # Executar no bash real
    echo -e "${GREEN}[BASH]${NC}"
    echo "$command" | bash 2>&1
    echo ""

    # Executar no minishell
    echo -e "${GREEN}[MINISHELL]${NC}"
    echo -e "$command\nexit" | ./minishell 2>&1 | grep -v "minishell>"
    echo ""
    echo "--------------------------------------"
    echo ""
}

# Compilar primeiro
echo "Compilando minishell..."
make > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${RED}Erro ao compilar!${NC}"
    exit 1
fi
echo -e "${GREEN}Compilado com sucesso!${NC}"
echo ""

# TESTES BÁSICOS DE PIPES

run_test 1 "Pipe simples com echo e cat" \
"echo hello | cat"

run_test 2 "Pipe com echo e wc" \
"echo hello world | wc -w"

run_test 3 "Pipe triplo: echo -> cat -> wc" \
"echo testing pipes | cat | wc -c"

run_test 4 "Built-in pwd com pipe" \
"pwd | cat"

run_test 5 "Built-in env com pipe e head" \
"env | head -3"

run_test 6 "Echo com -n e pipe" \
"echo -n no newline | cat"

run_test 7 "Múltiplos pipes (4 comandos)" \
"echo one two three | cat | cat | wc -w"

run_test 8 "Pipe com ls" \
"ls src | head -3"

run_test 9 "Pipe com grep" \
"echo -e 'line1\nline2\nline3' | grep line2"

run_test 10 "Echo e cat com sort" \
"echo -e 'zebra\napple\nbanana' | sort"

echo ""
echo "======================================"
echo "  TESTES CONCLUÍDOS"
echo "======================================"
