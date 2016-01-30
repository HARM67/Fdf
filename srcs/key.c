/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 04:54:27 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/30 14:31:34 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_insert_maj(int key, t_app *app)
{
	if (key == 257)
		app->maj = 1;
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
	else
		return (0);
	return (1);
}

int	key_mode(int key, t_app *app)
{
	if (key == 14)
	{
		if (app->maj)
			app->show_depth = !app->show_depth;
		else
			app->a_depth = !app->a_depth;
	}
	else if (key == 15)
		app->a_light = !app->a_light;
	else if (key == 12)
		app->a_culling = !app->a_culling;
	else if (key == 13)
		app->rem_no_visible = !app->rem_no_visible;
	else if (key == 17)
		app->a_picking = !app->a_picking;
	else if (key == 16)
		app->a_prof = !app->a_prof;
	else if (key == 53)
		put_error();
	else
		return (0);
	render(app);
	return (1);
}

int	key_light(int key, t_app *app)
{
	if (key == 69)
	{
		if (app->maj)
			app->ambient += (app->ambient < 1.0) ? 0.1 : 0;
		else
			app->light_coef += (app->light_coef < 1.0) ? 0.1 : 0;
	}
	else if (key == 78)
	{
		if (app->maj)
			app->ambient += (app->ambient > 0.1) ? -0.1 : 0;
		else
			app->light_coef += (app->light_coef > 0.1) ? -0.1 : 0;
	}
	else
		return (0);
	render(app);
	return (1);
}

int	key_down(int key, t_app *app)
{
	t_obj *o;

	o = app->scene.cur_obj;
	if (key_basic_transform(key, app))
		;
	else if (key_proj(key, app))
		;
	else if (key_select(key, app))
		;
	else if (key_render_type(key, app))
		;
	else if (key_insert_maj(key, app))
		;
	else if (key_mode(key, app))
		;
	else if (key_light(key, app))
		;
	else if (key_colors(key, app))
		;
	else if (key_fov(key, app))
		;
	else if (key_print_text(key, app))
		;
	return (0);
}
