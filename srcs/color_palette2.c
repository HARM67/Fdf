/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_palette2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 10:18:49 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/30 16:15:10 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color_red_blue(t_vec4 *v)
{
	float	c;

	c = v->relative_color;
	v->color.r = c * 255;
	v->color.g = 0;
	v->color.b = (1 - c) * 255;
}

void	color_yellow_red(t_vec4 *v)
{
	float	c;

	c = v->relative_color;
	v->color.r = 255;
	v->color.g = c * 255;
	v->color.b = 0;
}

void	color_white(t_vec4 *v)
{
	float	c;

	c = v->relative_color;
	v->color.r = 255;
	v->color.g = 255;
	v->color.b = 255;
}

void	color_green(t_vec4 *v)
{
	float	c;

	c = v->relative_color;
	v->color.r = 0;
	v->color.g = 255;
	v->color.b = 0;
}

void	color_white_blue(t_vec4 *v)
{
	float	c;

	c = v->relative_color;
	v->color.r = (1 - c) * 255;
	v->color.g = (1 - c) * 255;
	v->color.b = 255;
}
