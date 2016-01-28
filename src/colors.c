/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 09:25:57 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 09:29:13 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_colors(t_app *app)
{
	app->colors[0] = color_default;
	app->colors[1] = color_black_white;
	app->colors[2] = color_black_red;
	app->colors[3] = color_random;
	app->colors[4] = color_map;
}
