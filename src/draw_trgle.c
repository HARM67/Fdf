/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_trgle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 06:18:10 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/25 08:09:21 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	draw_trgle_wired(t_app *app, t_trgle t, int diag, t_obj *o)
{
	t_line l1;
	t_line l2;
	t_line l3;

	l1 = line(t.p[0], t.p[1]);
	l2 = line(t.p[1], t.p[2]);
	l3 = line(t.p[2], t.p[0]);
	draw_line(app, &l1, o);
	draw_line(app, &l2, o);
	if (diag)
		draw_line(app, &l3, o);
}

void	draw_trgle(t_app *app, t_trgle t, t_obj *o)
{
	t_vec4 light;
	float lum;
	t_vec4 normal;
	t_vec4 normal2;

	light.y = 1;
	light.x = -0.5;
	light.z = 0.5;
	light.w = 0;

	normal2 = normalize(t.normal2);
	if (prod_scal(normal2, vec4(0, 0, 1, 0)) < 0 && app->a_culling)
		return ;
	if (app->a_light)
	{
		normal = normalize(t.normal);
		light = normalize(light);
		lum =  prod_scal(normal, light) * app->light_coef;
		if (lum < app->ambient)
			lum = app->ambient;
		t.p[0]->color.r *= lum;
		t.p[0]->color.g *= lum;
		t.p[0]->color.b *= lum;
		t.p[1]->color.r *= lum;
		t.p[1]->color.g *= lum;
		t.p[1]->color.b *= lum;
		t.p[2]->color.r *= lum;
		t.p[2]->color.g *= lum;
		t.p[2]->color.b *= lum;
	}
	app->nb_trgl_draw++;
	rasterization(app, *t.p[0], *t.p[1], *t.p[2], o);
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
	t_vec4	tmp2[3];
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
		tmp[i] = v[i];
		if (proj == 2)
			v[i] = perspective_vec4(app, v[i]);
		tmp2[i] = v[i];
		v[i].z = (v[i].z - app->scene.cam.near) / app->scene.cam.far;
		v[i].x += WIDTH / 2;
		v[i].y += HEIGHT / 2;
		temoin += check_vec4(v[i]);
		rt.p[i] = &v[i];
		i++;
	}
	rt.normal = prod_vec(sous_vec4(tmp[1], tmp[0]), sous_vec4(tmp[2], tmp[0]));
	rt.normal2 = prod_vec(sous_vec4(tmp2[1], tmp2[0]), sous_vec4(tmp2[2], tmp2[0]));
	if (!temoin && app->rem_no_visible)
		return ;
	if (((o->render_type == 4 || o->render_type == 5) && !app->all) ||
			app->render_type == 4 || app->render_type == 5)
		draw_trgle_wired(app, rt, o->render_type - 4, o);
	else
	{
		draw_trgle(app, rt, o);
		draw_trgle_wired(app, rt, (app->all) ? app->render_type - 4 : o->render_type - 4, o);
	}
}
