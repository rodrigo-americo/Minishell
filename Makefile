# --- Nomes ---
NAME        = minishell


# --- Diretórios ---
LIBFT_DIR   = ./libft
SRC_DIR     = ./src
SRC_DIR_B   = ./src_bonus
OBJ_DIR     = ./obj
OBJ_DIR_B   = ./obj_bonus
INC_DIR     = ./includes
INC_DIR_B   = ./includes_bonus

# --- Arquivos ---
SRC_FILES   = main.c \
			  signal.c \
			  utils.c \
			  clean_utils.c \
			  assignment.c \
			  utils/continuation.c \
			  utils/continuation_utils.c \
			  utils/line_join.c \
			  lexer/lexer.c \
			  lexer/lexer_utils.c \
			  token_utils.c \
			  wrappers.c \
			  inits.c \
			  env/env.c \
			  env/env_set.c \
			  env/env_utils.c \
			  expander/expander.c \
			  expander/expander_utils.c \
			  expander/process_string.c \
			  expander/word_splitting.c \
			  parser/parser.c \
			  parser/parser_utils.c \
			  parser/syntax_check.c \
			  parser/redir.c \
			  parser/heredoc_parser.c \
			  parser/heredoc_parser_utils.c \
			  parser/heredoc_delimiter.c \
			  executor/executor.c \
			  executor/path_resolution.c \
			  executor/path_execution.c \
			  executor/env_conversion.c \
			  executor/pipes.c \
			  executor/pipes_helpers.c \
			  executor/pipe_utils.c \
			  executor/child_utils.c \
			  executor/redirections.c \
			  executor/heredoc.c \
			  builtins/builtins.c \
			  builtins/builtins_cd.c \
			  builtins/builtins_cd_utils.c \
			  builtins/builtins_env.c \
			  builtins/builtins_exit.c \
			  builtins/builtins_exit_utils.c \
			  builtins/builtins_print.c \
			  builtins/builtins_utils.c \
			  builtins/builtins_valid.c

SRC_FILES_B = main_bonus.c \
			  ast/ast_create_bonus.c \
			  ast/ast_free_bonus.c \
			  ast/ast_print_bonus.c \
			  ast/ast_utils_bonus.c \
			  ast/ast_copy_bonus.c \
			  builtins/builtins_bonus.c \
			  builtins/builtins_cd_bonus.c \
			  builtins/builtins_cd_utils_bonus.c \
			  builtins/builtins_env_bonus.c \
			  builtins/builtins_exit_bonus.c \
			  builtins/builtins_exit_utils_bonus.c \
			  builtins/builtins_print_bonus.c \
			  builtins/builtins_utils_bonus.c \
			  builtins/builtins_valid_bonus.c \
			  env/env_bonus.c \
			  env/env_set_bonus.c \
			  env/env_utils_bonus.c \
			  executor/executor_bonus.c \
			  executor/executor_command_bonus.c \
			  executor/executor_operators_bonus.c \
			  executor/executor_pipe_bonus.c \
			  executor/env_conversion_bonus.c \
			  executor/path_resolution_bonus.c \
			  executor/heredoc_bonus.c \
			  executor/redirections_bonus.c \
			  expander/expander_bonus.c \
			  expander/expander_utils_bonus.c \
			  expander/expander_value_bonus.c \
			  expander/process_string_bonus.c \
			  expander/word_splitting_bonus.c \
			  expander/wildcard_bonus.c \
			  expander/wildcard_match_bonus.c \
			  lexer/lexer_bonus.c \
			  lexer/lexer_utils_bonus.c \
			  parser/parser_bonus.c \
			  parser/parser_command_bonus.c \
			  parser/parser_precedence_bonus.c \
			  parser/parser_subshell_bonus.c \
			  parser/parser_redir_bonus.c \
			  parser/parser_utils_bonus.c \
			  parser/redir_bonus.c \
			  parser/heredoc_parser_bonus.c \
			  parser/syntax_check_bonus.c \
			  utils/continuation_bonus.c \
			  utils/inits_bonus.c \
			  utils/line_join_bonus.c \
			  utils/signal_bonus.c \
			  utils/token_utils_bonus.c \
			  utils/utils_bonus.c \
			  utils/wrappers_bonus.c

# Transforma .c em .o mantendo a estrutura ou simplificando
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
OBJS_B      = $(addprefix $(OBJ_DIR_B)/, $(SRC_FILES_B:.c=.o))

# --- Compilação ---
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
# Includes: Procura headers na pasta includes e na pasta de headers da libft
# (libft headers estão em `libft/include`)
INCLUDES    = -I $(INC_DIR) -I $(LIBFT_DIR)/include
INCLUDES_B  = -I $(INC_DIR_B) -I $(LIBFT_DIR)/include

# --- Bibliotecas ---
# Linka com a libft compilada e com a readline
LIBS        = -L$(LIBFT_DIR) -lft -lreadline

# --- Comandos ---
RM          = rm -rf
MKDIR       = mkdir -p

# --- Regras ---

all: $(NAME)

# Regra principal: Compila a libft se necessário, depois o minishell

$(NAME): $(OBJS)
	@make bonus -C $(LIBFT_DIR)
	@echo "🔨 Linkando $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "✅ Minishell compilado com sucesso!"

# Regra genérica para objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	@echo "📝 Compilando $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Limpeza
clean:
	@make clean -C $(LIBFT_DIR)
	@echo "🧹 Limpando objetos..."
	@$(RM) $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@echo "🗑️ Removendo executável..."
	@$(RM) $(NAME)

re: fclean all

# --- Regras Bonus ---

bonus: $(OBJS_B)
	@make bonus -C $(LIBFT_DIR)
	@echo "🔨 Linkando $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS_B) $(LIBS) -o $(NAME)
	@echo "✅ Minishell Bonus compilado com sucesso!"

# Regra genérica para objetos bonus
$(OBJ_DIR_B)/%.o: $(SRC_DIR_B)/%.c
	@$(MKDIR) $(dir $@)
	@echo "📝 Compilando $<..."
	@$(CC) $(CFLAGS) $(INCLUDES_B) -c $< -o $@

# Limpeza bonus
fclean_bonus: clean_bonus
	@echo "🗑️ Removendo executável bonus..."
	@$(RM) $(NAME)

clean_bonus:
	@echo "🧹 Limpando objetos bonus..."
	@$(RM) $(OBJ_DIR_B)

val: readline.supp all
	@valgrind -q --suppressions=readline.supp \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				./${NAME}

re_bonus: fclean_bonus bonus

.PHONY: all clean fclean re bonus clean_bonus fclean_bonus re_bonus
