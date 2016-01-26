/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 13:46:53 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 09:45:43 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vec4	*up(t_vec4 *v1, t_vec4 *v2, t_vec4 *v3)
{
	t_vec4	*rt;

	rt = v1;
	if (rt->y < v2->y)
		rt = v2;
	if (rt->y < v3->y)
		rt = v3;
	return (rt);
}

static t_vec4	*down(t_vec4 *v1, t_vec4 *v2, t_vec4 *v3)
{
	t_vec4	*rt;

	rt = v3;
	if (rt->y > v2->y)
		rt = v2;
	if (rt->y > v1->y)
		rt = v1;
	return (rt);
}

static t_vec4	*middle(t_vec4 *v1, t_vec4 *v2, t_vec4 *v3)
{
	if (v1 != up(v1, v2, v3) && v1 != down(v1, v2, v3))
		return (v1);
	if (v2 != up(v1, v2, v3) && v2 != down(v1, v2, v3))
		return (v2);
	if (v3 != up(v1, v2, v3) && v3 != down(v1, v2, v3))
		return (v3);
	return (v3);
}

void			rasterization(t_app *app, t_trgle t, t_obj *o)
{
	t_vec4	u;
	t_vec4	m;
	t_vec4	d;
	t_vec4	a;
	t_vec4	b;
	float	du;
	float	dm;
	float	um;
	float	cursor;
	float	cursor2;
	t_line	l;

	cursor = 0;
	cursor2 = 0;
	u = *up(t.p[0], t.p[1], t.p[2]);
	d = *down(t.p[0], t.p[1], t.p[2]);
	m = *middle(t.p[0], t.p[1], t.p[2]);
	dm = (m.x - d.x) / (m.y - d.y);
	du = (u.x - d.x) / (u.y - d.y);
	um = (u.x - m.x) / (u.y - m.y);
	while (cursor < m.y - d.y)
	{
		a = vec4(d.x + (cursor * dm), cursor + d.y,
				d.z + cursor * (m.z - d.z) / (m.y - d.y), 1);
		b = vec4(d.x + (cursor * du), cursor + d.y,
				d.z + cursor * (u.z - d.z) / (u.y - d.y), 1);
		a.color = color_pos(m.color, d.color, cursor / (m.y - d.y));
		b.color = color_pos(u.color, d.color, cursor / (u.y - d.y));
		l = line(&a, &b);
		draw_line(app, &l, o);
		cursor += 1.0;
	}
	cursor2 = 0;
	while (cursor < u.y - d.y)
	{
		a = vec4(m.x + (cursor2 * um), cursor + d.y,
				m.z + cursor2 * (u.z - m.z) / (u.y - m.y), 1);
		b = vec4(d.x + (cursor * du), cursor + d.y,
				d.z + cursor * (u.z - d.z) / (u.y - d.y), 1);
		a.color = color_pos(u.color, m.color, cursor2 / (u.y - m.y));
		b.color = color_pos(u.color, d.color, cursor / (u.y - d.y));
		l = line(&a, &b);
		draw_line(app, &l, o);
		cursor += 1.0;
		cursor2 += 1.0;
	}
}
