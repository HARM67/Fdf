/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 04:47:15 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 04:47:46 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	render(t_app *app)
{
	t_obj *o = app->scene.cur_obj;

	app->count += 0.01;
	//ft_bzero(app->data, HEIGHT * WIDTH * 4);
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
	print_text(app);
	app->nb_trgl_draw = 0;
	return (1);
}
