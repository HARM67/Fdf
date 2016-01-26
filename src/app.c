/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:38:35 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 07:06:45 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	app_init(t_app *app)
{
	app->mlx = mlx_init();
	app->win = mlx_new_window(app->mlx, WIDTH, HEIGHT, "fdf");
	app->img = mlx_new_image(app->mlx, WIDTH, HEIGHT);
	app->data = mlx_get_data_addr(app->img, &app->bpp,
			&app->sizeline, &app->endian);
	ft_bzero(app->data, HEIGHT * WIDTH * 4);
	ft_bzero(app->z_buffer, HEIGHT * WIDTH * 4);
}

void	app_run(t_app *app)
{
	t_obj *o;

	load_all_fdf(app);
	app->ray = (t_obj**)ft_memalloc(sizeof(t_obj*) * HEIGHT * WIDTH);
	scene_init(app);
	mlx_hook(app->win, 6, (1L << 6), mouse_move_hook, app);
	mlx_hook(app->win, 5, (1L << 2), mouse_up_hook, app);
	mlx_mouse_hook(app->win, mouse_press_hook, app);
	mlx_hook(app->win, 2, (1L << 0), key_down, app);
	mlx_hook(app->win, 3, (1L << 1), key_up, app);
	render(app);
	mlx_loop(app->mlx);
}

void	app_clean(t_app *app)
{
}
