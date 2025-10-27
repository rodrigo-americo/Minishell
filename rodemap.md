# 🗺️ Mapa de Desenvolvimento - Minishell

## 📊 Visão Geral do Projeto
**Tempo Total Estimado:** 4-6 semanas  
**Dificuldade:** ⭐⭐⭐⭐☆ (Alta)  
**Pontos Críticos:** Pipes, Redirecionamentos, Parsing, Sinais

---

## 🔧 Funções Autorizadas e Seus Usos

### 📖 Leitura e Interface
- `readline()` - Ler linha de comando do usuário com histórico
- `rl_clear_history()` - Limpar histórico de comandos
- `rl_on_new_line()` - Notificar readline sobre nova linha
- `rl_replace_line()` - Substituir conteúdo da linha atual
- `rl_redisplay()` - Redesenhar linha de comando
- `add_history()` - Adicionar comando ao histórico

### 💾 Memória e I/O
- `malloc()` / `free()` - Alocação dinâmica de memória
- `write()` / `read()` - Escrita/leitura em file descriptors
- `printf()` / `perror()` - Saída formatada e mensagens de erro
- `strerror()` - Converter errno em string de erro

### 📁 Sistema de Arquivos
- `access()` - Verificar permissões de arquivo
- `open()` / `close()` - Abrir/fechar arquivos
- `stat()` / `lstat()` / `fstat()` - Informações sobre arquivos
- `unlink()` - Remover arquivo
- `opendir()` / `readdir()` / `closedir()` - Operações com diretórios
- `getcwd()` - Obter diretório atual
- `chdir()` - Mudar diretório

### 🔀 Processos e Execução
- `fork()` - Criar processo filho
- `execve()` - Executar programa
- `wait()` / `waitpid()` / `wait3()` / `wait4()` - Aguardar processo filho
- `exit()` - Finalizar processo

### 📡 Sinais
- `signal()` / `sigaction()` - Configurar handlers de sinais
- `sigemptyset()` / `sigaddset()` - Manipular conjuntos de sinais
- `kill()` - Enviar sinal para processo

### 🔗 Pipes e Redirecionamento
- `pipe()` - Criar pipe
- `dup()` / `dup2()` - Duplicar file descriptors

### 🌍 Ambiente e Terminal
- `getenv()` - Obter variável de ambiente
- `isatty()` - Verificar se é terminal
- `ttyname()` / `ttyslot()` - Informações do terminal
- `ioctl()` - Controle de dispositivo I/O
- `tcsetattr()` / `tcgetattr()` - Configurar atributos do terminal
- `tgetent()` / `tgetflag()` / `tgetnum()` / `tgetstr()` / `tgoto()` / `tputs()` - Termcap (raramente usado)

---

## 📅 Fase 1: Fundação (Semana 1)
**Tempo estimado:** 5-7 dias  
**Dificuldade:** ⭐⭐☆☆☆

### 1.1 Estrutura Básica do Projeto
- [x] Criar Makefile com regras básicas
- [x] Configurar estrutura de pastas
- [x] Definir estruturas de dados principais
- [ ] Configurar libft (se usar)

**Estruturas Principais:**
```c
typedef struct s_token {
    char *value;
    int type; // WORD, PIPE, REDIR_IN, etc.
    struct s_token *next;
} t_token;

typedef struct s_cmd {
    char **args;
    t_redir *redirs;
    struct s_cmd *next;
} t_cmd;
```

**Testes:**
- Makefile compila sem erros
- Programa inicia e exibe prompt
- Ctrl-D fecha o programa

### 1.2 Loop Principal e Readline
- [x] Implementar loop principal do shell
- [x] Integrar readline e histórico
- [x] Tratamento básico de sinais (Ctrl-C, Ctrl-D, Ctrl-\)

**Funções a Implementar:**
- `main_loop()` - Loop principal
- `setup_signals()` - Configurar handlers de sinais
- `display_prompt()` - Exibir prompt

**Testes:**
- Prompt é exibido corretamente
- Histórico funciona (setas ↑↓)
- Ctrl-C limpa linha e mostra novo prompt
- Ctrl-D sai do shell
- Ctrl-\ não faz nada

---

## 📅 Fase 2: Lexer e Parser (Semana 1-2)
**Tempo estimado:** 7-10 dias  
**Dificuldade:** ⭐⭐⭐⭐☆

