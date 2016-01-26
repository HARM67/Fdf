/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 08:58:11 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 09:33:47 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_obj(t_app *app, t_obj *obj, t_vec4 v1, t_vec4 v2)
{
	float	proj;
	t_line	l;

	proj = app->scene.cam.proj;
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

void	draw_obj(t_app *app, t_obj *obj)
{
	unsigned int	i;
	int				render_type;

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
			draw_trans(app, obj->trgles[i], obj);
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
