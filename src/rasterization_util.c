/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterization_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 05:17:33 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 05:19:08 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec4	*up(t_vec4 *v1, t_vec4 *v2, t_vec4 *v3)
{
	t_vec4	*rt;

	rt = v1;
	if (rt->y < v2->y)
		rt = v2;
	if (rt->y < v3->y)
		rt = v3;
	return (rt);
}

t_vec4	*down(t_vec4 *v1, t_vec4 *v2, t_vec4 *v3)
{
	t_vec4	*rt;

	rt = v3;
	if (rt->y > v2->y)
		rt = v2;
	if (rt->y > v1->y)
		rt = v1;
	return (rt);
}

t_vec4	*middle(t_vec4 *v1, t_vec4 *v2, t_vec4 *v3)
{
	if (v1 != up(v1, v2, v3) && v1 != down(v1, v2, v3))
		return (v1);
	if (v2 != up(v1, v2, v3) && v2 != down(v1, v2, v3))
		return (v2);
	if (v3 != up(v1, v2, v3) && v3 != down(v1, v2, v3))
		return (v3);
	return (v3);
}