### 2.1 Lexer (Tokenização)
- [ ] Identificar tokens (palavras, operadores, redirecionamentos)
- [ ] Tratar aspas simples e duplas
- [ ] Identificar pipes e redirecionamentos

**Funções a Implementar:**
- `lexer()` - Tokenizar input
- `handle_quotes()` - Processar aspas
- `create_token()` - Criar novo token
- `is_metachar()` - Identificar metacaracteres

**Tipos de Token:**
- WORD - palavra comum
- PIPE - |
- REDIR_IN - <
- REDIR_OUT - >
- REDIR_APPEND - >>
- REDIR_HEREDOC - <<

**Testes:**
- `echo hello` → [WORD:"echo", WORD:"hello"]
- `echo "hello world"` → [WORD:"echo", WORD:"hello world"]
- `echo 'hello $USER'` → [WORD:"echo", WORD:"hello $USER"]
- `cat < file` → [WORD:"cat", REDIR_IN, WORD:"file"]
- `ls | grep txt` → [WORD:"ls", PIPE, WORD:"grep", WORD:"txt"]

### 2.2 Expansão de Variáveis
- [ ] Expandir variáveis de ambiente ($USER, $HOME)
- [ ] Expandir $? (exit status)
- [ ] Respeitar aspas (não expandir em aspas simples)

**Funções a Implementar:**
- `expand_variables()` - Expandir $VAR
- `expand_exit_status()` - Expandir $?
- `get_var_value()` - Obter valor de variável

**Testes:**
- `echo $USER` → expande para nome do usuário
- `echo '$USER'` → imprime literal "$USER"
- `echo "$USER"` → expande para nome do usuário
- `echo $?` → imprime exit status anterior
- `echo $NONEXISTENT` → imprime string vazia

### 2.3 Parser (Análise Sintática)
- [ ] Construir árvore de comandos
- [ ] Identificar comandos e argumentos
- [ ] Organizar pipes
- [ ] Organizar redirecionamentos

**Funções a Implementar:**
- `parser()` - Analisar tokens
- `parse_command()` - Criar estrutura de comando
- `parse_pipeline()` - Criar pipeline
- `validate_syntax()` - Validar sintaxe

**Testes:**
- `echo hello | cat` → 2 comandos conectados por pipe
- `< in cat | grep a > out` → comando com múltiplos redirecionamentos
- `echo` (sintaxe válida)
- `| echo` (erro de sintaxe)
- `echo |` (erro de sintaxe)

---

## 📅 Fase 3: Execução Básica (Semana 2-3)
**Tempo estimado:** 7-10 dias  
**Dificuldade:** ⭐⭐⭐☆☆

### 3.1 Busca de Executáveis
- [ ] Buscar comandos em PATH
- [ ] Aceitar caminhos relativos e absolutos
- [ ] Validar permissões de execução

**Funções a Implementar:**
- `find_command()` - Buscar comando no PATH
- `is_executable()` - Verificar se arquivo é executável
- `get_path_env()` - Obter variável PATH

**Testes:**
- `ls` → encontra /bin/ls
- `/bin/ls` → usa caminho absoluto
- `./minishell` → usa caminho relativo
- `nonexistent` → erro "command not found"

### 3.2 Execução Simples (sem pipes)
- [ ] Fork e execve para comandos externos
- [ ] Capturar exit status
- [ ] Tratamento de erros

**Funções a Implementar:**
- `execute_command()` - Executar comando único
- `fork_and_exec()` - Fork + execve
- `wait_for_child()` - Aguardar processo filho

**Testes:**
- `ls` → lista arquivos
- `cat arquivo.txt` → exibe conteúdo
- `sleep 1` → aguarda 1 segundo
- Exit status correto capturado

### 3.3 Built-ins
- [ ] `echo` (com opção -n)
- [ ] `cd` (mudar diretório)
- [ ] `pwd` (diretório atual)
- [ ] `export` (definir variável)
- [ ] `unset` (remover variável)
- [ ] `env` (listar variáveis)
- [ ] `exit` (sair do shell)

**Funções a Implementar:**
- `is_builtin()` - Verificar se é builtin
- `execute_builtin()` - Executar builtin
- `builtin_echo()` - Implementar echo
- `builtin_cd()` - Implementar cd
- `builtin_pwd()` - Implementar pwd
- `builtin_export()` - Implementar export
- `builtin_unset()` - Implementar unset
- `builtin_env()` - Implementar env
- `builtin_exit()` - Implementar exit

