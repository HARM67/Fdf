/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_palette.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 07:32:20 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 09:30:28 by mfroehly         ###   ########.fr       */
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
	v->color.r = rand() % 255;
	v->color.g = rand() % 255;
	v->color.b = rand() % 255;
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
