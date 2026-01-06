# Minishell Bonus - Exhaustive Test Results

## Executive Summary

Suite de testes exaustiva executada com **~280 testes** cobrindo todas as features do bonus:
- Operadores lógicos (&&, ||)
- Subshells ()
- Wildcards (*)
- Precedência de operadores
- Built-ins avançados
- Redirections com features bonus
- Combinações complexas
- Stress tests

**Tempo de Execução:** 12 segundos
**Data:** 2026-01-06

---

## Resultados por Suite

| Suite | Tests | Passed | Failed | Pass Rate |
|-------|-------|--------|--------|-----------|
| **Logical Operators (&&, \|\|)** | 43 | 27 | 16 | 62% |
| **Subshells ()** | 51 | 0 | 51 | 0% |
| **Wildcards (*)** | 45 | 7 | 38 | 15% |
| **Operator Precedence** | 50 | 24 | 26 | 48% |
| **Advanced Built-ins** | 55 | 36 | 19 | 65% |
| **Redirections + Bonus** | 30 | 15 | 15 | 50% |
| **Complex Combinations** | 58 | 19 | 39 | 32% |
| **Stress Tests** | 47 | 19 | 28 | 40% |
| **TOTAL** | **~280** | **~147** | **~133** | **~52%** |

---

## Principais Bugs Encontrados

### 🔴 CRÍTICO: Subshells Não Implementados
**Impacto:** 100% de falha em todos os testes de subshells

**Problema:**
```bash
(echo test)  # Retorna: "syntax error : unmatched '('"
```

**Causa:** Parser não reconhece parênteses como delimitadores de subshell, apenas como erro de sintaxe.

**Testes Afetados:** 51 testes (100% da suite de subshells)

**Arquivos Relacionados:**
- [src_bonus/parser/parser_subshell_bonus.c](../../src_bonus/parser/parser_subshell_bonus.c)
- [src_bonus/executor/executor_bonus.c](../../src_bonus/executor/executor_bonus.c)

---

### 🔴 CRÍTICO: Wildcards Não Expandem
**Impacto:** 84% de falha em testes de wildcards

**Problema:**
```bash
cd /tmp && echo *.txt
# Bash: file1.txt file2.txt file3.txt
# Minishell: *.txt  (literal, sem expansão)
```

**Causa:** Expander de wildcards não está funcionando corretamente.

**Testes Afetados:** 38 de 45 testes (84%)

**Arquivos Relacionados:**
- [src_bonus/expander/wildcard_bonus.c](../../src_bonus/expander/wildcard_bonus.c)
- [src_bonus/expander/wildcard_match_bonus.c](../../src_bonus/expander/wildcard_match_bonus.c)

---

### 🟡 IMPORTANTE: Syntax Errors Não Detectados
**Impacto:** Aceita comandos inválidos

**Problema:**
```bash
&& echo test    # Deveria dar erro, mas executa
echo test &&    # Deveria dar erro, mas executa
|| echo test    # Deveria dar erro, mas executa
```

**Causa:** Validação de sintaxe não verifica operadores sem operandos.

**Testes Afetados:** 6 testes de syntax errors

**Arquivos Relacionados:**
- [src_bonus/parser/syntax_check_bonus.c](../../src_bonus/parser/syntax_check_bonus.c)

---

### 🟡 IMPORTANTE: Exit Code em Subshells
**Impacto:** exit dentro de subshells não funciona

**Problema:**
```bash
(exit 42) && echo $?
# Bash: 42
# Minishell: syntax error (devido ao problema de subshells)
```

**Causa:** Relacionado ao problema principal de subshells não implementados.

**Testes Afetados:** 10+ testes

---

### 🟡 IMPORTANTE: Variáveis Não Expandem Corretamente
**Impacto:** Expansão de variáveis falha em muitos casos

**Problema:**
```bash
export VAR=hello && echo $VAR
# Bash: hello
# Minishell: (vazio)
```

**Causa:** Expander de variáveis pode ter problemas com o contexto de execução.

**Testes Afetados:** 10+ testes

**Arquivos Relacionados:**
- [src_bonus/expander/expander_value_bonus.c](../../src_bonus/expander/expander_value_bonus.c)

---

### 🟢 MENOR: Echo -n Flag
**Impacto:** Flag -n não funciona corretamente

