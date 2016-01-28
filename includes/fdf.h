/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 01:43:06 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 10:00:41 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIDTH 1024
# define HEIGHT 768
# include "mlx.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# define ABS(x) ((x > 0) ? x : -x)

typedef struct s_color		t_color;
typedef struct s_vec4		t_vec4;
typedef struct s_vec4_lst	t_vec4_lst;
typedef struct s_line		t_line;
typedef struct s_trgle		t_trgle;
typedef struct s_matrix4x4	t_matrix4x4;
typedef struct s_palette	t_palette;
typedef struct s_obj		t_obj;
typedef struct s_cam		t_cam;
typedef struct s_light		t_light;
typedef struct s_fdf		t_fdf;
typedef struct s_raster		t_raster;
typedef struct s_scene		t_scene;
typedef struct s_app		t_app;

struct 						s_color
{
	unsigned char			r;
	unsigned char			g;
	unsigned char			b;
	unsigned char			a;
};

struct 						s_vec4
{
	float					x;
	float					y;
	float					z;
	float					w;
	t_color					color;
	float					relative_color;
	t_vec4					*next;
};

struct						s_vec4_lst
{
	t_vec4					*first;
	t_vec4					*last;
	unsigned int			size;
	unsigned int			x;
	unsigned int			y;
};

struct						s_fdf
{
	unsigned int			largeur;
	unsigned int			profondeur;
	t_vec4_lst				lst;
	unsigned int			max;
};

struct						s_line
{
	t_vec4					*p[2];
};

struct						s_trgle
{
	t_vec4					*p[3];
	t_vec4					normal;
	t_vec4					normal2;
	t_vec4					tmp;
	t_vec4					tmp2;
	t_color					color;
	char					have_color;
	char					visible;
};

struct						s_matrix4x4
{
	float					n[4][4];
};

struct						s_obj
{
	char					name[32];
	t_vec4					*vecs;
	t_vec4					*vecs_orig;
	t_line					*lines;
	t_line					*lines2;
	t_trgle					*trgles;
	t_vec4					scale;
	t_vec4					pos;
	t_vec4					rot;
	unsigned int			nbr_vecs;
	unsigned int			nbr_lines;
	unsigned int			nbr_lines2;
	unsigned int			nbr_trgles;
	char					render_type;
	t_obj					*next;
	t_obj					*previous;
	t_color					color;
	char					have_color;
	t_matrix4x4				mat;
	//void					(*obj_color)(t_vec4 *);
	int						obj_color;
};

struct						s_cam
{
	t_vec4					pos;
	t_vec4					look;
	int						proj;
	float					size_para;
	float					fov;
	float					near;
	float					far;
};

struct						s_light
{
	t_vec4					d;
};

struct						s_scene
{
	t_obj					*first_obj;
	t_obj					*last_obj;
	t_obj					*cur_obj;
	t_cam					cam;
	t_vec4					scale;
	t_vec4					pos;
	t_vec4					rot;
	t_matrix4x4				mat;
};

struct						s_raster
{
	t_vec4					u;
	t_vec4					m;
	t_vec4					d;
	t_vec4					a;
	t_vec4					b;
	float					du;
	float					dm;
	float					um;
	float					cursor;
	float					cursor2;
	t_line					l;
};

struct						s_app
{
	int						ac;
	char					**av;
	void					*mlx;
	void					*win;
	t_scene					scene;
	float					count;
	float					count2;
	int						*img;
	char					*data;
	float					z_buffer[WIDTH * HEIGHT];
	t_obj					**ray;
	int						bpp;
	int						sizeline;
	int						endian;
	char					mouse_1;
	t_vec4					pos_save;
	t_vec4					pos_save2;
	t_vec4					click;
	int						maj;
	char					all;
	char					render_type;
	t_color					background;
	int						a_depth;
	int						show_depth;
	int						a_light;
	float					light_coef;
	int						a_culling;
	int						rem_no_visible;
	float					ambient;
	unsigned int			nb_trgl_draw;
	void					(*colors[5])(t_vec4 *);
};

/*
** app.c
*/
void						app_init(t_app *app);
void						app_run(t_app *app);
void						app_clean(t_app *app);

/*
** color.c
*/
unsigned int				colortohex(t_color color);
t_color						color(unsigned char r, unsigned char g,
									unsigned char b, unsigned char a);
t_color						color_pos(t_color c1, t_color c2,
									float position);
void						do_color(t_app *app, t_obj *obj);

/*
** color_palette.c
*/
void						color_map(t_vec4 *v);
void						color_random(t_vec4 *v);
void						color_black_white(t_vec4 *v);
void						color_default(t_vec4 *v);
void						color_black_red(t_vec4 *v);

/*
** colors.c
*/
void						init_colors(t_app *app);
/*
** vec4.c
*/
t_vec4						vec4(float x, float y, float z, float w);
t_vec4						sous_vec4(t_vec4 a, t_vec4 b);
t_vec4						inverse(t_vec4 v);
t_vec4						normalize(t_vec4 v);

/*
** line.c
*/t_line						line(t_vec4 *a, t_vec4 *b);

/*
**draw_vec4.c
*/
void						draw_vec4(t_app *app, t_vec4 tmp, t_obj *obj);

/*
** draw_line.c
*/
void						draw_line(t_app *app, t_line *line, t_obj *o);

/*
** draw_line_obj.c
*/
void						draw_line_obj_1(t_app *app, t_obj *obj,
								int render_type);
