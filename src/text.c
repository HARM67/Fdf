/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 04:48:45 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 04:49:35 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
