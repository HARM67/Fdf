/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:38:35 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/25 08:30:12 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	app_init(t_app *app)
{
	app->mlx = mlx_init();
	app->win = mlx_new_window(app->mlx, WIDTH, HEIGHT, "fdf");
	app->img = mlx_new_image(app->mlx, WIDTH, HEIGHT);
	app->data = mlx_get_data_addr(app->img, &app->bpp, &app->sizeline, &app->endian);
	ft_bzero(app->data, HEIGHT * WIDTH * 4);
	ft_bzero(app->z_buffer, HEIGHT * WIDTH * 4);
}

void	insert_sphere(t_app *app)
{
	t_obj *o;

	o = app->scene.last_obj;
	o = new_obj(app,make_sphere(40, 40));
	o->scale = vec4(150, 150, 150, 1);
	o->have_color = 1;
	o->color = color(rand() % 256, rand() % 256, rand() % 256, 0);
	o->render_type = 4;
	app->scene.cur_obj = o;
}

void	insert_cube(t_app *app)
{
	t_obj *o;

	o = app->scene.last_obj;
	o = new_obj(app,make_cube());
	o->scale = vec4(150, 150, 150, 1);
	o->have_color = 1;
	o->color = color(rand() % 256, rand() % 256, rand() % 256, 0);
	o->render_type = 4;
	app->scene.cur_obj = o;
}

void	print_text(t_app *app)
{
	char *txt;
	t_vec4 v;

	ft_sprintf(&txt, "name : [%s]", app->scene.cur_obj->name);
	mlx_string_put(app->mlx, app->win, 10, 10, 0xFFFFFF, txt);
	free(txt);
	if (app->scene.cam.proj == 0)
		mlx_string_put(app->mlx, app->win, 10, 30, 0xFFFFFF, "Projection : [Isometric]");
	else if (app->scene.cam.proj == 1)
		mlx_string_put(app->mlx, app->win, 10, 30, 0xFFFFFF, "Projection : [Parralel]");
	else
		mlx_string_put(app->mlx, app->win, 10, 30, 0xFFFFFF, "Projection : [Perspective]");
	if (app->scene.cur_obj->render_type == 0)
		mlx_string_put(app->mlx, app->win, 10, 50, 0xFFFFFF, "Render_type : [dot]");
	else if (app->scene.cur_obj->render_type == 1)
		mlx_string_put(app->mlx, app->win, 10, 50, 0xFFFFFF, "Render_type : [line_X]");
	else if (app->scene.cur_obj->render_type == 2)
		mlx_string_put(app->mlx, app->win, 10, 50, 0xFFFFFF, "Render_type : [line_Y]");
	else if (app->scene.cur_obj->render_type == 3)
		mlx_string_put(app->mlx, app->win, 10, 50, 0xFFFFFF, "Render_type : [line_XY]");
	else if (app->scene.cur_obj->render_type == 4)
		mlx_string_put(app->mlx, app->win, 10, 50, 0xFFFFFF, "Render_type : [triangle_no_diag]");
	else if (app->scene.cur_obj->render_type == 5)
		mlx_string_put(app->mlx, app->win, 10, 50, 0xFFFFFF, "Render_type : [triangle_with_diag]");
	else if (app->scene.cur_obj->render_type == 6)
		mlx_string_put(app->mlx, app->win, 10, 50, 0xFFFFFF, "Render_type : [rasterization]");
	if (app->scene.cur_obj->render_type == 6 || (app->all && app->render_type == 6))
	{
		ft_sprintf(&txt, "%u triangle draw", app->nb_trgl_draw);
		mlx_string_put(app->mlx, app->win, 10, 80, 0xFFFFFF, txt);
		free(txt);
	}
	v = app->scene.cur_obj->rot;
	ft_sprintf(&txt, "rot(x[%f], y[%f], z[%f])", v.x, v.y, v.z);
	mlx_string_put(app->mlx, app->win, 30, HEIGHT - 30, 0xFFFFFF, txt);
	free (txt);
}

void	reset_buffer(t_app *app)
{
	int i;
	int *p;

	i = 0;
	p = (int*)app->data;
	while (i < HEIGHT * WIDTH)
	{
		p[i] = colortohex(app->background);
		app->z_buffer[i] = 1.0;
		app->ray[i] = 0;
		i++;
	}
}

void	show_z_buffer(t_app *app)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			app->data[y * 4 * WIDTH + x * 4] = 1 - (app->z_buffer[y * WIDTH + x ] * 255);
			app->data[y * 4 * WIDTH + x * 4 + 1] = 1 - (app->z_buffer[y * WIDTH + x ] * 255);
			app->data[y * 4 * WIDTH + x * 4 + 2] = 1 - (app->z_buffer[y * WIDTH + x ] * 255);
			x++;
		}
		x = 0;
		y++;
	}
}

int	iteration(t_app *app)
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

int	mouse_move_hook(int x, int y, t_app *app)
{
	t_obj *o = app->scene.cur_obj;

	if (app->mouse_1 == 1 && x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (app->maj)
			app->scene.rot = vec4(((app->click.y - y)) / 200 + app->pos_save2.x, ((x - app->click.x)) / 200 + app->pos_save2.y, 0, 1);
		else
			o->rot = vec4(((app->click.y - y)) / 200 + app->pos_save.x, ((x - app->click.x)) / 200 + app->pos_save.y, 0, 1);

		iteration(app);
	}
	return (0);
}

