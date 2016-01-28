/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 04:47:15 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 14:34:33 by mfroehly         ###   ########.fr       */
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
	else
		mlx_string_put(app->mlx, app->win, 30, 10, 0x808080, "Show_info : <`>");
	app->nb_trgl_draw = 0;
	return (1);
}
