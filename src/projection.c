/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:29:52 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/14 16:43:19 by mfroehly         ###   ########.fr       */
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
	rt.n[2][3] = 1;
	return (rt);
}
