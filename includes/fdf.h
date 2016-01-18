/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 01:43:06 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/18 12:09:49 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIDTH 1024
# define HEIGHT 768
# include "mlx.h"
# include "ft_printf.h"
# include <math.h>
# define ABS(x) ((x > 0) ? x : -x)

typedef struct s_color		t_color;
typedef struct s_vec4		t_vec4;
typedef struct s_line		t_line;
typedef struct s_trgle		t_trgle;
typedef struct s_matrix4x4	t_matrix4x4;
typedef struct s_obj		t_obj;
typedef struct s_cam		t_cam;
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
};

struct						s_line
{
	t_vec4					*p[2];
};

struct						s_trgle
{
	t_vec4					*p[3];
	t_vec4					normal;
};

struct						s_matrix4x4
{
	float					n[4][4];
};

struct						image
{

};

struct						s_obj
{
	t_vec4					*vecs;
	t_line					*lines;
	t_trgle					*trgles;
	t_vec4					scale;
	t_vec4					pos;
	t_vec4					rot;
	unsigned int			nbr_vecs;
	unsigned int			nbr_lines;
	unsigned int			nbr_trgles;
	char					render_type;
	t_obj					*next;
	t_obj					*previous;
};

struct s_cam
{
	t_vec4					pos;
	t_vec4					look;
};

struct						s_scene
{
	t_obj					*first_obj;
	t_obj					*last_obj;
	t_cam					cam;
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
	int						bpp;
	int						sizeline;
	int						endian;
};

// app.c
void						app_init(t_app *app);
void						app_run(t_app *app);
void						app_clean(t_app *app);

// color.c
unsigned int				colortohex(t_color color);
t_color						color(unsigned char r, unsigned char g,
									unsigned char b, unsigned char a);
t_color						color_pos(t_color c1, t_color c2,
									float position);

// vec4.c
t_vec4						vec4(float x, float y, float z, float w);
t_vec4						sous_vec4(t_vec4 a, t_vec4 b);
t_vec4						inverse(t_vec4 v);
t_vec4						normalize(t_vec4 v);

// line.c
t_line						line(t_vec4 *a, t_vec4 *b);
// draw_vec4.c
void						draw_vec4(t_app *app, t_vec4 tmp);

// draw_line.c
void						draw_line(t_app *app, t_line *line);

// trgle.c
t_trgle						trgle(t_vec4 *v1, t_vec4 *v2, t_vec4 *v3);
t_obj						*make_trgle(t_vec4 v1, t_vec4 v2, t_vec4 v3);

// draw_trgle.c
void						draw_trans_wired(t_app *app, t_trgle t, t_obj *o);
void						draw_trgle_wired(t_app *app, t_trgle t);
void						draw_trgle(t_app *app, t_trgle t);

// op_mat4x4.c
t_matrix4x4					identity_mat4x4(void);
t_matrix4x4 				muli_mat4x4(t_matrix4x4 a, t_matrix4x4 b);
t_vec4						muli_mat4x4_vec4(t_matrix4x4 m, t_vec4 v);

// movement.c
t_vec4						translate_vec4(t_vec4 trans, t_vec4 v);
t_vec4						scale_vec4(t_vec4 pos, t_vec4 v);
t_vec4						rot_x(float rot_x, t_vec4 v);
t_vec4						rot_y(float rot_y, t_vec4 v);
t_vec4						rot_z(float rot_z, t_vec4 v);

// cube.c
t_obj						*make_cube();

/*
** sphare.c
*/
t_obj						*make_sphere(int row, int col);

// draw_obj.c
void						draw_obj(t_app *app, t_obj *obj);
void						draw_all_obj(t_app *app);

// projection.c
t_matrix4x4					perspective(t_vec4);

// prod_scal.c
float						prod_scal(t_vec4 v1, t_vec4 v2);

// cam.c
t_cam						new_cam(t_app *app);

// obj.c
t_obj						*new_obj(t_app *app, t_obj *o);
t_vec4						do_cam(t_app *app, t_vec4 v);

// prod_vec.c
t_vec4						prod_vec(t_vec4 a, t_vec4 b);

/*
** rasterization.c
*/
void						rasterization(t_app *app, t_vec4 v1, t_vec4 v2, t_vec4 v3);
#endif
