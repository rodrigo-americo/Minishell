LIBFT_DIR=../libft
INCLUDES=-I../includes -I$(LIBFT_DIR)/include
SRC_DIR=../src

CC=gcc
CFLAGS=-Wall -Wextra -Werror $(INCLUDES)

# Source files needed for tests
LEXER_SRCS=$(SRC_DIR)/lexer.c $(SRC_DIR)/token_utils.c $(SRC_DIR)/utils.c
PARSER_SRCS=$(SRC_DIR)/parser/parser.c $(SRC_DIR)/parser/parser_utils.c $(SRC_DIR)/lexer.c $(SRC_DIR)/token_utils.c $(SRC_DIR)/utils.c
EXPANDER_SRCS=$(SRC_DIR)/expander/expander.c $(SRC_DIR)/expander/expander_utils.c $(SRC_DIR)/parser/parser.c $(SRC_DIR)/parser/parser_utils.c $(SRC_DIR)/lexer.c $(SRC_DIR)/token_utils.c $(SRC_DIR)/utils.c $(SRC_DIR)/env.c
UTILS_SRCS=$(SRC_DIR)/token_utils.c $(SRC_DIR)/utils.c $(SRC_DIR)/parser/parser_utils.c

# Test executables
TESTS=test_token test_lexer test_parser test_utils

all: $(TESTS)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

test_token: test_token.c $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) test_token.c $(SRC_DIR)/token_utils.c $(SRC_DIR)/utils.c -L$(LIBFT_DIR) -lft -o test_token

test_lexer: test_lexer.c $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) test_lexer.c $(LEXER_SRCS) -L$(LIBFT_DIR) -lft -o test_lexer

test_parser: test_parser.c $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) test_parser.c $(PARSER_SRCS) -L$(LIBFT_DIR) -lft -o test_parser

test_utils: test_utils.c $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) test_utils.c $(UTILS_SRCS) -L$(LIBFT_DIR) -lft -o test_utils

# Note: test_expander commented out until env.c and word_splitting are fully implemented
# test_expander: test_expander.c $(LIBFT_DIR)/libft.a
# 	$(CC) $(CFLAGS) test_expander.c $(EXPANDER_SRCS) -L$(LIBFT_DIR) -lft -o test_expander

run: all
	@echo "\n========== Running test_token =========="
	./test_token
	@echo "\n========== Running test_lexer =========="
	./test_lexer
	@echo "\n========== Running test_parser =========="
	./test_parser
	@echo "\n========== Running test_utils =========="
	./test_utils

run_lexer: test_lexer
	./test_lexer

run_parser: test_parser
	./test_parser

run_utils: test_utils
	./test_utils

run_token: test_token
	./test_token

clean:
	rm -f $(TESTS) test_expander

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all run run_lexer run_parser run_utils run_token clean fclean re
