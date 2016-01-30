/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_palette.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 07:32:20 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/30 16:15:37 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color_map(t_vec4 *v)
{
	float c;

	c = v->relative_color;
	v->color = color(175 + 55 * c, 125 + 100 * c, 75 + 100 * c, 255);
	if (c < 0)
		v->color = color(0, 0, 150, 255);
	else if (c <= 0.001)
		v->color = color(20 + (1000000 * c), 30 + (1000000 * c), 150 +
				(1000000 * c), 255);
	else if (c > 0.002 && c <= 0.2)
		v->color = color(75 - (unsigned char)(c * 100), 75 +
				(unsigned char)(c * 400), 20, 255);
}

void	color_random(t_vec4 *v)
{
	float	c;
	float	t;

	c = v->relative_color;
	t = 6.0;
	if (c <= 1.0 / 6.0)
		v->color = color(255, t * c * 255, 0, 0);
	else if (c > 1.0 / 6.0 && c <= 1.0 / 3.0)
		v->color = color((1 - (c - 1 / 6)) * 6 * 255, 255, 0, 0);
	else if (c > 1.0 / 3.0 && c <= 1.0 / 2.0)
		v->color = color(0, 255, (c - 1 / 3) * 6 * 255, 0);
	else if (c > 1.0 / 2.0 && c <= 2.0 / 3.0)
		v->color = color(0, (1 - (c - 1 / 2)) * 6 * 255, 255, 0);
	else if (c > 2.0 / 3.0 && c <= 5.0 / 6.0)
		v->color = color((c - 2 / 3) * 6 * 255, 0, 255, 0);
	else if (c > 5.0 / 6.0)
		v->color = color(255, 0, (1 - (c - 5 / 6)) * 6 * 255, 0);
}

void	color_black_white(t_vec4 *v)
{
	float	c;

	c = v->relative_color;
	v->color.r = c * 255;
	v->color.g = c * 255;
	v->color.b = c * 255;
}

void	color_default(t_vec4 *v)
{
	v->color.r = 128;
	v->color.g = 128;
	v->color.b = 128;
}

void	color_black_red(t_vec4 *v)
{
	float	c;

	c = v->relative_color;
	v->color.r = c * 255;
	v->color.g = 0;
	v->color.b = 0;
}
