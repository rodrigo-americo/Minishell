#!/bin/bash

echo "=== TESTANDO REDIRECIONAMENTOS DO MINISHELL ==="
echo ""

cd "$(dirname "$0")"

# Limpa arquivos de teste anteriores
rm -f test_out.txt test_in.txt test_append.txt

echo "1. Testando redirecionamento de saída (>)"
echo "   Comando: echo hello world > test_out.txt"
echo 'echo hello world > test_out.txt' | ./minishell
if [ -f test_out.txt ]; then
    echo "   ✅ Arquivo criado!"
    echo "   Conteúdo: $(cat test_out.txt)"
else
    echo "   ❌ Arquivo NÃO foi criado"
fi
echo ""

echo "2. Testando redirecionamento de entrada (<)"
echo "test input" > test_in.txt
echo "   Comando: cat < test_in.txt"
echo 'cat < test_in.txt' | ./minishell
echo ""

echo "3. Testando append (>>)"
echo "linha 1" > test_append.txt
echo "   Comando: echo linha 2 >> test_append.txt"
echo 'echo linha 2 >> test_append.txt' | ./minishell
if [ -f test_append.txt ]; then
    echo "   ✅ Arquivo existe!"
    echo "   Conteúdo:"
    cat test_append.txt | sed 's/^/     /'
else
    echo "   ❌ Arquivo NÃO existe"
fi
echo ""

echo "4. Testando heredoc (<<)"
echo "   Comando: cat << EOF"
(echo 'cat << EOF'; echo 'linha 1'; echo 'linha 2'; echo 'EOF') | ./minishell
echo ""

echo "5. Testando com builtin (echo)"
echo "   Comando: echo teste > test_builtin.txt"
echo 'echo teste > test_builtin.txt' | ./minishell
if [ -f test_builtin.txt ]; then
    echo "   ✅ Arquivo criado!"
    echo "   Conteúdo: $(cat test_builtin.txt)"
    rm -f test_builtin.txt
else
    echo "   ❌ Arquivo NÃO foi criado"
fi
echo ""

# Limpa arquivos de teste
rm -f test_out.txt test_in.txt test_append.txt

echo "=== TESTES CONCLUÍDOS ==="