int	mouse2(int button, int x, int y, t_app *app)
{
	t_obj *o = app->scene.cur_obj;

	app->pos_save2 = app->scene.rot;
	app->pos_save = o->rot;
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

	if (key == 116)
	{
		o->scale.y += 1000;
		iteration(app);
	}
	else if (key == 121)
	{
		o->scale.y -= 1000;
		iteration(app);
	}
	else if (key == 126)
	{
		o->pos.z -= 100;
		iteration(app);
	}
	else if (key == 125)
	{
		o->pos.z += 100;
		iteration(app);
	}
	else if (key == 123)
	{
		o->pos.x -= 100;
		iteration(app);
	}
	else if (key == 124)
	{
		o->pos.x += 100;
		iteration(app);
	}
	else if (key == 36)
	{
		app->all = !app->all;
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
	else if (key == 19)
	{
		if (app->all)
		{
			app->render_type += (app->maj) ? -1 : 1;
			app->render_type = (app->render_type < 0) ? 6 : app->render_type;
			app->render_type = (app->render_type > 6) ? 0 : app->render_type;
		}
		else
		{
			o->render_type += (app->maj) ? -1 : 1;
			o->render_type = (o->render_type < 0) ? 6 : o->render_type;
			o->render_type = (o->render_type > 6) ? 0 : o->render_type;
		}
		iteration(app);
	}
	else if (key == 1)
	{
		insert_sphere(app);
		iteration(app);
	}
	else if (key == 8)
	{
		insert_cube(app);
		iteration(app);
	}
	else if (key == 2)
	{
		if (app->maj)
			app->show_depth = !app->show_depth;
		else
			app->a_depth = !app->a_depth;
		iteration(app);
	}
	else if (key == 37)
	{
		app->a_light = !app->a_light;
		iteration(app);
	}
	else if (key == 12)
	{
		app->a_culling = !app->a_culling;
		iteration(app);
	}
	else if (key == 13)
	{
		app->rem_no_visible = !app->rem_no_visible;
		iteration(app);
	}
	else if (key == 69)
	{
		if (app->maj)
		{
			if (app->ambient < 1.0)
				app->ambient += 0.1;
		}
		else
		{
			if (app->light_coef < 1.5)
				app->light_coef += 0.1;
		}
		iteration(app);
	}
	else if (key == 78)
	{
		if (app->maj)
		{
			if (app->ambient > 0.1)
				app->ambient -= 0.1;
		}
		else
		{
			if (app->light_coef > 0.1)
			app->light_coef -= 0.1;
		}
		iteration(app);
	}
	ft_printf("%d\n", key);
	return (0);
}


int	mouse_hook(int button, int x, int y, t_app *app)
{
	t_obj *o = app->scene.cur_obj;
	t_vec4 *v;

	if (app->maj)
		v = &app->scene.scale;
	else
		v = &o->scale;
	if (button == 1 && x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (app->ray[x + (y * WIDTH)])
			app->scene.cur_obj = app->ray[x + (y * WIDTH)];
	}
	if (button == 6 || button == 4)
	{
		v->x /= 1.2 ;
		v->y /= 1.2 ;
		v->z /= 1.2 ;
		iteration(app);
	}
	else if (button == 7 || button == 5)
	{
		v->x *= 1.2 ;
		v->y *= 1.2 ;
		v->z *= 1.2 ;
		iteration(app);
	}
	else if (button == 1 && app->scene.cam.proj != 0 && x > 0 && y > 0 && x < WIDTH && y < HEIGHT)
	{
		app->mouse_1 = 1;
		app->click.x = x;
		app->click.y = y;
		app->pos_save2 = app->scene.rot;
		app->pos_save = app->scene.cur_obj->rot;
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
		o->have_color = 0;
		o->render_type = 3;
		i++;
	}
}


void	app_run(t_app *app)
{
	t_obj *o;

	load_all_fdf(app);
	app->background = color(0, 0, 0, 255);
	app->ray = (t_obj**)ft_memalloc(sizeof(t_obj*) * HEIGHT * WIDTH);

	app->scene.cur_obj = app->scene.first_obj;
	app->scene.cam.fov = 70;
	app->scene.cam.pos = vec4(0, 1000, 1000, 1);
	app->scene.cam.look = vec4(0, 0, 0, 1);
	app->scene.cam.near = 500;
	app->scene.cam.far = 3000;
	app->scene.cam.proj = 2;
	app->light_coef = 1.0;
	app->a_culling = 1;
	app->ambient = 0;

	mlx_hook(app->win, 6, (1L<<6), mouse_move_hook, app);
	mlx_hook(app->win, 5, (1L<<2), &mouse2, app);
	mlx_mouse_hook(app->win, mouse_hook, app);
	mlx_hook(app->win, 2, (1L<<0), key_down, app);
	mlx_hook(app->win, 3, (1L<<1), key_up, app);

	app->scene.scale = vec4(1, 1, 1, 1);
	app->scene.rot = vec4(0, 0, 0, 1);
	app->scene.pos = vec4(0, 0, 0, 1);
	app->render_type = 3;
	iteration(app);
	mlx_loop(app->mlx);
}

void	app_clean(t_app *app)
{

}
