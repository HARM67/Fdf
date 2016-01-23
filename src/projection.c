/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:29:52 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/23 07:49:47 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix4x4	perspective(t_vec4 v)
{
	t_matrix4x4 rt;
	float		ratio;
	float		fov;

	fov = 70;
	ratio = WIDTH / HEIGHT;

	rt = identity_mat4x4();
	rt.n[0][0] = (HEIGHT) / (tan(fov / 2) * v.z);
	rt.n[1][1] = (HEIGHT  ) / (tan(fov / 2) * v.z);
	return (rt);
}

t_vec4	perspective_vec4(t_app *app, t_vec4 v)
{
	float fov;
	
	fov = app->scene.cam.fov;
	v.x *= (HEIGHT) / (tan(fov / 2) * v.z);
	v.y *= (HEIGHT) / (tan(fov / 2) * v.z);
	v.z = (v.z - app->scene.cam.near) / app->scene.cam.far;
	return (v);
}
