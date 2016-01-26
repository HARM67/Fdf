/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 04:54:27 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 04:58:15 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	key_up(int key, t_app *app)
{
	if (key == 257)
		app->maj = 0;
	return (0);
}

int	key_down(int key, t_app *app)
{
	t_obj *o = app->scene.cur_obj;
	float tmp;

	if (key == 116)
	{
		o->scale.y += 1000;
		render(app);
	}
	else if (key == 121)
	{
		o->scale.y -= 1000;
		render(app);
	}
	else if (key == 126)
	{
		o->pos.z -= 100;
		render(app);
	}
	else if (key == 125)
	{
		o->pos.z += 100;
		render(app);
	}
	else if (key == 123)
	{
		o->pos.x -= 100;
		render(app);
	}
	else if (key == 124)
	{
		o->pos.x += 100;
		render(app);
	}
	else if (key == 36)
	{
		app->all = !app->all;
		render(app);
	}
	else if (key == 18)
	{
		if (app->maj)
			app->scene.cam.proj--;
		else
			app->scene.cam.proj++;
		if (app->scene.cam.proj == 3 || app->scene.cam.proj == 0)
		{
			o->rot = vec4(0, -M_PI / 4, 0, 1);
			tmp = (ABS(app->scene.cam.pos.x) > ABS(app->scene.cam.pos.y))
				? app->scene.cam.pos.x : app->scene.cam.pos.y;
			app->scene.cam.pos = vec4(0, tmp, tmp, 1);
			app->scene.cam.proj = 0;
		}
		else if (app->scene.cam.proj == -1)
			app->scene.cam.proj = 2;

		render(app);
	}
	else if (key == 257)
		app->maj = 1;
	else if (key == 48)
	{
		if (!app->maj)
			app->scene.cur_obj = (o->next) ? o->next : app->scene.first_obj;
		else
			app->scene.cur_obj = (o->previous) ? o->previous : app->scene.last_obj;
		render(app);
	}
	else if (key == 19)
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
	else if (key == 1)
	{
		insert_sphere(app);
		render(app);
	}
	else if (key == 8)
	{
		insert_cube(app);
		render(app);
	}
	else if (key == 2)
	{
		if (app->maj)
			app->show_depth = !app->show_depth;
		else
			app->a_depth = !app->a_depth;
		render(app);
	}
	else if (key == 37)
	{
		app->a_light = !app->a_light;
		render(app);
	}
	else if (key == 12)
	{
		app->a_culling = !app->a_culling;
		render(app);
	}
	else if (key == 13)
	{
		app->rem_no_visible = !app->rem_no_visible;
		render(app);
	}
	else if (key == 69)
	{
		if (app->maj)
		{
			if (app->ambient < 1.0)
				app->ambient += 0.1;
		}
		else
		{
			if (app->light_coef < 1.5)
				app->light_coef += 0.1;
		}
		render(app);
	}
	else if (key == 78)
	{
		if (app->maj)
		{
			if (app->ambient > 0.1)
				app->ambient -= 0.1;
		}
		else
		{
			if (app->light_coef > 0.1)
			app->light_coef -= 0.1;
		}
		render(app);
	}
	ft_printf("%d\n", key);
	return (0);
}
