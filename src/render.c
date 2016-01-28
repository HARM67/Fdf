/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 04:47:15 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 13:32:42 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	render(t_app *app)
{
	t_obj *o;

	o = app->scene.cur_obj;
	reset_buffer(app);
	if (app->all)
		draw_scene(app);
	else
		draw_obj(app, o);
	if (app->show_depth)
	{
		ft_bzero(app->data, HEIGHT * WIDTH * 4);
		show_z_buffer(app);
	}
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	if (app->print_text)
		print_text(app);
	app->nb_trgl_draw = 0;
	return (1);
}
