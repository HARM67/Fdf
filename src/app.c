/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:38:35 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/18 12:32:12 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	app_init(t_app *app)
{
	app->mlx = mlx_init();
	app->win = mlx_new_window(app->mlx, WIDTH, HEIGHT, "42");
	app->img = mlx_new_image(app->mlx, WIDTH, HEIGHT);
	app->data = mlx_get_data_addr(app->img, &app->bpp, &app->sizeline, &app->endian);
	ft_bzero(app->data, HEIGHT * WIDTH * 4);
	ft_bzero(app->z_buffer, HEIGHT * WIDTH * 4);
}

int	iteration(t_app *app)
{
	t_obj *o = app->scene.first_obj;

	ft_bzero(app->data, HEIGHT * WIDTH * 4);
	ft_bzero(app->z_buffer, HEIGHT * WIDTH * 4);
	o->rot = vec4(app->count, -app->count / 2, 4 , 1);
	o = o->next;
	o->rot = vec4(app->count, -app->count / 2, 4 , 1);
	app->count += 0.01;
	draw_all_obj(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	return (1);
}

void	app_run(t_app *app)
{
	t_obj *o;

	ft_bzero(app->data, HEIGHT * WIDTH * 4);
	ft_memset(app->z_buffer, 0xff, HEIGHT * WIDTH * 4);
	o = new_obj(app, make_sphere(80, 80));
	o->pos = vec4(0, 0, 0, 1);
	o->rot = vec4(0, 0, 0, 1);
	o->scale = vec4(20, 20, 20, 5);
	o->render_type = 1;
	o = new_obj(app,make_cube(1));
	o->scale = vec4(20, 20, 20, 5);
	o->pos = vec4(0, 0, 0, 1);

	app->scene.cam.pos = vec4(0, 0, -150, 1);
	app->scene.cam.look = vec4(0, 0, 0, 1);
	draw_obj(app, app->scene.first_obj);
	mlx_loop_hook(app->mlx, iteration, app);
	draw_all_obj(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	mlx_loop(app->mlx);
}

void	app_clean(t_app *app)
{

}
