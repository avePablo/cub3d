# **************************************************************************** #
#                                  CONFIG                                      #
# **************************************************************************** #

NAME		= cub3D

# Directorios
SRC_DIR		= src
OBJ_DIR		= obj
INCLUDE_DIR	= includes

# Bibliotecas
LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a


# Compilación
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I$(INCLUDE_DIR) -I$(LIBFT_DIR) 

# **************************************************************************** #
#                                 SOURCES                                      #
# **************************************************************************** #

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/parser/parser.c \

# Obtener .o desde .c
#(“Toma cada archivo de $(SRC) que encaje con src/%.c” “Y devuélveme el mismo nombre pero en obj/%.o”)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT_A) -o $(NAME)

# Compilar cada .o en obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # Crea el directorio del archivo .o si no existe
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build las libs externas

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME) $(MAP)

.PHONY: all clean fclean re run