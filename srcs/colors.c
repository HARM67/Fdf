/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:25:57 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/30 10:33:33 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_colors(t_app *app)
{
	app->colors[0] = color_default;
	app->colors[1] = color_white;
	app->colors[2] = color_green;
	app->colors[3] = color_black_white;
	app->colors[4] = color_black_red;
	app->colors[5] = color_white_blue;
	app->colors[6] = color_yellow_red;
	app->colors[7] = color_red_blue;
	app->colors[8] = color_random;
	app->colors[9] = color_map;
}
