/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 08:58:11 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/23 10:33:33 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	do_transform(t_app *app, t_obj *obj, t_matrix4x4 mat)
{
	int i;
	float proj;

	i = 0;
	proj = app->scene.cam.proj;
	obj->mat = scale_mat(obj->scale);
//	obj->mat = muli_mat4x4(scale_mat(obj->scale), mat);
	obj->mat = muli_mat4x4(rot_y_mat(obj->rot.y), obj->mat);
	obj->mat = muli_mat4x4(rot_x_mat(obj->rot.x), obj->mat);
	obj->mat = muli_mat4x4(rot_z_mat(obj->rot.z), obj->mat);
	obj->mat = muli_mat4x4(translate_mat(obj->pos), obj->mat);
	obj->mat = muli_mat4x4(mat, obj->mat);
	obj->mat = muli_mat4x4(cam_mat(app), obj->mat);
	while (i < obj->nbr_vecs)
	{
		obj->vecs[i] = muli_mat4x4_vec4(obj->mat, obj->vecs_orig[i]);
		i++;
	}
}

void	draw_dot(t_app *app, t_vec4 v, t_obj *o)
{
	t_trgle	rt;
	t_vec4	tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	//v = translate_vec4(vec4(WIDTH / 2, HEIGHT / 2, 1.0, 1.0), v);
	v.x += WIDTH / 2;
	v.y += HEIGHT / 2;
	while (i < 3)
	{
		while (j < 3)
		{
			tmp = vec4(v.x - 1 + i, v.y - 1 + j, v.z, v.w);
			tmp.color = v.color;
			draw_vec4(app, tmp, o);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_line_obj(t_app *app, t_obj *obj, t_vec4 v1, t_vec4 v2)
{
	float proj;
	t_line l;

	proj = app->scene.cam.proj;
//	v1 = muli_mat4x4_vec4(obj->mat, v1);
//	v2 = muli_mat4x4_vec4(obj->mat, v2);
	if (proj == 2)
	{
		v1 = perspective_vec4(app, v1);
		v2 = perspective_vec4(app, v2);
	}
	l.p[0] = &v1;
	l.p[1] = &v2;
	v1.x += WIDTH / 2;
	v1.y += HEIGHT / 2;
	v2.x += WIDTH / 2;
	v2.y += HEIGHT / 2;
	if (!check_vec4(v1) && !check_vec4(v2))
		return ;
	draw_line(app, &l, obj);
}

void	draw_all_line(t_app *app, t_obj *obj, int render_type)
{
	unsigned int i;
	i = 0;
	if (render_type == 1 || render_type == 3)
		while (i < obj->nbr_lines)
		{
			draw_line_obj(app, obj, *obj->lines[i].p[0], *obj->lines[i].p[1]);
			i++;
		}
	i = 0;
	if (render_type == 2 || render_type == 3)
		while (i < obj->nbr_lines2)
		{
			draw_line_obj(app, obj, *obj->lines2[i].p[0], *obj->lines2[i].p[1]);
			i++;
		}
}

void	draw_all_vec4(t_app *app, t_obj *obj)
{
	unsigned int i;
	t_vec4 v;
	float proj;

	i = 0;
/*
	proj = app->scene.cam.proj;
	
	obj->mat = scale_mat(obj->scale);
	obj->mat = muli_mat4x4(rot_y_mat(obj->rot.y), obj->mat);
	obj->mat = muli_mat4x4(rot_x_mat(obj->rot.x), obj->mat);
	obj->mat = muli_mat4x4(rot_z_mat(obj->rot.z), obj->mat);
	obj->mat = muli_mat4x4(translate_mat(obj->pos), obj->mat);
	obj->mat = muli_mat4x4(cam_mat(app), obj->mat);
*/	while (i < obj->nbr_vecs)
	{
//		v = obj->vecs[i];
//		v = muli_mat4x4_vec4(obj->mat, v);
		if (proj == 2)
			obj->vecs[i] = perspective_vec4(app, obj->vecs[i] );

		draw_dot(app, obj->vecs[i], obj);
		i++;
	}
}

void	draw_obj(t_app *app, t_obj *obj)
{
	unsigned int i;
	int render_type;

	i = 0;
	if (app->all)
	{
		do_transform(app, obj, app->scene.mat);
		render_type = app->render_type;
	}
	else
	{
		do_transform(app, obj, identity_mat4x4());
		render_type = obj->render_type;
	}
	if (render_type == 0)
		draw_all_vec4(app, obj);
	else if (render_type >= 1 && render_type <= 3)
		draw_all_line(app, obj, render_type);
	else
	{
		while (i < obj->nbr_trgles)
		{
			if (obj->have_color == 1)
			{
				obj->trgles[i].have_color = 1;
				obj->trgles[i].color = obj->color;
			}
			draw_trans_wired(app, obj->trgles[i], obj);
			i++;
		}
	}
}

void	draw_all_obj(t_app *app)
{
	t_obj *tmp;

	tmp = app->scene.first_obj;
	while (tmp)
	{
		draw_obj(app, tmp);
		tmp = tmp->next;
	}
}
