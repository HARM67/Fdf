/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vec4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:52:30 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/25 08:36:36 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_vec4(t_app *app, t_vec4 tmp, t_obj *o)
{
	if ((int)tmp.y <= 0 || (int)tmp.y > HEIGHT - 2 || (int)tmp.x < 0 || (int)tmp.x > WIDTH - 2)
		return ;
	if (app->z_buffer[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))] < tmp.z && app->a_depth)
		return ;
	app->z_buffer[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))] = tmp.z;
	app->ray[(int)((int)(tmp.x + 0.5) + ((int)(tmp.y + 0.5) * WIDTH))] = o;
	app->data[(int)(tmp.y + 0.5) * 4 * WIDTH + (int)(tmp.x + 0.5) * 4] = tmp.color.b * (1 - tmp.z );
	app->data[(int)(tmp.y + 0.5) * 4 * WIDTH + (int)(tmp.x + 0.5) * 4 + 1] = tmp.color.g * (1 - tmp.z);
	app->data[(int)(tmp.y + 0.5) * 4 * WIDTH + (int)(tmp.x + 0.5) * 4 + 2] = tmp.color.r * (1 - tmp.z);
}
