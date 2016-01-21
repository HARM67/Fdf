/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:38:35 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/21 22:05:51 by mfroehly         ###   ########.fr       */
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

void	print_text(t_app *app)
{
	char *txt;
	t_vec4 v;

	ft_sprintf(&txt, "name : [%s]", app->scene.cur_obj->name);
	mlx_string_put(app->mlx, app->win, 10, 10, 0xFFFFFF, txt);
	mlx_string_put(app->mlx, app->win, 10, 40, 0xFFFFFF, "Projection :");
	if (app->scene.cam.proj == 0)
		mlx_string_put(app->mlx, app->win, 30, 60, 0xFFFFFF, "isometric");
	else if (app->scene.cam.proj == 1)
	{
		mlx_string_put(app->mlx, app->win, 30, 60, 0xFFFFFF, "parralel");
		v = app->scene.first_obj->rot;
		ft_sprintf(&txt, "rot(x[%f], y[%f], z[%f])", v.x, v.y, v.z);
		mlx_string_put(app->mlx, app->win, 30, 80, 0xFFFFFF, txt);
		free (txt);
	}
	else 
	{
		mlx_string_put(app->mlx, app->win, 30, 60, 0xFFFFFF, "perspective");
		v = app->scene.first_obj->rot;
		ft_sprintf(&txt, "rot(x[%f], y[%f], z[%f])", v.x, v.y, v.z);
		mlx_string_put(app->mlx, app->win, 30, 80, 0xFFFFFF, txt);
		free (txt);
	}
	
}


int	iteration(t_app *app)
{
	t_obj *o = app->scene.cur_obj;

	app->count += 0.01;
	ft_bzero(app->data, HEIGHT * WIDTH * 4);
	ft_memset(app->z_buffer, 0xff, HEIGHT * WIDTH * 4);
	draw_obj(app, o);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	print_text(app);
	return (1);
}

int	mouse_move_hook(int x, int y, t_app *app)
{
	t_obj *o = app->scene.cur_obj;

	if (app->mouse_1 == 1)
	{
		o->rot = vec4(
				((app->click.y - y)) / 200 + app->pos_save.x,
				((x - app->click.x)) / 200 + app->pos_save.y,
				0, 1)
			;
		iteration(app);
	}
	return (0);
}

int	mouse2(int button, int x, int y, t_app *app)
{
	t_obj *o = app->scene.cur_obj;

	app->mouse_1 = 0;
	return (0);
}

int	key_up(int key, t_app *app)
{
	if (key == 257)
		app->maj = 0;
	return (0);
}

int	key_down(int key, t_app *app)
{
	t_obj *o = app->scene.cur_obj;
	float tmp;

	if (key == 126)
	{
		o->scale.y *= 2;
		iteration(app);
	}
	else if (key == 125 && o->scale.y > 1)
	{
		o->scale.y /= 2;
		iteration(app);
	}
	else if (key == 18)
	{
		if (app->maj)
			app->scene.cam.proj--;
		else
			app->scene.cam.proj++;
		if (app->scene.cam.proj == 3 || app->scene.cam.proj == 0)
		{
			o->rot = vec4(0, -M_PI / 4, 0, 1);
			tmp = (ABS(app->scene.cam.pos.x) > ABS(app->scene.cam.pos.y))
				? app->scene.cam.pos.x : app->scene.cam.pos.y;
			app->scene.cam.pos = vec4(0, tmp, tmp, 1);
			app->scene.cam.proj = 0;
		}
		else if (app->scene.cam.proj == -1)
			app->scene.cam.proj = 2;

		iteration(app);
	}
	else if (key == 257)
		app->maj = 1;
	else if (key == 48)
	{
		if (!app->maj)
			app->scene.cur_obj = (o->next) ? o->next : app->scene.first_obj;
		else
			app->scene.cur_obj = (o->previous) ? o->previous : app->scene.last_obj;
		iteration(app);
	}
	else if (key == 3)
	{
		o->render_type = (o->render_type) ? 0 : 1;
		iteration(app);
	}
	ft_printf("%d\n", key);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_app *app)
{
	t_obj *o = app->scene.cur_obj;
	if (button == 6 || button == 4)
	{
		o->scale.x /= 1.2 ;
		o->scale.y /= 1.2 ;
		o->scale.z /= 1.2 ;
		iteration(app);
	}
	else if (button == 7 || button == 5)
	{
		o->scale.x *= 1.2 ;
		o->scale.y *= 1.2 ;
		o->scale.z *= 1.2 ;
		iteration(app);
	}
	else if (button == 1 && app->scene.cam.proj != 0)
	{
		app->mouse_1 = 1;
		app->click.x = x;
		app->click.y = y;
		app->pos_save = o->rot;
	}
	return (0);
}

void	load_all_fdf(t_app *app)
{
	int i = 1;
	t_obj *o;

		ft_printf("%d", app->ac);
	while (i < app->ac)
	{
		o = new_obj(app,read_fdf(app, app->av[i]));
		o->scale = vec4(800, 800, 800, 1);
		o->rot = vec4(0, -M_PI / 4, 0, 1);
		i++;
	}
}

void	app_run(t_app *app)
{
	t_obj *o;

	load_all_fdf(app);
/*
	o = new_obj(app,read_fdf(app, "pyramide.fdf"));
	o->scale = vec4(800, 800, 800, 1);
	o->rot = vec4(0, -M_PI / 4, 0, 1);
*/
	o = app->scene.last_obj;
	o = new_obj(app,make_sphere(40, 40));
	o->scale = vec4(300, 300, 300, 1);
	o->rot = vec4(0, -M_PI / 4, 0, 1);
	o->have_color = 1;
	o->color = color(200, 50, 50, 0);

	o = new_obj(app,make_cube(40, 40));
	o->rot = vec4(0, -M_PI / 4, 0, 1);
	o->scale = vec4(300, 300, 300, 1);
	o->have_color = 0;

	app->scene.cur_obj = app->scene.first_obj;
	app->scene.cam.fov = 70;
	app->scene.cam.pos = vec4(0, 1000, 1000, 1);
	app->scene.cam.look = vec4(0, 0, 0, 1);

	mlx_hook(app->win, 6, (1L<<6), mouse_move_hook, app);
	mlx_hook(app->win, 5, (1L<<2), &mouse2, app);
	mlx_mouse_hook(app->win, mouse_hook, app);
//	mlx_loop_hook(app->mlx, iteration, app);
	mlx_hook(app->win, 2, (1L<<0), key_down, app);
	mlx_hook(app->win, 3, (1L<<1), key_up, app);

//	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);


	iteration(app);
	mlx_loop(app->mlx);
}

void	app_clean(t_app *app)
{

}
