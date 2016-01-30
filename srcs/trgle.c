/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trgle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 06:09:56 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/30 14:38:35 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_trgle	trgle(t_vec4 *v1, t_vec4 *v2, t_vec4 *v3)
{
	t_trgle rt;

	rt.p[0] = v1;
	rt.p[1] = v2;
	rt.p[2] = v3;
	return (rt);
}

t_vec4	calc_normal(t_trgle t)
{
	t_vec4	rt;

	rt = prod_vec(sous_vec4(*t.p[1], *t.p[0]), sous_vec4(*t.p[2], *t.p[0]));
	return (rt);
}

t_obj	*make_trgle(t_vec4 v1, t_vec4 v2, t_vec4 v3)
{
	t_obj	*rt;

	rt = (t_obj*)ft_memalloc(sizeof(t_obj));
	if (!rt)
		put_error();
	rt->vecs = (t_vec4*)ft_memalloc(sizeof(t_vec4) * 3);
	rt->trgles = (t_trgle*)ft_memalloc(sizeof(trgle));
	if (!rt->vecs || !rt->trgles)
		put_error();
	rt->vecs[0] = v1;
	rt->vecs[1] = v2;
	rt->vecs[2] = v3;
	rt->trgles[0] = trgle(rt->vecs, rt->vecs + 1, rt->vecs + 2);
	rt->nbr_vecs = 3;
	rt->nbr_lines = 0;
	rt->nbr_trgles = 1;
	rt->scale = vec4(1, 1, 1, 1);
	return (rt);
}
