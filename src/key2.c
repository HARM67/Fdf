/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 08:34:58 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 08:40:53 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_up(int key, t_app *app)
{
	if (key == 257)
		app->maj = 0;
	return (0);
}

int	key_basic_transform(int key, t_app *app)
{
	t_obj *o;

	o = app->scene.cur_obj;
	if (key == 116)
		o->scale.y += 1000;
	else if (key == 121)
		o->scale.y -= 1000;
	else if (key == 126)
		o->pos.z -= 100;
	else if (key == 125)
		o->pos.z += 100;
	else if (key == 123)
		o->pos.x -= 100;
	else if (key == 124)
		o->pos.x += 100;
	else if (key == 36)
		app->all = !app->all;
	else
		return (0);
	render(app);
	return (1);
}

int	key_proj(int key, t_app *app)
{
	float tmp;

	if (key == 18)
	{
		if (app->maj)
			app->scene.cam.proj--;
		else
			app->scene.cam.proj++;
		if (app->scene.cam.proj == 3 || app->scene.cam.proj == 0)
		{
			app->scene.cur_obj->rot = vec4(0, -M_PI / 4, 0, 1);
			tmp = (ABS(app->scene.cam.pos.x) > ABS(app->scene.cam.pos.y))
				? app->scene.cam.pos.x : app->scene.cam.pos.y;
			app->scene.cam.pos = vec4(0, tmp, tmp, 1);
			app->scene.cam.proj = 0;
		}
		else if (app->scene.cam.proj == -1)
			app->scene.cam.proj = 2;
		render(app);
	}
	else
		return (0);
	return (1);
}

int	key_select(int key, t_app *app)
{
	t_obj *o;

	o = app->scene.cur_obj;
	if (key == 48)
	{
		if (!app->maj)
			app->scene.cur_obj = (o->next) ? o->next : app->scene.first_obj;
		else
			app->scene.cur_obj = (o->previous) ? o->previous :
				app->scene.last_obj;
		render(app);
	}
	else
		return (0);
	return (1);
}

int	key_render_type(int key, t_app *app)
{
	t_obj *o;

	o = app->scene.cur_obj;
	if (key == 19)
	{
		if (app->all)
		{
			app->render_type += (app->maj) ? -1 : 1;
			app->render_type = (app->render_type < 0) ? 6 : app->render_type;
			app->render_type = (app->render_type > 6) ? 0 : app->render_type;
		}
		else
		{
			o->render_type += (app->maj) ? -1 : 1;
			o->render_type = (o->render_type < 0) ? 6 : o->render_type;
			o->render_type = (o->render_type > 6) ? 0 : o->render_type;
		}
		render(app);
	}
	else
		return (0);
	return (1);
}
