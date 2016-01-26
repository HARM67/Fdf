/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 04:31:12 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 07:04:57 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scene_init(t_app *app)
{
	app->background = color(0, 0, 0, 255);
	app->scene.cur_obj = app->scene.first_obj;
	app->scene.cam.fov = 70;
	app->scene.cam.pos = vec4(0, 1000, 1000, 1);
	app->scene.cam.look = vec4(0, 0, 0, 1);
	app->scene.cam.near = 500;
	app->scene.cam.far = 3000;
	app->scene.cam.proj = 2;
	app->light_coef = 1.0;
	app->a_culling = 1;
	app->ambient = 0;
	app->scene.scale = vec4(1, 1, 1, 1);
	app->scene.rot = vec4(0, 0, 0, 1);
	app->scene.pos = vec4(0, 0, 0, 1);
	app->render_type = 3;
}
