/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 07:27:14 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 07:23:46 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec4	translate_vec4(t_vec4 trans, t_vec4 v)
{
	t_matrix4x4	m;
	t_vec4		rt;

	m = identity_mat4x4();
	m.n[0][3] = trans.x;
	m.n[1][3] = trans.y;
	m.n[2][3] = trans.z;
	m.n[3][3] = 1.0;
	rt = muli_mat4x4_vec4(m, v);
	rt.color = v.color;
	return (rt);
}

t_vec4	scale_vec4(t_vec4 scale, t_vec4 v)
{
	t_matrix4x4	m;
	t_vec4		rt;

	m = identity_mat4x4();
	m.n[0][0] = scale.x;
	m.n[1][1] = scale.y;
	m.n[2][2] = scale.z;
	m.n[3][3] = 1.0;
	rt = muli_mat4x4_vec4(m, v);
	rt.color = v.color;
	return (rt);
}

t_vec4	rot_x(float rot_x, t_vec4 v)
{
	t_matrix4x4	m;
	t_vec4		rt;

	m = identity_mat4x4();
	m.n[1][1] = cos(rot_x);
	m.n[1][2] = sin(rot_x);
	m.n[2][1] = -sin(rot_x);
	m.n[2][2] = cos(rot_x);
	rt = muli_mat4x4_vec4(m, v);
	rt.color = v.color;
	return (rt);
}

t_vec4	rot_y(float rot_y, t_vec4 v)
{
	t_matrix4x4	m;
	t_vec4		rt;

	m = identity_mat4x4();
	m.n[0][0] = cos(rot_y);
	m.n[0][2] = sin(rot_y);
	m.n[2][0] = -sin(rot_y);
	m.n[2][2] = cos(rot_y);
	rt = muli_mat4x4_vec4(m, v);
	rt.color = v.color;
	return (rt);
}

t_vec4	rot_z(float rot_z, t_vec4 v)
{
	t_matrix4x4	m;
	t_vec4		rt;

	m = identity_mat4x4();
	m.n[0][0] = cos(rot_z);
	m.n[0][1] = -sin(rot_z);
	m.n[1][0] = sin(rot_z);
	m.n[1][1] = cos(rot_z);
	rt = muli_mat4x4_vec4(m, v);
	rt.color = v.color;
	return (rt);
}
