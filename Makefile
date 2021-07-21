NAME = miniRT
LIBFT_NAME = libft.a
MINILIBX = libmlx.dylib
MAIN_NAME = miniRT.c
HFILENAME = ./src/miniRT.h

SRC_NAME = miniRT.c miniRT_utils.c miniRT_utils_intersect_figure.c \
	miniRT_utils_new_figure.c \
	miniRT_utils_obj_actions.c miniRT_utils_vector_actions.c \
	miniRT_utils_export.c miniRT_utils_import.c miniRT_utils_debuger.c \
	miniRT_utils_color_palete.c miniRT_utils_color_actions.c \
	miniRT_utils_normal_lighting.c miniRT_utils_raytracing.c \
	miniRT_utils_screenshot.c miniRT_utils_vector_actions1.c \
	miniRT_utils_vector_actions2.c miniRT_utils_raytracing1.c \
	miniRT_utils_obj_actions1.c miniRT_utils_new_figure1.c \
	miniRT_utils_intersect_figure1.c miniRT_utils_import1.c\
	miniRT_utils_import2.c miniRT_utils_import3.c \
	miniRT_utils_import4.c miniRT_utils_export1.c \
	miniRT_utils_export2.c miniRT_utils_export3.c \
	miniRT_utils_debuger1.c miniRT_utils_color_actions1.c \
	miniRT_utils1.c miniRT_utils2.c miniRT_utils3.c miniRT_utils4.c \
	miniRT_utils_hook.c miniRT_utils5.c miniRT_utils6.c miniRT_utils7.c \
	miniRT_utils_close_n_clear.c miniRT_utils_raytracing2.c \
	miniRT_utils_import5.c

CC = gcc

LIB_PATH = ./libft/
MLX_PATH = ./mlx/
SRC_PATH = ./src/
OBJ_PATH = ./obj/

MLX = -Lmlx -lmlx -framework OpenGL -framework Appkit
FLAGS = -Wall -Wextra -Werror -g

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_BONUS_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIBFT = $(addprefix $(LIB_PATH), $(LIBFT_NAME))

all: $(NAME) $(LIB_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c

	@mkdir -p $(OBJ_PATH)
	@printf  "\r%-25s\033[34m[$<]\033[0m\n" "miniRT: $@"
	@$(CC) $(FLAGS) -Imlx -o $@ -c $<
	@printf "\033[A\033[2K"

$(NAME): $(OBJ) $(LIB_PATH) $(HFILENAME)

	@$(MAKE) -C $(LIB_PATH)
	@$(MAKE) -C $(MLX_PATH)
	@cp $(MLX_PATH)$(MINILIBX) .
	@$(CC) $(FLAGS) -lpthread $(LIBFT) $(MLX) $(OBJ) -o $(NAME)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "miniRT: $@"

bonus: all

run: all

	./miniRT --edit

clean:

	@$(MAKE) -C $(LIB_PATH) clean
	@$(MAKE) -C $(MLX_PATH) clean
	@rm -rf $(OBJ_PATH)
	@rm -rf $(MINILIBX)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "miniRT: $@"


fclean: clean

	@$(MAKE) -C $(LIB_PATH) fclean
	@rm -rf $(NAME)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "miniRT: $@"

re: fclean all
