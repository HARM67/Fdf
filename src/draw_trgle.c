/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_trgle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 06:18:10 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/18 14:26:53 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	draw_trgle_wired(t_app *app, t_trgle t)
{
	t_line l1;
	t_line l2;
	t_line l3;

	l1 = line(t.p[0], t.p[1]);
	l2 = line(t.p[1], t.p[2]);
	l3 = line(t.p[2], t.p[0]);
	draw_line(app, &l1);
	draw_line(app, &l2);
	draw_line(app, &l3);
}

void	draw_trgle(t_app *app, t_trgle t)
{
	rasterization(app, *t.p[0], *t.p[1], *t.p[2]);
}

void	draw_trans_wired(t_app *app, t_trgle t, t_obj *o)
{
	t_trgle	rt;
	t_vec4	v[3];
	int i;

	i = 0;
	while (i < 3)
	{
		v[i] = *t.p[i];
		v[i] = scale_vec4(o->scale, v[i]);
		v[i] = rot_y(o->rot.y, v[i]);
		v[i] = rot_x(o->rot.x, v[i]);
		v[i] = rot_z(o->rot.z, v[i]);
		v[i] = translate_vec4(o->pos, v[i]);
		v[i] = do_cam(app, v[i]);
		v[i] = muli_mat4x4_vec4(perspective(v[i]), v[i]);
		v[i] = translate_vec4(vec4(WIDTH / 2, HEIGHT / 2, 1.0, 1.0), v[i]);
		rt.p[i] = &v[i];
		i++;
	}
	draw_trgle(app, rt);
//	draw_trgle_wired(app, rt);
}
