/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 04:48:45 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 13:13:16 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_text_proj(t_app *app)
{
	char *txt;

	if (app->scene.cam.proj == 0)
		mlx_string_put(app->mlx, app->win, 10, 30, 0x0000FF,
				" <1>  Projection : [Isometric]");
	else if (app->scene.cam.proj == 1)
		mlx_string_put(app->mlx, app->win, 10, 30, 0x0000FF,
				" <1>  Projection : [Parralel]");
	else
	{
		ft_sprintf(&txt, " <1>  Projection : [Perspective]; fov : [%f]",
				app->scene.cam.fov);
		mlx_string_put(app->mlx, app->win, 10, 30, 0x0000FF,
				txt);
		free(txt);
	}
}

void	print_text_render(t_app *app)
{
	int render_type;

	render_type = (app->all) ? app->render_type :
		app->scene.cur_obj->render_type;
	if (render_type == 0)
		mlx_string_put(app->mlx, app->win, 10, 50, 0x0000FF,
				" <2>  Render_type : [dot]");
	else if (render_type == 1)
		mlx_string_put(app->mlx, app->win, 10, 50, 0x0000FF,
				" <2>  Render_type : [line_X]");
	else if (render_type == 2)
		mlx_string_put(app->mlx, app->win, 10, 50, 0x0000FF,
				" <2>  Render_type : [line_Y]");
	else if (render_type == 3)
		mlx_string_put(app->mlx, app->win, 10, 50, 0x0000FF,
				" <2>  Render_type : [line_XY]");
	else if (render_type == 4)
		mlx_string_put(app->mlx, app->win, 10, 50, 0x0000FF,
				" <2>  Render_type : [triangle_no_diag]");
	else if (render_type == 5)
		mlx_string_put(app->mlx, app->win, 10, 50, 0x0000FF,
				" <2>  Render_type : [triangle_with_diag]");
	else if (render_type == 6)
		mlx_string_put(app->mlx, app->win, 10, 50, 0x0000FF,
				" <2>  Render_type : [rasterization]");
}

void	print_text_nbr_trgles(t_app *app)
{
	char *txt;

	if (app->scene.cur_obj->render_type == 6 ||
			(app->all && app->render_type == 6))
	{
		ft_sprintf(&txt, "%-6utriangle draw", app->nb_trgl_draw);
		mlx_string_put(app->mlx, app->win, 10, 190, 0x0000FF, txt);
		free(txt);
	}
}

void	print_text_rot(t_app *app)
{
	char	*txt;
	t_vec4	v;

	v = app->scene.cur_obj->rot;
	ft_sprintf(&txt, "<mouse move>   rot(x[%f], y[%f], z[%f])", v.x, v.y, v.z);
	mlx_string_put(app->mlx, app->win, 30, HEIGHT - 30, 0x0000FF, txt);
	free(txt);
}

void	print_text(t_app *app)
{
	char *txt;

	ft_sprintf(&txt, "<tab> name : [%s]", app->scene.cur_obj->name);
	mlx_string_put(app->mlx, app->win, 10, 10, 0x0000FF, txt);
	free(txt);
	print_text_proj(app);
	print_text_render(app);
	print_text_nbr_trgles(app);
	print_text_rot(app);
	print_text_onoff(app);
	print_text_pos(app);
	print_text_info2(app);
}
