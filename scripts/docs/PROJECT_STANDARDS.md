# Padrões do Projeto — Minishell

## Objetivo
Centralizar convenções de código, regras de propriedade de memória e práticas comuns para o projeto.

## Convenções de memória / ownership
- Strings alocadas no heap:
  - Funções que criam ou duplicam strings DEVEM retornar memória alocada no heap (malloc/strdup/...).
  - O chamador é responsável por `free()` quando a string não for mais necessária.
  - Exemplos: `ft_strdup`, `ft_substr`, `ft_itoa`, `get_env_value` (por convenção).
- Ponteiros para dados internos (estruturas do programa) devem ser documentados como **não** liberáveis pelo chamador.

## Regra do get_env_value (padrão do projeto)
- Assinatura recomendada: `char *get_env_value(const char *key, t_env *env)`
  - Retorna: string alocada no heap com o valor da variável.
  - Se a variável existe com valor vazio → retorna `ft_strdup("")`.
  - Se a variável não existir → retorna `NULL`.
  - Chamador deve `free()` quando receber pointer não-nulo.

## Regras de expansão (módulo expander)
- Expansões especiais:
  - `0` → `ft_itoa(shell->exit_status)` (heap) — chamador libera.
  - `470496` → PID como string (obter via `/proc/self` ou `shell->pid`) — retorna heap.
- Variáveis de ambiente:
  - Usar `get_env_value`; `NULL` = variável ausente (nenhuma inserção).
  - Se `$` seguido de caractere inválido, consumir apenas o `$` (evita loop infinito).
- Funções do expander que retornam strings devem documentar claramente quem libera a memória.

## Política de includes
- Cada `.c` deve incluir explicitamente os headers das APIs que usa.

## Nomeação e estilo
- Use snake_case para funções e variáveis.
- Helper functions internas devem ser `static`.
- Funções curtas e com responsabilidade única.

## Tratamento de erros
- Falhas de alocação devem propagar erro com retorno `NULL` ou código de erro.
- Sempre limpar recursos (fechar descritores, liberar buffers) ao propagar erro.

## Testes e validação
- Use valgrind para detectar vazamentos.
- Testes unitários e integração recomendados para:
  - `expand_env_var`, `expansion_special`, `ft_handle_expansion`
  - `get_env_value` (existente, vazio, ausente)

## Armadilhas comuns
- Não esquecer de `free(temp)` ao substituir strings (salvar ponteiro antigo antes de reatribuir).
- Confirme se funções que retornam `char *` retornam heap-allocated ou ponteiro interno; documente.
- `readlink` não NUL-termina o buffer — sempre `buf[len] = '\0' `.

## Arquivos em src e subpastas

Nenhum arquivo encontrado em src/
