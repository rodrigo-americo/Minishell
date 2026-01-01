# --- Nomes ---
NAME        = minishell

# --- Diretórios ---
LIBFT_DIR   = ./libft
SRC_DIR     = ./src
OBJ_DIR     = ./obj
INC_DIR     = ./includes

# --- Arquivos ---
SRC_FILES   = main.c \
			  signal.c \
			  utils.c \
			  clean_utils.c \
			  assignment.c \
			  utils/continuation.c \
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
			  executor/executor.c \
			  executor/path_resolution.c \
			  executor/path_execution.c \
			  executor/env_conversion.c \
			  executor/pipes.c \
			  executor/pipe_utils.c \
			  executor/redirections.c \
			  executor/heredoc.c \
			  builtins/builtins.c \
			  builtins/builtins_cd.c \
			  builtins/builtins_cd_utils.c \
			  builtins/builtins_env.c \
			  builtins/builtins_exit.c \
			  builtins/builtins_print.c \
			  builtins/builtins_utils.c \
			  builtins/builtins_valid.c \

# Transforma .c em .o mantendo a estrutura ou simplificando
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# --- Compilação ---
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
# Includes: Procura headers na pasta includes e na pasta de headers da libft
# (libft headers estão em `libft/include`)
INCLUDES    = -I $(INC_DIR) -I $(LIBFT_DIR)/include

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

.PHONY: all clean fclean re