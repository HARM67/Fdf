/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vec4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:52:30 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/23 10:54:44 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_vec4(t_app *app, t_vec4 tmp, t_obj *o)
{
	if ((int)tmp.y <= 0 || (int)tmp.y > HEIGHT - 5 || (int)tmp.x < 0 || (int)tmp.x > WIDTH)
		return ;
	if (app->z_buffer[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))] < tmp.z && app->scene.cur_obj->render_type != 6)
		return ;
	app->z_buffer[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))] = tmp.z;
	app->ray[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))] = o;
	app->data[(int)(tmp.y + 0.5) * 4 * WIDTH + (int)(tmp.x + 0.5) * 4] = tmp.color.b;
	app->data[(int)(tmp.y + 0.5) * 4 * WIDTH + (int)(tmp.x + 0.5) * 4 + 1] = tmp.color.g;
	app->data[(int)(tmp.y + 0.5) * 4 * WIDTH + (int)(tmp.x + 0.5) * 4 + 2] = tmp.color.r;
}

void	ray_trace(t_app *app, t_vec4 tmp, t_obj *obj)
{
	if ((int)tmp.y <= 0 || (int)tmp.y > HEIGHT - 5 || (int)tmp.x < 0 || (int)tmp.x > WIDTH)
		return ;
	if (app->z_buffer[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))] < tmp.z && app->scene.cur_obj->render_type != 6)
		return ;
	app->ray[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))] = 0;
}
