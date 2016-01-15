/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:38:35 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/15 01:05:47 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	app_init(t_app *app)
{
	app->mlx = mlx_init();
	app->win = mlx_new_window(app->mlx, WIDTH, HEIGHT, "42");
}

int	iteration(t_app *app)
{
	t_obj *o = app->scene.first_obj;
	app->scene.cam.pos = vec4(150 /** sin(app->count*/,50 /*50*/, 200 /** cos(app->count)*/, 1);
	app->count += 0.01;
	o->rot = vec4(0.7, 0, app->count * app->count2, 1);
	app->count2 += 0.001;
	mlx_clear_window(app->mlx, app->win);
	draw_all_obj(app);
	return (1);
}

void	app_run(t_app *app)
{
	t_obj *o;
	
	o = new_obj(app, make_cube(1));
	o->pos = vec4(0, 0, 0, 1);
	o->rot = vec4(3, 2, 5, 1);
	o->scale = vec4(30, 30, 30, 5);

	app->count2 = 1.0;
//	t_obj *obj;
	

//	obj = make_cube(1);
	//obj->scale = vec4(10.0, 10.0, 10.0, 1.0);
	//obj->pos = vec4(0.4, 0.5, 50.0, 1.0);
	//`obj->rot = vec4(M_PI / 5, M_PI / 7, M_PI / 6, 1.0);
	//draw_obj(app, app->scene.first_obj);
	//draw_all_obj(app);

	mlx_loop_hook(app->mlx, iteration, app);
	//	MLX_
	mlx_loop(app->mlx);
}

void	app_clean(t_app *app)
{

}
