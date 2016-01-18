/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 08:40:10 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/18 12:29:49 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"fdf.h"

static	void	make_sphere_vertex(t_obj *o, int row, int col)
{
	int i;
	int j;

	i = 0;
	j = 0;
	o->vecs = (t_vec4 *)ft_memalloc(sizeof(t_vec4) * o->nbr_vecs);
	if (o->vecs == 0)
		exit (1);
	o->vecs[0] = vec4(0, 1, 0, 1);
	o->vecs[1] = vec4(0, -1, 0, 1);
	while (i < row)
	{
		while (j < col)
		{
			o->vecs[i * row + j  + 2] = vec4(sin(i * M_PI / row) * cos(j * 2 * M_PI / col), cos(i * M_PI / row), sin(i * M_PI / row) * sin(j * 2 * M_PI / col), 1);
			j++;
		}
		j = 0;
		i++;
	}
}

static void	make_sphere_trgles(t_obj *o, int row, int col)
{
	int i;

	i = 0;
	o->trgles = (t_trgle *)ft_memalloc(sizeof(t_trgle) * (row + 1) * col);
	if (o->vecs == 0)
		exit (1);
	while (i < row)
	{
		o->trgles[i] = trgle(&(o->vecs)[0], &(o->vecs)[1], &(o->vecs)[i + 2]);
		i++;
	}
	//o->trgles[] = trgle(&(o->vecs)[0], &(o->vecs)[1], &(o->vecs)[2]);
	o->nbr_trgles = 1;
}

t_obj	*make_sphere(int row, int col)
{
	t_obj	*o;

	o = (t_obj *)ft_memalloc(sizeof(t_obj));
	o->nbr_vecs = 2 + (row * col);
	make_sphere_vertex(o, row, col);
	make_sphere_trgles(o, row, col);
	o->nbr_lines = 0;
	o->scale = vec4(1.0, 1.0, 1.0, 1.0);
	return (o);
}
