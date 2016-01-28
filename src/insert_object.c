/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 04:51:46 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 14:59:52 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	insert_sphere(t_app *app)
{
	t_obj *o;

	o = app->scene.last_obj;
	o = new_obj(app, make_sphere(40, 40));
	o->scale = vec4(150, 150, 150, 1);
	o->have_color = 0;
	o->render_type = 4;
	app->scene.cur_obj = o;
}

void	insert_cube(t_app *app)
{
	t_obj *o;

	o = app->scene.last_obj;
	o = new_obj(app, make_cube());
	o->scale = vec4(150, 150, 150, 1);
	o->render_type = 4;
	app->scene.cur_obj = o;
}
