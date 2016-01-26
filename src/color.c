/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 02:58:59 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 06:57:10 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	colortohex(t_color color)
{
	return ((unsigned int)(color.r << 16 | color.g << 8 | color.b));
}

t_color			color_pos(t_color c1, t_color c2, float position)
{
	t_color	rt;

	rt.r = c2.r + ((c1.r - c2.r) * position);
	rt.g = c2.g + ((c1.g - c2.g) * position);
	rt.b = c2.b + ((c1.b - c2.b) * position);
	rt.a = c2.a + ((c1.a - c2.a) * position);
	return (rt);
}

t_color			color(unsigned char r, unsigned char g,
						unsigned char b, unsigned char a)
{
	t_color	rt;

	rt.r = r;
	rt.g = g;
	rt.b = b;
	rt.a = a;
	return (rt);
}
/*
**	float			c;
**		c = (float)(tmp->y / fdf->max);
**		tmp->color = color(175 + 55 * c, 125 + 100 * c, 75 + 100 * c, 255);
**		if (c < 0)
**			tmp->color = color(0, 0, 150, 255);
**		else if (c <= 0.001)
**			tmp->color = color(20 + (1000000 * c), 30 + (1000000 * c), 150 +
**					(1000000 * c), 255);
**		else if (c > 0.002 && c <= 0.2)
**			tmp->color = color(75 - (unsigned char)(c * 100), 75 +
**					(unsigned char)(c * 400), 20, 255);
*/
