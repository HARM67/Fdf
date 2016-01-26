/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 04:34:55 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 04:46:58 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_move_hook(int x, int y, t_app *app)
{
	t_obj *o = app->scene.cur_obj;

	if (app->mouse_1 == 1 && x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (app->maj)
			app->scene.rot = vec4(((app->click.y - y)) / 200 + app->pos_save2.x, ((x - app->click.x)) / 200 + app->pos_save2.y, 0, 1);
		else
			o->rot = vec4(((app->click.y - y)) / 200 + app->pos_save.x, ((x - app->click.x)) / 200 + app->pos_save.y, 0, 1);

		render(app);
	}
	return (0);
}

int	mouse_up_hook(int button, int x, int y, t_app *app)
{
	t_obj *o = app->scene.cur_obj;

	app->pos_save2 = app->scene.rot;
	app->pos_save = o->rot;
	app->mouse_1 = 0;
	return (0);
}

int	mouse_press_hook(int button, int x, int y, t_app *app)
{
	t_obj *o = app->scene.cur_obj;
	t_vec4 *v;

	if (app->maj)
		v = &app->scene.scale;
	else
		v = &o->scale;
	if (button == 1 && x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (app->ray[x + (y * WIDTH)])
			app->scene.cur_obj = app->ray[x + (y * WIDTH)];
	}
	if (button == 6 || button == 4)
	{
		v->x /= 1.2 ;
		v->y /= 1.2 ;
		v->z /= 1.2 ;
		render(app);
	}
	else if (button == 7 || button == 5)
	{
		v->x *= 1.2 ;
		v->y *= 1.2 ;
		v->z *= 1.2 ;
		render(app);
	}
	else if (button == 1 && app->scene.cam.proj != 0 && x > 0 && y > 0 && x < WIDTH && y < HEIGHT)
	{
		app->mouse_1 = 1;
		app->click.x = x;
		app->click.y = y;
		app->pos_save2 = app->scene.rot;
		app->pos_save = app->scene.cur_obj->rot;
	}
	return (0);
}


