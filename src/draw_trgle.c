/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_trgle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 06:18:10 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/23 03:31:32 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	draw_trgle_wired(t_app *app, t_trgle t, int diag)
{
	t_line l1;
	t_line l2;
	t_line l3;

	l1 = line(t.p[0], t.p[1]);
	l2 = line(t.p[1], t.p[2]);
	l3 = line(t.p[2], t.p[0]);
	draw_line(app, &l1);
	draw_line(app, &l2);
	if (diag)
		draw_line(app, &l3);
}

void	draw_trgle(t_app *app, t_trgle t)
{
	t_vec4 light;
	float lum;

	light.y = 1;
	light.x = -0.5;
	light.z = 0.4;


	//ft_printf("%f %f %f\n", t.normal.x, t.normal.y, t.normal.z);
//	ft_printf("%f\n", prod_scal(normalize(t.normal), normalize(light)));
	lum = prod_scal(normalize(t.normal), normalize(light));
	if (lum < 0.6)
		lum = 0.6;
	t.p[0]->color.r *= lum;
	t.p[0]->color.g *= lum;
	t.p[0]->color.b *= lum;
	t.p[1]->color.r *= lum;
	t.p[1]->color.g *= lum;
	t.p[1]->color.b *= lum;
	t.p[2]->color.r *= lum;
	t.p[2]->color.g *= lum;
	t.p[2]->color.b *= lum;
	rasterization(app, *t.p[0], *t.p[1], *t.p[2]);
}

int	check_vec4(t_vec4 v)
{
	if (v.x < 0 || v.x > WIDTH || v.y < 0 || v.y > HEIGHT || v.z < 0)
		return (0);
	return (1);
}


void	draw_trans_wired(t_app *app, t_trgle t, t_obj *o)
{
	t_trgle	rt;
	t_vec4	v[3];
	t_vec4	tmp[3];
	int i;
	int temoin;
	int	proj;

	proj = app->scene.cam.proj;
	temoin = 0;
	i = 0;
	while (i < 3)
	{
		v[i] = *t.p[i];
		if (t.have_color == 1)
		{
			v[i].color = t.color;
		}
		v[i] = muli_mat4x4_vec4(o->mat, v[i]);
		tmp[i] = v[i];
		if (proj == 2)
			v[i] = perspective_vec4(app, v[i]);
		v[i].x += WIDTH / 2;
		v[i].y += HEIGHT / 2;
		temoin += check_vec4(v[i]);
		rt.p[i] = &v[i];
		i++;
	}
	rt.normal = prod_vec(sous_vec4(tmp[1], tmp[0]), sous_vec4(tmp[2], tmp[0]));
	if (!temoin)
		return ;
	if (o->render_type == 4 || o->render_type == 5)
		draw_trgle_wired(app, rt, o->render_type - 4);
	else
	{
		draw_trgle(app, rt);
		draw_trgle_wired(app, rt, o->render_type - 4);
	}
}
