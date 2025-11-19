# --- Nomes ---
NAME        = minishell

# --- Diretórios ---
LIBFT_DIR   = ./libft
SRC_DIR     = ./src
OBJ_DIR     = ./obj
INC_DIR     = ./includes

# --- Arquivos ---
# Liste aqui todos os seus arquivos .c que estão dentro de src/
# Estou colocando os que você me enviou + lexer_utils (que vamos precisar)
SRC_FILES   = main.c \
              signal.c \
              utils.c \
              lexer/lexer.c \
              lexer/token_utils.c

# Transforma .c em .o mantendo a estrutura ou simplificando
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# --- Compilação ---
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
# Includes: Procura headers na pasta includes E na pasta libft
INCLUDES    = -I $(INC_DIR) -I $(LIBFT_DIR)

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
	@make -C $(LIBFT_DIR)
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