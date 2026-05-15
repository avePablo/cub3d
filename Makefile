# **************************************************************************** #
#                                  CONFIG                                      #
# **************************************************************************** #

NAME        = cub3D

# Directorios
SRC_DIR     = src
OBJ_DIR     = obj
INCLUDE_DIR = includes

# Bibliotecas
LIBFT_DIR   = libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

# MLX42
MLX42_DIR   = MLX42
MLX42_BUILD = $(MLX42_DIR)/build
MLX42_LIB   = $(MLX42_BUILD)/libmlx42.a
MLX42_INC   = -I$(MLX42_DIR)/include
MLX42_DEPS  = $(MLX42_LIB)

# Sanitizers
#SANITIZE = -fsanitize=address -g

# Compilación
CC          = cc
CFLAGS      = -Wall -Wextra -Werror #$(SANITIZE)
INCLUDES    = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

# Librerías adicionales necesarias en Linux
MLX42_LDFLAGS = -lglfw -ldl -lm -lpthread 

# **************************************************************************** #
#                                 SOURCES                                      #
# **************************************************************************** #

SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/exec/init.c \
      $(SRC_DIR)/parser/parser.c \
      $(SRC_DIR)/parser/split_file.c \
	  $(SRC_DIR)/parser/parser_config.c \
	  $(SRC_DIR)/parser/parser_color.c \
	  $(SRC_DIR)/parser/parser_texture.c \
	  $(SRC_DIR)/parser/parser_helper.c \
	  $(SRC_DIR)/parser/validate.c \
	  $(SRC_DIR)/parser/rectangular.c \
	  $(SRC_DIR)/exec/raycast.c \
	  $(SRC_DIR)/exec/raycast_init.c \
	  $(SRC_DIR)/exec/raycast_helper.c \
	  $(SRC_DIR)/exec/raycast_draw.c \
	  $(SRC_DIR)/exec/moves.c \
	  $(SRC_DIR)/exec/textures.c \
	  $(SRC_DIR)/exec/free.c \

OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(NAME)

# ---------------------- Compilar MLX42 ----------------------
$(MLX42_LIB):
	@echo "Compiling MLX42..."
	cmake -B $(MLX42_BUILD) $(MLX42_DIR)
	cmake --build $(MLX42_BUILD) -j4

# ---------------------- Compilar tu proyecto ----------------------
$(NAME): $(LIBFT_A) $(MLX42_DEPS) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT_A) $(MLX42_LIB) $(MLX42_INC) $(MLX42_LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ---------------------- Librerías externas ----------------------
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

# ---------------------- Limpieza ----------------------
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)
	rm -rf $(MLX42_BUILD)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME) $(MAP)

.PHONY: all clean fclean re run