/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 08:58:11 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/18 12:35:39 by mfroehly         ###   ########.fr       */
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
	v.color = color(255, 255, 255, 255);
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
