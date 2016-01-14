/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:38:35 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/14 20:17:46 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	app_init(t_app *app)
{
	app->mlx = mlx_init();
	app->win = mlx_new_window(app->mlx, WIDTH, HEIGHT, "42");
}

void	app_run(t_app *app)
{
	t_obj *o;
	
	o = new_obj(app, make_cube(1));
	o->scale = vec4(5, 5, 5, 5);
	o->pos = vec4(5.0, 0, -75, 1);
	o = new_obj(app, make_cube(1));
	o->pos = vec4(-3.0, -5, -50, 1);
	o->scale = vec4(5, 5, 5, 5);
	app->scene.cam.pos = vec4(5, 5, 500, 1);
	app->scene.cam.look = vec4(5, 0, -75, 1);
//	t_obj *obj;
	

//	obj = make_cube(1);
	//obj->scale = vec4(10.0, 10.0, 10.0, 1.0);
	//obj->pos = vec4(0.4, 0.5, 50.0, 1.0);
	//`obj->rot = vec4(M_PI / 5, M_PI / 7, M_PI / 6, 1.0);
	//draw_obj(app, app->scene.first_obj);
	draw_all_obj(app);

	mlx_loop(app->mlx);
}

void	app_clean(t_app *app)
{

}
