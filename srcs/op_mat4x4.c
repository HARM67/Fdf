/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_opp4x4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 07:11:55 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 14:25:26 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix4x4	identity_mat4x4(void)
{
	t_matrix4x4 m;

	ft_bzero(&m, sizeof(t_matrix4x4));
	m.n[0][0] = 1.0;
	m.n[1][1] = 1.0;
	m.n[2][2] = 1.0;
	m.n[3][3] = 1.0;
	return (m);
}

t_vec4		muli_mat4x4_vec4(t_matrix4x4 m, t_vec4 v)
{
	t_vec4	rt;

	rt.x = m.n[0][0] * v.x + m.n[0][1] * v.y + m.n[0][2] * v.z + m.n[0][3] *
		v.w;
	rt.y = m.n[1][0] * v.x + m.n[1][1] * v.y + m.n[1][2] * v.z + m.n[1][3] *
		v.w;
	rt.z = m.n[2][0] * v.x + m.n[2][1] * v.y + m.n[2][2] * v.z + m.n[2][3] *
		v.w;
	rt.w = m.n[3][0] * v.x + m.n[3][1] * v.y + m.n[3][2] * v.z + m.n[3][3] *
		v.w;
	rt.color = v.color;
	return (rt);
}

t_matrix4x4	muli_mat4x4(t_matrix4x4 a, t_matrix4x4 b)
{
	t_matrix4x4	rt;
	int			i;
	int			j;
	int			p;

	ft_bzero(&rt, sizeof(t_matrix4x4));
	i = 0;
	j = 0;
	p = 0;
	while (j < 4)
	{
		while (i < 4)
		{
			while (p < 4)
			{
				rt.n[j][i] += a.n[j][p] * b.n[p][i];
				p++;
			}
			p = 0;
			i++;
		}
		i = 0;
		j++;
	}
	return (rt);
}

void		do_transform(t_app *app, t_obj *obj, t_matrix4x4 mat)
{
	unsigned int	i;
	float			proj;

	i = 0;
	proj = app->scene.cam.proj;
	obj->mat = scale_mat(obj->scale);
	obj->mat = muli_mat4x4(rot_y_mat(obj->rot.y), obj->mat);
	obj->mat = muli_mat4x4(rot_x_mat(obj->rot.x), obj->mat);
	obj->mat = muli_mat4x4(rot_z_mat(obj->rot.z), obj->mat);
	obj->mat = muli_mat4x4(translate_mat(obj->pos), obj->mat);
	obj->mat = muli_mat4x4(mat, obj->mat);
	obj->mat = muli_mat4x4(cam_mat(app), obj->mat);
	while (i < obj->nbr_vecs)
	{
		obj->vecs[i] = muli_mat4x4_vec4(obj->mat, obj->vecs_orig[i]);
		i++;
	}
}
