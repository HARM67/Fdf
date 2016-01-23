/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 07:28:30 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/23 08:46:06 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	do_scene_transform(t_app *app, t_scene *scn)
{
	int i;

	i = 0;
	scn->mat = scale_mat(scn->scale);
	scn->mat = muli_mat4x4(rot_y_mat(scn->rot.y), scn->mat);
	scn->mat = muli_mat4x4(rot_x_mat(scn->rot.x), scn->mat);
	scn->mat = muli_mat4x4(rot_z_mat(scn->rot.z), scn->mat);
	scn->mat = muli_mat4x4(translate_mat(scn->pos), scn->mat);
}

void	draw_scene(t_app *app)
{
	do_scene_transform(app, &app->scene);
	draw_all_obj(app);
}
