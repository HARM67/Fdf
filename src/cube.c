/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 08:14:54 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 09:25:41 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	make_cube_vertex(t_obj *o)
{
	o->vecs = (t_vec4 *)ft_memalloc(sizeof(t_vec4) * 8);
	o->vecs_orig = (t_vec4 *)ft_memalloc(sizeof(t_vec4) * 8);
	if (o->vecs == 0 || o->vecs_orig == 0)
		exit(1);
	o->vecs_orig[0] = vec4(-0.5, 0.5, -0.5, 1.0);
	o->vecs_orig[1] = vec4(0.5, 0.5, -0.5, 1.0);
	o->vecs_orig[2] = vec4(-0.5, -0.5, -0.5, 1.0);
	o->vecs_orig[3] = vec4(0.5, -0.5, -0.5, 1.0);
	o->vecs_orig[4] = vec4(-0.5, 0.5, 0.5, 1.0);
	o->vecs_orig[5] = vec4(0.5, 0.5, 0.5, 1.0);
	o->vecs_orig[6] = vec4(-0.5, -0.5, 0.5, 1.0);
	o->vecs_orig[7] = vec4(0.5, -0.5, 0.5, 1.0);
	o->vecs_orig[2].color = color(255, 0, 0, 0);
	o->vecs_orig[0].color = color(0, 255, 0, 0);
	o->vecs_orig[6].color = color(0, 0, 255, 0);
	o->vecs_orig[7].color = color(0, 255, 255, 0);
	o->vecs_orig[4].color = color(0, 0, 255, 0);
	o->vecs_orig[5].color = color(255, 0, 255, 0);
	o->nbr_vecs = 8;
}

static void		make_cube_trgles(t_obj *o)
{
	int i;

	i = 0;
	o->trgles = (t_trgle *)ft_memalloc(sizeof(t_trgle) * 12);
	if (o->trgles == 0)
		exit(1);
	o->trgles[0] = trgle(&(o->vecs)[1], &(o->vecs)[0], &(o->vecs)[2]);
	o->trgles[1] = trgle(&(o->vecs)[2], &(o->vecs)[3], &(o->vecs)[1]);
	o->trgles[2] = trgle(&(o->vecs)[5], &(o->vecs)[1], &(o->vecs)[3]);
	o->trgles[3] = trgle(&(o->vecs)[3], &(o->vecs)[7], &(o->vecs)[5]);
	o->trgles[4] = trgle(&(o->vecs)[4], &(o->vecs)[5], &(o->vecs)[7]);
	o->trgles[5] = trgle(&(o->vecs)[7], &(o->vecs)[6], &(o->vecs)[4]);
	o->trgles[6] = trgle(&(o->vecs)[0], &(o->vecs)[4], &(o->vecs)[6]);
	o->trgles[7] = trgle(&(o->vecs)[6], &(o->vecs)[4], &(o->vecs)[0]);
	o->trgles[8] = trgle(&(o->vecs)[0], &(o->vecs)[1], &(o->vecs)[4]);
	o->trgles[9] = trgle(&(o->vecs)[5], &(o->vecs)[4], &(o->vecs)[1]);
	o->trgles[10] = trgle(&(o->vecs)[6], &(o->vecs)[2], &(o->vecs)[7]);
	o->trgles[11] = trgle(&(o->vecs)[2], &(o->vecs)[3], &(o->vecs)[7]);
	o->nbr_trgles = 12;
}

t_obj			*make_cube(void)
{
	t_obj	*o;

	o = (t_obj *)ft_memalloc(sizeof(t_obj));
	ft_strcpy(o->name, "cube");
	make_cube_vertex(o);
	make_cube_trgles(o);
	o->nbr_lines = 0;
	o->scale = vec4(1.0, 1.0, 1.0, 1.0);
	return (o);
}
