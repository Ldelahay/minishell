# Nom de l'exécutable
NAME = minishell

# Répertoires
SRC_DIR = src
OBJ_DIR = obj

# Fichiers sources et objets
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) #changer le wildcard avant de rendre le projet
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
LDFLAGS = -lreadline -lncurses  

# Header
HEAD = inc/minishell.h -I/usr/local/include/readline/readline.h

# Règles
all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ $(LDFLAGS)  

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
