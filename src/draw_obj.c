/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 08:58:11 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/20 23:35:53 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_dot(t_app *app, t_vec4 v, t_obj *o)
{
	t_trgle	rt;
	int i;

	v = scale_vec4(o->scale, v);
	v = rot_y(o->rot.y, v);
	v = rot_x(o->rot.x, v);
	v = rot_z(o->rot.z, v);
	v = translate_vec4(o->pos, v);
	v = do_cam(app, v);
	v = muli_mat4x4_vec4(perspective(v), v);
	v = translate_vec4(vec4(WIDTH / 2, HEIGHT / 2, 1.0, 1.0), v);
	//v.color = color(255, 255, 255, 255);
	draw_vec4(app, v);
}

void	draw_all_vec4(t_app *app, t_obj *obj)
{
	unsigned int i;

	i = 0;
	while (i < obj->nbr_vecs)
	{
		draw_dot(app, obj->vecs[i], obj);
		i++;
	}
}

void	draw_obj(t_app *app, t_obj *obj)
{
	unsigned int i;

	i = 0;
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

t_matrix4x4 translate_mat(t_vec4 trans)
{
	t_matrix4x4 m;

	m = identity_mat4x4();
	m.n[0][3] = trans.x;
	m.n[1][3] = trans.y;
	m.n[2][3] = trans.z;
	m.n[3][3] = 1.0;
	return (m);
}

t_matrix4x4	scale_mat(t_vec4 scale)
{
	t_matrix4x4 m;

	m = identity_mat4x4();
	m.n[0][0] = scale.x;
	m.n[1][1] = scale.y;
	m.n[2][2] = scale.z;
	m.n[3][3] = 1.0;
	return (m);
}

t_matrix4x4	rot_x_mat(float rot_x)
{
	t_matrix4x4 m;

	m = identity_mat4x4();
	m.n[1][1] = cos(rot_x);
	m.n[1][2] = sin(rot_x);
	m.n[2][1] = -sin(rot_x);
	m.n[2][2] = cos(rot_x);
	return (m);
}

t_matrix4x4 rot_y_mat(float rot_y)
{
	t_matrix4x4 m;

	m = identity_mat4x4();
	m.n[0][0] = cos(rot_y);
	m.n[0][2] = sin(rot_y);
	m.n[2][0] = -sin(rot_y);
	m.n[2][2] = cos(rot_y);
	return (m);
}

t_matrix4x4	rot_z_mat(float rot_z)
{
	t_matrix4x4 m;

	m = identity_mat4x4();
	m.n[0][0] = cos(rot_z);
	m.n[0][1] = -sin(rot_z);
	m.n[1][0] = sin(rot_z);
	m.n[1][1] = cos(rot_z);
	return (m);
}

void	draw_all_obj(t_app *app)
{
	t_obj *tmp;

	tmp = app->scene.first_obj;
	while (tmp)
	{
		tmp->mat = scale_mat(tmp->scale);
		tmp->mat = muli_mat4x4(rot_y_mat(tmp->rot.y), tmp->mat);
		tmp->mat = muli_mat4x4(rot_x_mat(tmp->rot.x), tmp->mat);
		tmp->mat = muli_mat4x4(rot_z_mat(tmp->rot.z), tmp->mat);
		tmp->mat = muli_mat4x4(translate_mat(tmp->pos), tmp->mat);
		if (tmp->render_type == 1)
			draw_all_vec4(app, tmp);
		else
			draw_obj(app, tmp);
		tmp = tmp->next;
	}
}
