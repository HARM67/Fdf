/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 08:58:11 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/21 22:03:06 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_dot(t_app *app, t_vec4 v, t_obj *o)
{
	t_trgle	rt;
	int i;

	v = translate_vec4(vec4(WIDTH / 2, HEIGHT / 2, 1.0, 1.0), v);
	//v.color = color(255, 255, 255, 255);
	draw_vec4(app, v);
}

void	draw_all_vec4(t_app *app, t_obj *obj)
{
	unsigned int i;
	t_vec4 *v;
	float proj;

	v = obj->vecs;
	i = 0;

	proj = app->scene.cam.proj;
	/*
	obj->mat = scale_mat(obj->scale);
	obj->mat = muli_mat4x4(rot_y_mat(obj->rot.y), obj->mat);
	obj->mat = muli_mat4x4(rot_x_mat(obj->rot.x), obj->mat);
	obj->mat = muli_mat4x4(rot_z_mat(obj->rot.z), obj->mat);
	obj->mat = muli_mat4x4(translate_mat(obj->pos), obj->mat);
	obj->mat = muli_mat4x4(cam_mat(app), obj->mat);
*/	while (i < obj->nbr_vecs)
	{
		v[i] = muli_mat4x4_vec4(obj->mat, v[i]);
		if (proj == 2)
			v[i] = perspective_vec4(app, v[i]);

		draw_dot(app, obj->vecs[i], obj);
		i++;
	}
}

void	draw_obj(t_app *app, t_obj *obj)
{
	unsigned int i;

	i = 0;
	if (obj->render_type)
		draw_all_vec4(app, obj);
	else
	while (i < obj->nbr_trgles)
	{
		obj->mat = scale_mat(obj->scale);
		obj->mat = muli_mat4x4(rot_y_mat(obj->rot.y), obj->mat);
		obj->mat = muli_mat4x4(rot_x_mat(obj->rot.x), obj->mat);
		obj->mat = muli_mat4x4(rot_z_mat(obj->rot.z), obj->mat);
		obj->mat = muli_mat4x4(translate_mat(obj->pos), obj->mat);
		obj->mat = muli_mat4x4(cam_mat(app), obj->mat);
		if (obj->have_color == 1)
		{
			obj->trgles[i].have_color = 1;
			obj->trgles[i].color = obj->color;
		}
		draw_trans_wired(app, obj->trgles[i], obj);
		i++;
	}
}


void	draw_all_obj(t_app *app)
{
	t_obj *tmp;

	tmp = app->scene.first_obj;
	while (tmp)
	{
		if (tmp->render_type == 1)
			draw_all_vec4(app, tmp);
		else
			draw_obj(app, tmp);
		tmp = tmp->next;
	}
}