**Testes echo:**
- `echo hello` → "hello\n"
- `echo -n hello` → "hello" (sem newline)
- `echo -n -n hello` → "hello" (sem newline)
- `echo hello world` → "hello world\n"

**Testes cd:**
- `cd /tmp` → muda para /tmp
- `cd ..` → volta um diretório
- `cd ~` → vai para home (se implementar)
- `cd nonexistent` → erro

**Testes pwd:**
- `pwd` → imprime diretório atual

**Testes export:**
- `export VAR=value` → define variável
- `export` → lista todas variáveis (formato bash)
- `echo $VAR` → imprime "value"

**Testes unset:**
- `unset VAR` → remove variável
- `echo $VAR` → imprime vazio

**Testes env:**
- `env` → lista variáveis de ambiente

**Testes exit:**
- `exit` → sai com status 0
- `exit 42` → sai com status 42

---

## 📅 Fase 4: Redirecionamentos (Semana 3)
**Tempo estimado:** 5-7 dias  
**Dificuldade:** ⭐⭐⭐⭐☆

### 4.1 Redirecionamentos Básicos
- [ ] `<` - redirecionar entrada
- [ ] `>` - redirecionar saída
- [ ] `>>` - redirecionar saída (append)
- [ ] Múltiplos redirecionamentos

**Funções a Implementar:**
- `setup_redirections()` - Configurar redirecionamentos
- `redirect_input()` - Redirecionar stdin
- `redirect_output()` - Redirecionar stdout
- `open_file()` - Abrir arquivo com permissões corretas

**Testes:**
- `echo hello > file.txt` → cria arquivo
- `cat < file.txt` → lê do arquivo
- `echo world >> file.txt` → adiciona ao arquivo
- `< in cat > out` → entrada e saída redirecionadas
- `> file1 > file2 echo test` → último redirecionamento prevalece

### 4.2 Here-doc (<<)
- [ ] Ler até delimitador
- [ ] Não adicionar ao histórico
- [ ] Expandir variáveis em here-doc

**Funções a Implementar:**
- `handle_heredoc()` - Processar here-doc
- `read_heredoc()` - Ler linhas até delimitador

**Testes:**
- `cat << EOF` → lê até "EOF"
- `cat << END | grep hello` → here-doc com pipe
- Here-doc expande $VAR

---

## 📅 Fase 5: Pipes (Semana 3-4)
**Tempo estimado:** 5-7 dias  
**Dificuldade:** ⭐⭐⭐⭐⭐

### 5.1 Pipes Simples
- [ ] Conectar stdout de cmd1 ao stdin de cmd2
- [ ] Criar processos para cada comando
- [ ] Gerenciar file descriptors

**Funções a Implementar:**
- `execute_pipeline()` - Executar pipeline
- `setup_pipe()` - Criar e configurar pipe
- `close_unused_fds()` - Fechar FDs não usados

**Testes:**
- `ls | cat` → pipe simples
- `cat file.txt | grep hello` → busca em arquivo
- `echo hello | cat | cat | cat` → múltiplos pipes
- Exit status é do último comando

### 5.2 Pipes com Redirecionamentos
- [ ] Combinar pipes e redirecionamentos
- [ ] Ordem correta de operações

**Testes:**
- `< in cat | grep a > out` → entrada, pipe, saída
- `cat < file | grep hello > result` → combinação completa
- `echo test | cat > file` → pipe para arquivo

---

## 📅 Fase 6: Tratamento de Sinais (Semana 4)
**Tempo estimado:** 2-3 dias  
**Dificuldade:** ⭐⭐⭐☆☆

### 6.1 Sinais no Shell
- [ ] Ctrl-C (SIGINT) - novo prompt
- [ ] Ctrl-D (EOF) - sair
- [ ] Ctrl-\ (SIGQUIT) - ignorar
- [ ] Sinais durante execução de comandos

**Funções a Implementar:**
- `signal_handler()` - Handler de sinais
- `setup_signal_handlers()` - Configurar handlers
- `ignore_signals()` - Ignorar sinais específicos

**Usar variável global apenas para armazenar número do sinal!**

**Testes:**
- Ctrl-C durante prompt → novo prompt
- Ctrl-C durante `sleep 5` → interrompe comando
- Ctrl-D → sai do shell
- Ctrl-\ → não faz nada
- Sinal capturado na variável global corretamente

---

## 📅 Fase 7: Refinamento e Testes (Semana 4-5)
**Tempo estimado:** 7-10 dias  
**Dificuldade:** ⭐⭐⭐☆☆

