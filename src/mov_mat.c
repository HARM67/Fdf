/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_mat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 19:15:28 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/21 19:15:37 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix4x4 translate_mat(t_vec4 trans)
{
	t_matrix4x4 m;

	m = identity_mat4x4();
	m.n[0][3] = trans.x;
	m.n[1][3] = trans.y;
	m.n[2][3] = trans.z;
	m.n[3][3] = 1.0;
	return (m);
}

t_matrix4x4	scale_mat(t_vec4 scale)
{
	t_matrix4x4 m;

	m = identity_mat4x4();
	m.n[0][0] = scale.x;
	m.n[1][1] = scale.y;
	m.n[2][2] = scale.z;
	m.n[3][3] = 1.0;
	return (m);
}

t_matrix4x4	rot_x_mat(float rot_x)
{
	t_matrix4x4 m;

	m = identity_mat4x4();
	m.n[1][1] = cos(rot_x);
	m.n[1][2] = sin(rot_x);
	m.n[2][1] = -sin(rot_x);
	m.n[2][2] = cos(rot_x);
	return (m);
}

t_matrix4x4 rot_y_mat(float rot_y)
{
	t_matrix4x4 m;

	m = identity_mat4x4();
	m.n[0][0] = cos(rot_y);
	m.n[0][2] = sin(rot_y);
	m.n[2][0] = -sin(rot_y);
	m.n[2][2] = cos(rot_y);
	return (m);
}

t_matrix4x4	rot_z_mat(float rot_z)
{
	t_matrix4x4 m;

	m = identity_mat4x4();
	m.n[0][0] = cos(rot_z);
	m.n[0][1] = -sin(rot_z);
	m.n[1][0] = sin(rot_z);
	m.n[1][1] = cos(rot_z);
	return (m);
}