void						draw_line_obj_2(t_app *app, t_obj *obj,
								int render_type);

/*
** trgle.c
*/
t_trgle						trgle(t_vec4 *v1, t_vec4 *v2, t_vec4 *v3);
t_obj						*make_trgle(t_vec4 v1, t_vec4 v2, t_vec4 v3);
t_vec4						calc_normal(t_trgle t);

/*
** draw_trgle.c
*/
void						prepare_trgle(t_app *app, t_trgle t, t_obj *o);
void						draw_trans(t_app *app, t_trgle rt, t_obj *o,
								t_vec4 *tmp);
void						draw_trgle_wired(t_app *app, t_trgle t,
								int diag, t_obj *o);
void						draw_trgle(t_app *app, t_trgle t, t_obj *o);
int							check_vec4(t_vec4 v);

/*
** op_mat4x4.c
*/
t_matrix4x4					identity_mat4x4(void);
t_matrix4x4 				muli_mat4x4(t_matrix4x4 a, t_matrix4x4 b);
t_vec4						muli_mat4x4_vec4(t_matrix4x4 m, t_vec4 v);
void						do_transform(t_app *app, t_obj *obj,
								t_matrix4x4 mat);

/*
** movement.c
*/
t_vec4						translate_vec4(t_vec4 trans, t_vec4 v);
t_vec4						scale_vec4(t_vec4 pos, t_vec4 v);
t_vec4						rot_x(float rot_x, t_vec4 v);
t_vec4						rot_y(float rot_y, t_vec4 v);
t_vec4						rot_z(float rot_z, t_vec4 v);

/*
** cube.c
*/
t_obj						*make_cube();

/*
** sphere.c
*/
t_obj						*make_sphere(int row, int col);

/*
** draw_obj.c
*/
void						draw_obj(t_app *app, t_obj *obj);
void						draw_all_obj(t_app *app);

// projection.c
t_matrix4x4					perspective(t_vec4);
t_vec4						perspective_vec4(t_app *app, t_vec4 v);

/*
** prod_scal.c
*/
float						prod_scal(t_vec4 v1, t_vec4 v2);

/*
** cam.c
*/
t_cam						new_cam(t_app *app);
t_matrix4x4					cam_mat(t_app *app);

/*
**  obj.c
*/
t_obj						*new_obj(t_app *app, t_obj *o);
t_vec4						do_cam(t_app *app, t_vec4 v);

/*
** prod_vec.c
*/
t_vec4						prod_vec(t_vec4 a, t_vec4 b);

/*
** rasterization.c
*/
void						rasterization(t_app *app, t_trgle t, t_obj *o);

/*
** rasterization_util.c
*/
t_vec4						*up(t_vec4 *v1, t_vec4 *v2, t_vec4 *v3);
t_vec4						*down(t_vec4 *v1, t_vec4 *v2, t_vec4 *v3);
t_vec4						*middle(t_vec4 *v1, t_vec4 *v2, t_vec4 *v3);

/*
** fdf.c
*/
t_obj						*read_fdf(t_app *app, char *filename);
void						load_all_fdf(t_app *app);

/*
** fdf2.c
*/
void						clean_fdf(t_fdf *fdf);
void						fdf_lst_to_array(t_obj *o, t_fdf *fdf);
void						make_fdf_trgle(t_obj *o, t_fdf *fdf);
void						make_fdf_line(t_obj *o, t_fdf *fdf);
void						make_fdf_line2(t_obj *o, t_fdf *fdf);

/*
** vec4_lst.c
*/
t_vec4						*new_vec4(t_vec4 c);
void						push_back_vec4(t_vec4_lst *lst, t_vec4 *elem);

/*
** mov_mat.c
*/
t_matrix4x4 				translate_mat(t_vec4 trans);
t_matrix4x4					scale_mat(t_vec4 scale);
t_matrix4x4					rot_x_mat(float rot_x);
t_matrix4x4 				rot_y_mat(float rot_y);
t_matrix4x4					rot_z_mat(float rot_z);

/*
** draw_scene.c
*/
void						do_scene_transform(t_app *app, t_scene *scn);
void						draw_scene(t_app *app);

/*
** draw_vec4.c
*/
void						ray_trace(t_app *app, t_vec4 tmp, t_obj *obj);
void						draw_all_vec4(t_app *app, t_obj *obj);

/*
** scene.c
*/
void						scene_init(t_app *app);

/*
** mouse.c
*/
int							mouse_move_hook(int x, int y, t_app *app);
int							mouse_up_hook(int button, int x, int y,
								t_app *app);
int							mouse_press_hook(int button, int x, int y,
								t_app *app);

/*
** render.c
*/
int							render(t_app *app);

/*
** text.c
*/
void						print_text(t_app *app);

/*
** buffer.c
*/
void						reset_buffer(t_app *app);
void						show_z_buffer(t_app *app);

/*
** insert_object.c
*/
void						insert_sphere(t_app *app);
void						insert_cube(t_app *app);

/*
** key.c
*/
int							key_up(int key, t_app *app);
int							key_down(int key, t_app *app);

/*
** key2.c
*/
int							key_up(int key, t_app *app);
int							key_basic_transform(int key, t_app *app);
int							key_proj(int key, t_app *app);
int							key_select(int key, t_app *app);
int							key_render_type(int key, t_app *app);

/*
** key3.c
*/
int							key_colors(int key, t_app *app);
int							key_fov(int key, t_app *app);

/*
** light.c
*/
void						do_light(t_app *app, t_trgle t);
#endif