### 7.1 Tratamento de Erros
- [ ] Validar todas as entradas
- [ ] Mensagens de erro apropriadas
- [ ] Não vazar memória em casos de erro

**Testes:**
- Sintaxe inválida → mensagem de erro
- Arquivo inexistente → erro apropriado
- Comando não encontrado → "command not found"
- Permissão negada → erro apropriado

### 7.2 Memory Leaks
- [ ] Verificar com valgrind
- [ ] Liberar todas as estruturas
- [ ] Tratar erros de alocação

**Comando:**
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell
```

**Nota:** readline pode vazar, mas seu código não pode!

### 7.3 Testes Intensivos
- [ ] Testar com bash como referência
- [ ] Casos extremos (strings vazias, muitos pipes)
- [ ] Comandos complexos

**Casos de Teste Críticos:**
```bash
# Aspas
echo "hello   world"
echo 'hello   world'
echo "hello $USER world"

# Pipes múltiplos
ls | grep minishell | wc -l

# Redirecionamentos múltiplos
< in1 < in2 cat > out1 > out2

# Here-doc
cat << EOF | grep hello
hello world
test
EOF

# Variáveis
export TEST=hello
echo $TEST
unset TEST
echo $TEST

# Exit status
ls
echo $?
lsnonexistent
echo $?

# Built-ins em pipes
echo test | cat
export | grep PATH

# Sinais
sleep 10  # Ctrl-C deve interromper
```

---

## 🎁 Fase 8: Bônus (Semana 5-6)
**Tempo estimado:** 5-7 dias  
**Dificuldade:** ⭐⭐⭐⭐⭐

### 8.1 Operadores Lógicos
- [ ] `&&` (AND) - executa cmd2 se cmd1 sucesso
- [ ] `||` (OR) - executa cmd2 se cmd1 falha
- [ ] Parênteses para prioridade

**Testes:**
- `ls && echo success` → executa echo
- `lsnonexistent || echo failed` → executa echo
- `(ls && echo success) || echo failed`

### 8.2 Wildcards
- [ ] `*` funciona no diretório atual
- [ ] Expansão de padrões

**Testes:**
- `ls *.c` → lista arquivos .c
- `echo *` → lista todos os arquivos
- `cat *.txt` → concatena todos .txt

---

## 📋 Checklist Final

### Funcionalidades Obrigatórias
- [ ] Prompt funcional
- [ ] Histórico funcionando
- [ ] Busca de executáveis (PATH)
- [ ] Aspas simples e duplas
- [ ] Redirecionamentos: <, >, <<, >>
- [ ] Pipes (|)
- [ ] Variáveis de ambiente ($VAR)
- [ ] $? (exit status)
- [ ] Sinais: Ctrl-C, Ctrl-D, Ctrl-\
- [ ] Built-ins: echo, cd, pwd, export, unset, env, exit

### Qualidade de Código
- [ ] Sem memory leaks (exceto readline)
- [ ] Sem segfaults
- [ ] Norma respeitada
- [ ] Makefile completo
- [ ] Tratamento de erros robusto

### Testes Recomendados
- [ ] Comparar output com bash
- [ ] Testar casos extremos
- [ ] Valgrind sem erros
- [ ] Testes de colegas

---

## 💡 Dicas de Desenvolvimento

### Prioridades
1. **Faça funcionar primeiro** - código limpo depois
2. **Teste continuamente** - não deixe bugs acumularem
3. **Compare com bash** - ele é sua referência
4. **Peça revisão** - colegas encontram bugs que você não vê

### Armadilhas Comuns
- **File descriptors não fechados** → usar close() corretamente
- **Processos zumbis** → sempre usar wait()
- **Sinais durante syscalls** → podem interromper read/write
- **Fork bombs** → limitar número de processos
- **Heredoc infinito** → validar delimitador

### Ferramentas Úteis
```bash
# Verificar memory leaks
valgrind --leak-check=full ./minishell

# Verificar file descriptors abertos
lsof -c minishell

# Comparar com bash
diff <(bash -c "comando") <(./minishell -c "comando")

# Debug
lldb ./minishell
gdb ./minishell
```

---

## 📚 Recursos Recomendados

- Manual do bash: `man bash`
- Tutoriais sobre fork/exec/pipe
- Documentação das funções autorizadas
- Projetos minishell de colegas (após terminar o seu!)

**Boa sorte! 🚀**