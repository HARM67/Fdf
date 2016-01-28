SRC_PATH=./src/
SRC=main.c

all:
	gcc -o fdf -g \
		$(SRC_PATH)main.c \
		$(SRC_PATH)app.c \
		$(SRC_PATH)draw_vec4.c \
		$(SRC_PATH)color.c \
		$(SRC_PATH)colors.c \
		$(SRC_PATH)color_palette.c \
		$(SRC_PATH)vec4.c \
		$(SRC_PATH)draw_line.c \
		$(SRC_PATH)draw_line_obj.c \
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
		$(SRC_PATH)rasterization_util.c \
		$(SRC_PATH)sphere.c \
		$(SRC_PATH)fdf.c \
		$(SRC_PATH)fdf2.c \
		$(SRC_PATH)vec4_lst.c \
		$(SRC_PATH)mov_mat.c \
		$(SRC_PATH)draw_scene.c \
		$(SRC_PATH)scene.c \
		$(SRC_PATH)mouse.c \
		$(SRC_PATH)render.c \
		$(SRC_PATH)text.c \
		$(SRC_PATH)buffer.c \
		$(SRC_PATH)insert_object.c \
		$(SRC_PATH)key.c \
		$(SRC_PATH)key2.c \
		$(SRC_PATH)key3.c \
		$(SRC_PATH)light.c \
	 	get_next_line.c -I./ft_printf/includes/ -I./includes -L./ft_printf -L./minilibx_macos -framework OpenGL -framework AppKit -lmlx -lftprintf
