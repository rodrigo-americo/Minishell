# Minishell Test Suite

Esta pasta contém os testes automatizados para o projeto Minishell.

## Estrutura dos Testes

### Testes em C (Componentes Internos)
- **test_token.c**: Testes básicos de tokens e listas
- **test_lexer.c**: Testes abrangentes do analisador léxico (lexer)
- **test_parser.c**: Testes do analisador sintático (parser)
- **test_expander.c**: Testes de expansão de variáveis e remoção de aspas
- **test_utils.c**: Testes das funções utilitárias

### Testes em Bash (Funcionalidade End-to-End) 🆕
- **test_executor.sh**: Testes de execução de comandos (PATH, caminhos absolutos/relativos, command not found, exit status)
- **test_pipes.sh**: Testes de pipes (simples, múltiplos comandos, argumentos, edge cases)
- **test_expansion.sh**: Testes de expansão de variáveis ($VAR, $?, aspas, múltiplas expansões)
- **run_all_tests.sh**: Script master que executa todos os testes bash com sumário completo

## Como Compilar (Testes em C)

Para compilar todos os testes:
```bash
make
```

Para compilar um teste específico:
```bash
make test_lexer
make test_parser
make test_utils
make test_token
```

## Como Executar

Para executar todos os testes:
```bash
make run
```

Para executar um teste específico:
```bash
make run_lexer
make run_parser
make run_utils
make run_token
```

Ou execute diretamente o binário:
```bash
./test_lexer
./test_parser
./test_utils
./test_token
```

## Cobertura de Testes

### test_lexer.c (14 testes)
- Tokenização de palavras simples e múltiplas
- Reconhecimento de operadores (pipe, redirecionamentos)
- Tratamento de aspas simples e duplas
- Detecção de erros (aspas não fechadas)
- Tratamento de espaços em branco
- Comandos complexos

### test_parser.c (15 testes)
- Parsing de comandos simples
- Parsing de pipelines (2 e 3 comandos)
- Parsing de redirecionamentos (entrada, saída, append, heredoc)
- Múltiplos redirecionamentos
- Detecção de erros de sintaxe (pipe no início/fim, redirecionamento sem arquivo)
- Comandos complexos

### test_expander.c (10 testes)
- Expansão de variáveis simples
- Expansão de exit status ($?)
- Expansão dentro de aspas duplas
- Não expansão em aspas simples
- Variáveis indefinidas
- Múltiplas expansões
- Expansão em redirecionamentos
- Remoção de aspas
- Caracteres especiais em variáveis

### test_utils.c (26 testes)
- skip_whitespace: remoção de espaços e tabs
- is_separator: identificação de separadores
- ft_add_to_array: manipulação de arrays de strings
- create_redir: criação de estruturas de redirecionamento
- add_redir_to_end: gerenciamento de lista de redirecionamentos
- create_token: criação de tokens

## Formato de Saída

Os testes exibem o resultado de cada teste individualmente:
- `[✓]` indica teste passou
- `[✗]` indica teste falhou

No final, um resumo é exibido com:
- Total de testes executados
- Número de testes que passaram
- Número de testes que falharam

## Como Executar (Testes em Bash) 🆕

Para executar TODOS os testes bash de uma vez:
```bash
cd tests
bash run_all_tests.sh
```

Para executar um teste bash específico:
```bash
cd tests
bash test_executor.sh     # Testa execução de comandos
bash test_pipes.sh         # Testa pipes
bash test_expansion.sh     # Testa expansão de variáveis
```

**Nota**: Os scripts bash testam o minishell compilado em `../minishell`, então certifique-se de compilar antes:
```bash
cd ..
make
cd tests
bash run_all_tests.sh
```

## Notas

- O teste `test_expander` está comentado no Makefile até que as funções `env.c` e `word_splitting` sejam totalmente implementadas
- Todos os testes verificam corretamente a memória alocada e fazem cleanup apropriado
- Os testes são independentes e podem ser executados em qualquer ordem
- Os testes bash comparam a saída do minishell com a do bash real para garantir compatibilidade

## Limpeza

Para limpar os binários de teste:
```bash
make clean
```

Para limpar tudo (incluindo libft):
```bash
make fclean
```

Para recompilar do zero:
```bash
make re
```
