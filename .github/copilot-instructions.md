<!--
Guidance for AI coding agents working on the Minishell repository.
Keep this file concise and concrete — reference real files and commands.
-->

# Copilot instructions for Minishell

Summary
- Purpose: Implement and maintain a small shell (tokenize → parse → expand → execute).
- Scope: Low-level C code under `src/` + a bundled `libft/` used for common helpers.

Big picture (what to know first)
- Input flow: user input (in `main.c`) → lexical analysis (`src/lexer.c`, `src/token_utils.c`) → parsing (`src/parser/parser.c`, `src/parser/parser_utils.c`) → expansion (`src/expander/expander.c`, `src/expander/expander_utils.c`) → execution (handled across `src/utils.c`, `env.c`, and the code that calls builtins/executables).
- Shared definitions and types live in `includes/minishell.h` — review this header before changing data structures or adding globals.
- `libft/` provides common helpers (string, memory, list utilities). Changes to libft should preserve its API; the top-level `Makefile` relies on it.

Key files to inspect for most tasks
- `src/lexer.c` and `src/token_utils.c` — tokenization rules, quoting, and token lifetimes.
- `src/parser/parser.c` — AST/command-structure building and validation.
- `src/expander/expander.c` — variable expansion and word splitting rules.
- `src/env.c` — environment variable storage/lookup and `export/unset` behavior.
- `src/signal.c` — terminal signal handling; careful changes here affect interactive behavior and tests.
- `includes/minishell.h` — types, macros, and function prototypes used across modules.

Build / run / debug
- Build: run `make` at the repository root. This compiles `libft/` and the shell binary (expected: `./minishell`).
- Clean: `make fclean` / `make re` follow usual 42-style Makefile targets (check the root `Makefile`).
- Run locally: execute `./minishell` from the repo root to test interactive behavior.
- Debugging: use `gdb` or run compiled binary under `valgrind` (Linux/macOS). Avoid changing signal handlers when adding debug prints.

Project-specific conventions and patterns
- Minimal dependencies: code uses only the provided `libft` functions and standard C libs. Don’t add new external dependencies without updating the `Makefile` and explaining why.
- Memory ownership: allocation helpers live in `libft/src/mandatory` (e.g., `ft_calloc`, `ft_strdup`). Freeing responsibilities follow local conventions — check callers before changing a function's return ownership.
- Error handling: functions return `NULL` or error codes consistent with surrounding code. Preserve these conventions to avoid subtle runtime issues.
- Tests and behavior expectations: this project mirrors a shell exercise with strict behavior (signals, prompts, exit codes). Avoid changing CLI output or exit codes unless the change is intentional and covered by tests.

Examples (how to make a safe change)
- To change tokenization for escaped quotes: update `src/lexer.c` and adjust helpers in `src/token_utils.c`. Run `make` and then manual acceptance tests in `./minishell` (try commands with mixing quotes and backslashes).
- To add a new builtin that reads/changes environment: add prototype in `includes/minishell.h`, implement in `src/env.c` or a new `src/builtin_*.c`, and register it in the command dispatch path in the parser/executor code.

Integration notes
- `libft/` is built in-tree; changes to its API require coordinated updates where it's used (search for `ft_` helpers before refactoring).
- Signal handling in `src/signal.c` interacts with the interactive prompt and child processes — modifications here require careful manual testing of Ctrl-C and Ctrl-\ behavior.

When in doubt
- Read `includes/minishell.h` and the caller sites before changing a function signature.
- Prefer minimal, behavior-preserving edits. Run `make` and exercise affected features interactively.

If you alter core behavior or public APIs, add a concise note at the top of the changed file and include a short test case in the PR description.

-- End of instructions --