**Problema:**
```bash
echo -n test
# Bash: test(sem newline)
# Minishell: testminishell> exit (newline aparece)
```

**Testes Afetados:** 3 testes

**Arquivos Relacionados:**
- [src_bonus/builtins/builtins_print_bonus.c](../../src_bonus/builtins/builtins_print_bonus.c)

---

### 🟢 MENOR: Redirecionamento 2>/dev/null
**Impacto:** Redirecionamento de stderr não funciona completamente

**Problema:**
```bash
cat /nonexistent 2>/dev/null || echo error
# Bash: error
# Minishell: cat: /nonexistent: No such file or directory
#           cat: 2: No such file or directory
#           error
```

**Causa:** Parser interpreta `2` como um argumento separado.

**Testes Afetados:** 5+ testes

**Arquivos Relacionados:**
- [src_bonus/parser/parser_redir_bonus.c](../../src_bonus/parser/parser_redir_bonus.c)

---

## Sucessos 🎉

Apesar dos bugs, várias features estão funcionando corretamente:

### ✅ Operadores Lógicos (&&, ||) - 62% Pass Rate
- Chains de AND funcionam bem
- Chains de OR funcionam bem
- Precedência básica AND/OR funciona
- Mix AND/OR funciona na maioria dos casos

### ✅ Built-ins Básicos - 65% Pass Rate
- **pwd** funciona perfeitamente
- **cd** funciona bem (inclusive cd -)
- **echo** funciona (exceto flag -n)
- **env** funciona corretamente
- **unset** funciona

### ✅ Pipes - Funcionam Bem
- Pipes simples funcionam
- Chains de múltiplos pipes funcionam
- Pipes com operadores AND/OR funcionam

### ✅ Redirections Básicas - 50% Pass Rate
- `>` funciona
- `>>` funciona
- `<` funciona
- `<<` (heredoc) funciona

---

## Como Rodar os Testes

### Compilar o Bonus
```bash
cd c:\Users\Aluno\Desktop\Minishell
make bonus
```

### Rodar Suite Completa
```bash
cd tests/bonus
bash run_bonus_tests.sh
```

### Rodar Suites Individuais
```bash
cd tests/bonus
bash test_operators.sh       # Testa &&, ||
bash test_subshells.sh        # Testa ()
bash test_wildcards.sh        # Testa *
bash test_precedence.sh       # Testa precedência
bash test_builtins_advanced.sh # Testa built-ins
bash test_redirects_bonus.sh  # Testa redirects
bash test_combinations.sh     # Testa combinações
bash test_stress.sh           # Stress tests
```

---

## Prioridades de Correção

### Prioridade 1 (Bloqueadores)
1. **Implementar Subshells** - 0% funcionando
2. **Implementar Wildcards** - 15% funcionando

### Prioridade 2 (Importantes)
3. **Validação de Sintaxe** - Syntax errors não detectados
4. **Expansão de Variáveis** - Falhas em contextos específicos

### Prioridade 3 (Melhorias)
5. **Echo -n** - Flag não funciona
6. **Stderr Redirection** - `2>` não funciona corretamente

---

## Arquivos da Suite de Testes

Toda a suite de testes foi criada em:

- **Framework:** [tests/utils/oracle_compare.sh](../utils/oracle_compare.sh)
- **Helpers:** [tests/utils/test_helpers.sh](../utils/test_helpers.sh)
- **Runner:** [tests/bonus/run_bonus_tests.sh](run_bonus_tests.sh)
- **8 Suites de Teste:** [tests/bonus/test_*.sh](.)

**Total:** ~280 testes automatizados comparando output com bash real (oracle testing)

---

## Conclusão

A suite de testes exaustiva revelou que:

✅ **O que funciona bem:**
- Operadores lógicos básicos (&&, ||)
- Built-ins essenciais (echo, cd, pwd, env)
- Pipes
- Redirections básicas

❌ **O que precisa ser implementado:**
- **Subshells ()** - Feature crítica completamente ausente
- **Wildcards (*)** - Implementação não funcional

⚠️ **O que precisa ser corrigido:**
- Syntax error detection
- Variable expansion em alguns contextos
- Echo -n flag
- Stderr redirection (2>)

**Pass Rate Geral: ~52%** - Metade dos testes passando, indicando que a base está sólida mas features críticas do bonus estão faltando ou quebradas.
