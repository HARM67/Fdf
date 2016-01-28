/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 08:58:11 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 13:27:29 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_all_line(t_app *app, t_obj *obj, int render_type)
{
	float			proj;
	unsigned int	i;

	i = 0;
	proj = app->scene.cam.proj;
	while (i < obj->nbr_vecs)
	{
		if (proj == 2)
			obj->vecs[i] = perspective_vec4(app, obj->vecs[i]);
		obj->vecs[i].z = (obj->vecs[i].z - app->scene.cam.near) /
			app->scene.cam.far;
		i++;
	}
	draw_line_obj_1(app, obj, render_type);
	draw_line_obj_2(app, obj, render_type);
}

void	draw_obj2(t_app *app, t_obj *obj, int render_type)
{
	unsigned int	i;

	i = 0;
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
			prepare_trgle(app, obj->trgles[i], obj);
			i++;
		}
	}
}

void	draw_obj(t_app *app, t_obj *obj)
{
	int	render_type;

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
	draw_obj2(app, obj, render_type);
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
