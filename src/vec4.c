/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 03:42:32 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/14 18:25:35 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

t_vec4	inverse(t_vec4 v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

t_vec4	*vec4cpy(t_vec4 src)
{
	t_vec4 *rt;

	rt = ft_memalloc(sizeof(t_vec4));
	return (rt);
}

t_vec4	vec4(float x, float y, float z, float w)
{
	t_vec4 rt;

	rt.x = x;
	rt.y = y;
	rt.z = z;
	rt.w = w;
	rt.color = color(255, 255, 255, 255);
	return (rt);
}

t_vec4	sous_vec4(t_vec4 a, t_vec4 b)
{
	return (vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w));
}
