/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 10:33:22 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/30 14:19:46 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_text_insert(t_app *app)
{
	mlx_string_put(app->mlx, app->win, 30, HEIGHT - 170, 0x0000FF,
			" <S>           Insert Sphere");
	mlx_string_put(app->mlx, app->win, 30, HEIGHT - 190, 0x0000FF,
			" <C>           Insert Cube");
	if (app->all)
		mlx_string_put(app->mlx, app->win, 30, HEIGHT - 210, 0x00FF00,
				" <enter>       Mode all : ON");
	else
		mlx_string_put(app->mlx, app->win, 30, HEIGHT - 210, 0xFF0000,
				" <enter>       Mode all : OFF");
}

void	print_text_onoff(t_app *app)
{
	if (app->scene.cur_obj->render_type == 6 ||
			(app->all && app->render_type == 6))
	{
		if (app->rem_no_visible)
			mlx_string_put(app->mlx, app->win, 10, 100, 0x00FF00,
					" <W>  Remove out of screen triangle : ON");
		else
			mlx_string_put(app->mlx, app->win, 10, 100, 0xFF0000,
					" <W>  Remove out of screen triangle : OFF");
	}
	if (app->a_picking && app->all)
		mlx_string_put(app->mlx, app->win, 10, 160, 0x00FF00,
				" <T>  Picking : ON");
	else if (app->all)
		mlx_string_put(app->mlx, app->win, 10, 160, 0xFF0000,
				" <T>  Picking : OFF");
	if (app->a_culling)
		mlx_string_put(app->mlx, app->win, 10, 80, 0x00FF00,
				" <Q>  Culling : ON");
	else
		mlx_string_put(app->mlx, app->win, 10, 80, 0xFF0000,
				" <Q>  Culling : OFF");
}

void	print_text_info2(t_app *app)
{
	char *txt;

	if (app->scene.cur_obj->render_type == 6 ||
			(app->all && app->render_type == 6))
	{
		if (app->a_light)
		{
			ft_sprintf(&txt, " <R>  Light : ON [%f], amb[%f]", app->light_coef,
					app->ambient);
			mlx_string_put(app->mlx, app->win, 10, 140, 0x00FF00,
					txt);
			free(txt);
		}
		else
			mlx_string_put(app->mlx, app->win, 10, 140, 0xFF0000,
					" <R>  Light : OFF");
	}
	if (app->a_depth)
		mlx_string_put(app->mlx, app->win, 10, 120, 0x00FF00,
				" <E>  Depth_test : ON");
	else
		mlx_string_put(app->mlx, app->win, 10, 120, 0xFF0000,
				" <E>  Depth_test : OFF");
}

void	print_text_pos(t_app *app)
{
	char	*txt;
	t_vec4	v;

	v = app->scene.cur_obj->pos;
	if (app->a_prof)
		mlx_string_put(app->mlx, app->win, 10, 180, 0x00FF00,
				" <Y>  Depth_multiply : ON");
	else
		mlx_string_put(app->mlx, app->win, 10, 180, 0xFF0000,
				" <Y>  Depth_multiply : ON");
	ft_sprintf(&txt, "<arrow>        pos(x[%f], y[%f], z[%f])", v.x, v.y, v.z);
	mlx_string_put(app->mlx, app->win, 30, HEIGHT - 50, 0x0000FF, txt);
	free(txt);
	v = app->scene.cur_obj->scale;
	ft_sprintf(&txt, "<mouse wheel>  scale(x[%f], y[%f], z[%f])", v.x, v.y,
			v.z);
	mlx_string_put(app->mlx, app->win, 30, HEIGHT - 70, 0x0000FF, txt);
	free(txt);
	mlx_string_put(app->mlx, app->win, 30, HEIGHT - 90, 0x0000FF,
			"<page up/down> Change height");
}
