/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vec4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:52:30 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/23 00:42:33 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_vec4(t_app *app, t_vec4 tmp)
{
	if ((int)tmp.y <= 0 || (int)tmp.y > HEIGHT - 5 || (int)tmp.x < 0 || (int)tmp.x > WIDTH)
		return ;
	if (app->z_buffer[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))] < tmp.z && app->scene.cur_obj->render_type != 6)
		return ;
	app->z_buffer[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))] = tmp.z;
	if (app->scene.cur_obj->render_type == 8)
	{
		app->data[(int)(tmp.y + 0.5) * app->sizeline + (int)(tmp.x + 0.5) *
			app->bpp / 8] = (unsigned char)(app->z_buffer[(int)((tmp.x + 0.5) +
						((tmp.y + 0.5) * WIDTH))] / 7);
		return ;
	}
	app->data[(int)(tmp.y + 0.5) * 4 * WIDTH + (int)(tmp.x + 0.5) * 4] = tmp.color.b;
	app->data[(int)(tmp.y + 0.5) * 4 * WIDTH + (int)(tmp.x + 0.5) * 4 + 1] = tmp.color.g;
	app->data[(int)(tmp.y + 0.5) * 4 * WIDTH + (int)(tmp.x + 0.5) * 4 + 2] = tmp.color.r;
}
