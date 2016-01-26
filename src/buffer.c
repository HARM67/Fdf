/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 04:49:48 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 04:50:53 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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


