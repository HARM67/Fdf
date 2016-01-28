/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vec4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:52:30 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 14:28:10 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_vec4(t_app *app, t_vec4 tmp, t_obj *o)
{
	if ((int)tmp.y <= 0 || (int)tmp.y > HEIGHT - 2 || (int)tmp.x < 0 ||
			(int)tmp.x > WIDTH - 2)
		return ;
	if (app->z_buffer[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))]
			< tmp.z && app->a_depth)
		return ;
	app->z_buffer[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))] =
		tmp.z;
	app->data[(int)(tmp.y + 0.5) * 4 * WIDTH + (int)(tmp.x + 0.5) * 4] =
		tmp.color.b * (1 - tmp.z);
	app->data[(int)(tmp.y + 0.5) * 4 * WIDTH + (int)(tmp.x + 0.5) * 4 + 1] =
		tmp.color.g * (1 - tmp.z);
	app->data[(int)(tmp.y + 0.5) * 4 * WIDTH + (int)(tmp.x + 0.5) * 4 + 2] =
		tmp.color.r * (1 - tmp.z);
	if (!app->a_picking)
		return ;
	app->ray[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))] = o;
}

static void	draw_dot(t_app *app, t_vec4 v, t_obj *o)
{
	t_vec4	tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
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

void		draw_all_vec4(t_app *app, t_obj *obj)
{
	unsigned int	i;
	float			proj;

	proj = app->scene.cam.proj;
	i = 0;
	while (i < obj->nbr_vecs)
	{
		if (proj == 2)
			obj->vecs[i] = perspective_vec4(app, obj->vecs[i]);
		obj->vecs[i].z = (obj->vecs[i].z - app->scene.cam.near) /
			app->scene.cam.far;
		draw_dot(app, obj->vecs[i], obj);
		i++;
	}
}
