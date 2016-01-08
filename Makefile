
all:
	gcc -o fdf main.c -L./minilibx_macos -framework OpenGL -framework AppKit -lmlx
