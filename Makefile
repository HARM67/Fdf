SRC_PATH=./src/
SRC=main.c

all:
	gcc -o fdf -g \
		$(SRC_PATH)main.c \
		$(SRC_PATH)app.c \
		$(SRC_PATH)draw_vec4.c \
		$(SRC_PATH)color.c \
		$(SRC_PATH)vec4.c \
		$(SRC_PATH)draw_line.c \
		$(SRC_PATH)line.c \
		$(SRC_PATH)trgle.c \
		$(SRC_PATH)draw_trgle.c \
		$(SRC_PATH)op_mat4x4.c \
		$(SRC_PATH)movement.c \
		$(SRC_PATH)cube.c \
		$(SRC_PATH)draw_obj.c \
		$(SRC_PATH)projection.c \
		$(SRC_PATH)prod_scal.c \
		$(SRC_PATH)cam.c \
		$(SRC_PATH)obj.c \
		$(SRC_PATH)prod_vec.c \
		$(SRC_PATH)rasterization.c \
		$(SRC_PATH)sphere.c \
		$(SRC_PATH)fdf.c \
		$(SRC_PATH)vec4_lst.c \
		$(SRC_PATH)mov_mat.c \
		$(SRC_PATH)draw_scene.c \
	 	get_next_line.c -I./ft_printf/includes/ -I./includes -L./ft_printf -L./minilibx_macos -framework OpenGL -framework AppKit -lmlx -lftprintf
