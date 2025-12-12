# 🐚 Minishell - Detailed To-Do List

## 🏗️ 1. Infraestrutura e Setup
- [x] [cite_start]**Repositório Git:** Garantir que tudo esteja no repo (somente o que está lá será avaliado)[cite: 39].
- [x] **Makefile:**
    - [x] [cite_start]Regras obrigatórias: `$(NAME)`, `all`, `clean`, `fclean`, `re`[cite: 27].
    - [x] [cite_start]Compilar com flags: `-Wall`, `-Wextra`, `-Werror`[cite: 25].
    - [ ] [cite_start]Não realizar re-links desnecessários[cite: 26].
    - [x] [cite_start]Incluir regra `bonus` (se fizer bônus)[cite: 28].
- [x] [cite_start]**Libft:** Copiar fontes e Makefile para pasta `libft` e compilar via Makefile principal[cite: 31, 32].
- [ ] [cite_start]**Norminette:** Verificar todos os arquivos (incluindo bônus)[cite: 20, 21].
- [ ] [cite_start]**Gestão de Memória:** Garantir `free` em tudo alocado na heap (sem leaks)[cite: 24].

## 🔄 2. Loop Principal e Parsing
- [ ] [cite_start]Exibir prompt aguardando novo comando[cite: 101].
- [ ] [cite_start]Implementar histórico de comandos funcional[cite: 102].
- [ ] **Tratamento de Aspas:**
    - [ ] [cite_start]`'` (Aspas simples): Não interpretar metacaracteres[cite: 114].
    - [ ] [cite_start]`"` (Aspas duplas): Interpretar apenas `$`[cite: 115].
    - [ ] [cite_start]Não interpretar aspas não fechadas[cite: 112].
    - [ ] [cite_start]Não interpretar `\` (barra invertida) ou `;` (ponto e vírgula)[cite: 112, 113].

## 💲 3. Expansões e Variáveis
- [ ] [cite_start]Expandir variáveis de ambiente (ex: `$VAR`) para seus valores[cite: 123].
- [ ] [cite_start]Expandir `$?` para o status de saída do último pipeline executado[cite: 124].

## 🚦 4. Sinais (Signals)
- [ ] [cite_start]Utilizar no máximo **uma variável global** para o sinal recebido[cite: 104].
    - [ ] [cite_start]A variável global não deve acessar estruturas de dados principais[cite: 105].
- [ ] **Modo Interativo:**
    - [ ] [cite_start]`ctrl-C`: Exibe novo prompt em nova linha[cite: 127].
    - [ ] [cite_start]`ctrl-D`: Sai do shell[cite: 128].
    - [ ] [cite_start]`ctrl-\`: Não faz nada[cite: 129].

## ⚙️ 5. Execução de Comandos
- [ ] [cite_start]Buscar e lançar executáveis baseados na variável `PATH`[cite: 103].
- [ ] [cite_start]Aceitar caminhos absolutos e relativos[cite: 103].
- [ ] [cite_start]Usar apenas funções autorizadas (fork, waitpid, execve, pipe, dup2, etc.)[cite: 99].

## 🔀 6. Redirecionamentos e Pipes
- [ ] [cite_start]`|` (Pipe): Conectar saída de um comando à entrada do próximo[cite: 122].
- [ ] [cite_start]`<` (Input): Redirecionar entrada[cite: 117].
- [ ] [cite_start]`>` (Output): Redirecionar saída[cite: 118].
- [ ] [cite_start]`>>` (Append): Redirecionar saída em modo de anexação[cite: 121].
- [ ] `<<` (Heredoc):
    - [ ] [cite_start]Receber delimitador e ler até encontrar a linha com ele[cite: 119].
    - [ ] [cite_start]Não atualizar o histórico com o input do heredoc[cite: 120].

## 📦 7. Built-ins
- [ ] [cite_start]`echo`: Com opção `-n`[cite: 131].
- [ ] [cite_start]`cd`: Apenas caminho relativo ou absoluto[cite: 133].
- [ ] [cite_start]`pwd`: Sem opções[cite: 133].
- [ ] [cite_start]`export`: Sem opções[cite: 133].
- [ ] [cite_start]`unset`: Sem opções[cite: 133].
- [ ] [cite_start]`env`: Sem opções ou argumentos[cite: 133].
- [ ] [cite_start]`exit`: Sem opções[cite: 133].

## ⭐ 8. Bônus (Opcional)
> [cite_start]A parte bônus só é avaliada se a mandatória for perfeita[cite: 139].
- [ ] [cite_start]`&&` e `||`: Com parênteses para prioridade[cite: 137].
- [ ] [cite_start]`*` (Wildcards): Para o diretório atual[cite: 138].

## ✅ 9. Validação
- [ ] [cite_start]Verificar estabilidade: Sem segfaults, bus errors, double frees[cite: 22].
- [ ] [cite_start]Verificar vazamentos de memória (exceto readline)[cite: 134].