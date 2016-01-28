/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:31:43 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 11:16:50 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_colors(int key, t_app *app)
{
	if (key == 20)
	{
		if (!app->maj)
			app->scene.cur_obj->obj_color++;
		else
			app->scene.cur_obj->obj_color--;
		if (app->scene.cur_obj->obj_color < 0)
			app->scene.cur_obj->obj_color = 4;
		else if (app->scene.cur_obj->obj_color >= 5)
			app->scene.cur_obj->obj_color = 0;
		do_color(app, app->scene.cur_obj);
		render(app);
		return (1);
	}
	return (0);
}

int	key_fov(int key, t_app *app)
{
	if (key == 21)
	{
		if (!app->maj && app->scene.cam.fov > 69.1)
			app->scene.cam.fov -= 0.1 ;
		else if (app->maj && app->scene.cam.fov < 71)
			app->scene.cam.fov += 0.1;
		render(app);
		return (1);
	}
	return (0);
}

int	key_print_text(int key, t_app *app)
{
	if (key == 50)
		app->print_text = !app->print_text;
	render(app);
	return (0);
}
