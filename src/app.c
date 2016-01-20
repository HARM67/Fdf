/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:38:35 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/20 22:47:26 by mfroehly         ###   ########.fr       */
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

	app->count += 0.01;
	ft_bzero(app->data, HEIGHT * WIDTH * 4);
	ft_memset(app->z_buffer, 0xff, HEIGHT * WIDTH * 4);
	draw_all_obj(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	return (1);
}

int	mouse_move_hook(int x, int y, t_app *app)
{
	t_obj *o = app->scene.first_obj;

	if (app->mouse_1 == 1)
	{
		//app->pos_save = vec4()
		o->rot = vec4(
				((app->click.y - y)) / 200 + app->pos_save.x,
				((x - app->click.x)) / 200 + app->pos_save.y,
				0, 1)
			;
		ft_printf("%f, %f\n", o->rot.x, o->rot.y);
	}
	return (0);
}

int	mouse2(int button, int x, int y, t_app *app)
{
	t_obj *o = app->scene.first_obj;

	//app->pos_save = o->rot;
/*	= vec4(
				(float)-(app->click.y - y - (HEIGHT / 2)) / 200.0,
				(float)-(app->click.x - (x - WIDTH / 2))/200.0, 
				0, 1)
			;
*/	app->mouse_1 = 0;
	return (0);
}

int	mouse_hook(int button, int x, int y, t_app *app)
{
	ft_printf("%d\n", button);
	t_obj *o = app->scene.first_obj;
	if (button == 6 || button == 4)
	{
		app->scene.cam.pos.x *= 1.2;
		app->scene.cam.pos.y *= 1.2;
		app->scene.cam.pos.z *= 1.2;
	}
	else if (button == 7 || button == 5)
	{
		app->scene.cam.pos.x *= 0.8;
		app->scene.cam.pos.y *= 0.8;
		app->scene.cam.pos.z *= 0.8;
	}
	else if (button == 1)
	{
		app->mouse_1 = 1;
		app->click.x = x;
		app->click.y = y;
		app->pos_save = o->rot;
	}
	return (0);
}

void	app_run(t_app *app)
{
	t_obj *o;

	
	/*o = new_obj(app, make_sphere(20, 20));
	o->scale = vec4(20, 20, 20, 1);
	o->render_type = 1;
	o->have_color = 1;
	o->color = color(150, 50, 50, 0);
*/
//	o = new_obj(app,make_cube(1));
//	o->scale = vec4(40, 40, 40, 1);
//	o->have_color = 1;
//	o->color = color(0, 255, 0, 0);
//	read_fdf(app, "42.fdf");
	app->mouse_1 = 0;
	o = new_obj(app,read_fdf(app, "42.fdf"));
	o->scale = vec4(4, 4, 4, 1);

	app->scene.cam.pos = vec4(0, -50, 500, 1);
	app->scene.cam.look = vec4(0, 0, 0, 1);

	mlx_hook(app->win, 6, (1L<<6), mouse_move_hook, app);
	mlx_hook(app->win, 5, (1L<<2), &mouse2, app);
	mlx_mouse_hook(app->win, mouse_hook, app);
	mlx_loop_hook(app->mlx, iteration, app);

//	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);

	ft_bzero(app->data, HEIGHT * WIDTH * 4);
	ft_memset(app->z_buffer, 0xff, HEIGHT * WIDTH * 4);
	draw_all_obj(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);

	mlx_loop(app->mlx);
}

void	app_clean(t_app *app)
{

}
