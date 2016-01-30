NAME = fdf
INCLUDES=./includes
INCLUDES_FT_PRINTF=./ft_printf/includes
COMPILER = gcc
LIB=./ft_printf/
SRCS=main.c app.c draw_vec4.c color.c colors.c color_palette.c \
		color_palette2.c vec4.c draw_line.c draw_line_obj.c \
		line.c trgle.c draw_trgle.c op_mat4x4.c movement.c cube.c draw_obj.c \
		projection.c prod_scal.c cam.c obj.c prod_vec.c rasterization.c \
		rasterization_util.c sphere.c fdf.c fdf2.c vec4_lst.c \
		mov_mat.c draw_scene.c scene.c mouse.c render.c text.c text2.c \
		buffer.c insert_object.c key.c key2.c key3.c light.c error.c \
		get_next_line.c
SRC_PATH=./srcs/
OBJ=$(SRCS:.c=.o)
FLAG=-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(LIB)libftprintf.a $(INCLUDES)/get_next_line.h $(INCLUDES_FT_PRINTF)/ft_printf.h \
	$(INCLUDES)/fdf.h $(OBJ)
	$(COMPILER) -o $(NAME) -I$(INCLUDES_FT_PRINTF) -I$(INCLUDES) $(OBJ) -L$(LIB) -lftprintf \
		-L./minilibx_macos -framework OpenGL -framework AppKit -lmlx

%.o: $(SRC_PATH)%.c
	$(COMPILER) -c $(FLAG) $< -I$(INCLUDES_FT_PRINTF) -I$(INCLUDES)

$(LIB)libftprintf.a:
	make -C $(LIB)
	make clean -C $(LIB)

.PHONY: clean fclean re

clean:
	make clean -C $(LIB)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIB)
	rm -f $(NAME)

re: fclean $(NAME)

