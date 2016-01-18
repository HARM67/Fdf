/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vec4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:52:30 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/18 12:34:07 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_vec4(t_app *app, t_vec4 tmp)
{
	
	if (app->z_buffer[(int)tmp.x + (int)(tmp.y * WIDTH)] > tmp.z)
		return ;
	app->z_buffer[(int)tmp.x + (int)(tmp.y * WIDTH)] = tmp.z;
	app->data[(int)tmp.y * app->sizeline + (int)tmp.x * app->bpp / 8] = (char)tmp.z / 2;
//	app->data[(int)tmp.y * app->sizeline + (int)tmp.x * app->bpp / 8] = tmp.color.b;
//	app->data[(int)tmp.y * app->sizeline + (int)tmp.x * app->bpp / 8 + 1] = tmp.color.g;
//	app->data[(int)tmp.y * app->sizeline + (int)tmp.x * app->bpp / 8 + 2] = tmp.color.r;
}
