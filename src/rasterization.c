/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 13:46:53 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 14:23:53 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void			init_raster(t_raster *r, t_trgle t)
{
	r->cursor = 0;
	r->cursor2 = 0;
	r->u = *up(t.p[0], t.p[1], t.p[2]);
	r->d = *down(t.p[0], t.p[1], t.p[2]);
	r->m = *middle(t.p[0], t.p[1], t.p[2]);
	r->dm = (r->m.x - r->d.x) / (r->m.y - r->d.y);
	r->du = (r->u.x - r->d.x) / (r->u.y - r->d.y);
	r->um = (r->u.x - r->m.x) / (r->u.y - r->m.y);
}

static void		rasterization2(t_app *app, t_obj *o, t_raster r)
{
	r.cursor2 = 0;
	while (r.cursor < r.u.y - r.d.y)
	{
		r.a = vec4(r.m.x + (r.cursor2 * r.um), r.cursor + r.d.y,
				r.m.z + r.cursor2 * (r.u.z - r.m.z) / (r.u.y - r.m.y), 1);
		r.b = vec4(r.d.x + (r.cursor * r.du), r.cursor + r.d.y,
				r.d.z + r.cursor * (r.u.z - r.d.z) / (r.u.y - r.d.y), 1);
		r.a.color = color_pos(r.u.color, r.m.color, r.cursor2 / (r.u.y - r.m.y));
		r.b.color = color_pos(r.u.color, r.d.color, r.cursor / (r.u.y - r.d.y));
		r.l = line(&r.a, &r.b);
		draw_line(app, &r.l, o);
		r.cursor += 1.0;
		r.cursor2 += 1.0;
	}
}

void			rasterization(t_app *app, t_trgle t, t_obj *o)
{
	t_raster r;

	init_raster(&r, t);
	while (r.cursor < r.m.y - r.d.y)
	{
		r.a = vec4(r.d.x + (r.cursor * r.dm), r.cursor + r.d.y,
				r.d.z + r.cursor * (r.m.z - r.d.z) / (r.m.y - r.d.y), 1);
		r.b = vec4(r.d.x + (r.cursor * r.du), r.cursor + r.d.y,
				r.d.z + r.cursor * (r.u.z - r.d.z) / (r.u.y - r.d.y), 1);
		r.a.color = color_pos(r.m.color, r.d.color, r.cursor / (r.m.y - r.d.y));
		r.b.color = color_pos(r.u.color, r.d.color, r.cursor / (r.u.y - r.d.y));
		r.l = line(&r.a, &r.b);
		draw_line(app, &r.l, o);
		r.cursor += 1.0;
	}
	rasterization2(app, o, r);
}
