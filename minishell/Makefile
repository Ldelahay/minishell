# Nom de l'exécutable
NAME = minishell

# Répertoires
SRC_DIR = src
OBJ_DIR = obj

# Fichiers sources et objets
SRC_FILES = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/builtins/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
LDFLAGS = -lreadline -lncurses  

# Header
HEAD = inc/minishell.h -I/usr/local/include/readline/readline.h

# Règles
all: $(NAME)

$(NAME): $(OBJ_FILES)
	@printf "Compiling %s                                             \r" $<
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ $(LDFLAGS)  

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@printf "Compiling %s                                             \r" $<
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@printf "Object files removed\n"

fclean: clean
	@rm -f $(NAME)
	@printf "Executable removed\n"


re: fclean all

.PHONY: all clean fclean re
