/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 18:11:46 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 15:02:40 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_cam				cam(void)
{
	t_cam	rt;

	ft_bzero(&rt, sizeof(t_cam));
	rt.pos = vec4(10.0, 10.0, 10.0, 1);
	return (rt);
}

static t_matrix4x4	cam_rot(t_app *app)
{
	t_vec4		f;
	t_vec4		s;
	t_vec4		u;
	t_matrix4x4	rt;

	f = normalize(sous_vec4(app->scene.cam.pos, app->scene.cam.look));
	s = normalize(prod_vec(f, vec4(0, -1, 0, 1)));
	u = normalize(prod_vec(s, f));
	rt = identity_mat4x4();
	rt.n[0][0] = s.x;
	rt.n[0][1] = s.y;
	rt.n[0][2] = s.z;
	rt.n[1][0] = u.x;
	rt.n[1][1] = u.y;
	rt.n[1][2] = u.z;
	rt.n[2][0] = -f.x;
	rt.n[2][1] = -f.y;
	rt.n[2][2] = -f.z;
	return (rt);
}

static t_matrix4x4	tr(t_vec4 trans)
{
	t_matrix4x4 m;

	m = identity_mat4x4();
	m.n[0][3] = trans.x;
	m.n[1][3] = trans.y;
	m.n[2][3] = trans.z;
	m.n[3][3] = 1.0;
	return (m);
}

t_matrix4x4			cam_mat(t_app *app)
{
	t_matrix4x4	mat;

	mat = muli_mat4x4(cam_rot(app), tr(inverse(app->scene.cam.pos)));
	return (mat);
}

t_vec4				do_cam(t_app *app, t_vec4 v)
{
	t_vec4		rt;
	t_matrix4x4	mat;

	mat = cam_mat(app);
	rt = muli_mat4x4_vec4(mat, v);
	return (rt);
}
