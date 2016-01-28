/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 07:12:20 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 07:14:54 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line_obj(t_app *app, t_obj *obj, t_vec4 v1, t_vec4 v2)
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

void	draw_line_obj_1(t_app *app, t_obj *obj, int render_type)
{
	int i;

	i = 0;
	if (render_type == 1 || render_type == 3)
		while (i < obj->nbr_lines)
		{
			draw_line_obj(app, obj, *obj->lines[i].p[0], *obj->lines[i].p[1]);
			i++;
		}
}

void	draw_line_obj_2(t_app *app, t_obj *obj, int render_type)
{
	int i;

	i = 0;
	if (render_type == 2 || render_type == 3)
		while (i < obj->nbr_lines2)
		{
			draw_line_obj(app, obj, *obj->lines2[i].p[0], *obj->lines2[i].p[1]);
			i++;
		}
}
