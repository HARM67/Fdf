/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 08:40:10 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 14:55:37 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	make_sphere_vertex(t_obj *o, int row, int col)
{
	int i;
	int j;

	i = 0;
	j = 0;
	o->vecs = (t_vec4 *)ft_memalloc(sizeof(t_vec4) * o->nbr_vecs);
	o->vecs_orig = (t_vec4 *)ft_memalloc(sizeof(t_vec4) * o->nbr_vecs);
	if (o->vecs == 0 || o->vecs_orig == 0)
		exit(1);
	o->vecs_orig[0] = vec4(0, 1, 0, 1);
	o->vecs_orig[1] = vec4(0, -1, 0, 1);
	while (i < row)
	{
		while (j < col)
		{
			o->vecs_orig[i * row + j + 2] = vec4(sin((i + 1) * M_PI / row) *
					cos((j + 1) * 2 * M_PI / col), cos((i + 1) * M_PI / row),
					sin((i + 1) * M_PI / row) * sin((j + 1) * 2 * M_PI / col),
					1);
			j++;
		}
		j = 0;
		i++;
	}
}

static int	make_sphere_trgles2(t_obj *o, unsigned int row, unsigned int col,
		unsigned int *i)
{
	unsigned int j;

	j = *i;
	while (*i < col * (row - 1))
	{
		if (((*i - col) % col) != col - 1)
		{
			o->trgles[j] = trgle(&(o->vecs)[*i - col + 2], &(o->vecs)[*i + 2],
					&(o->vecs)[*i + 3]);
			(*i)++;
			o->trgles[j + 1] = trgle(&(o->vecs)[*i + 2],
					&(o->vecs)[*i - col + 2], &(o->vecs)[*i - col + 1]);
			j += 2;
		}
		else
		{
			o->trgles[j] = trgle(&(o->vecs)[*i - col + 2], &(o->vecs)[*i + 2],
					&(o->vecs)[*i + 3 - col]);
			(*i)++;
			o->trgles[j + 1] = trgle(&(o->vecs)[*i + 2 - col],
					&(o->vecs)[*i - col + 2 - col], &(o->vecs)[*i - col + 1]);
			j += 2;
		}
	}
	return (j);
}

static void	make_sphere_trgles(t_obj *o, unsigned int row, unsigned int col)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	o->trgles = (t_trgle *)ft_memalloc(sizeof(t_trgle) * o->nbr_trgles);
	if (o->trgles == 0)
		exit(1);
	while (i < col)
	{
		if (i < col - 1)
			o->trgles[i] = trgle(&(o->vecs)[0], &(o->vecs)[i + 2],
					&(o->vecs)[i + 3]);
		else
			o->trgles[i] = trgle(&(o->vecs)[0], &(o->vecs)[i + 2],
					&(o->vecs)[2]);
		i++;
	}
	j = make_sphere_trgles2(o, row, col, &i);
	while (j < o->nbr_trgles)
	{
		o->trgles[j] = trgle(&(o->vecs)[1], &(o->vecs)[i - col + 3],
				&(o->vecs)[i - col + 2]);
		j++;
		i++;
	}
}

static void	sphere_vecs_relative(t_obj *o)
{
	unsigned int i;

	i = 0;
	while (i < o->nbr_vecs)
	{
		o->vecs_orig[i].relative_color = (o->vecs_orig[i].y + 1) / 2;
		i++;
	}
}

t_obj		*make_sphere(unsigned int row, unsigned int col)
{
	t_obj	*o;

	o = (t_obj *)ft_memalloc(sizeof(t_obj));
	ft_strcpy(o->name, "sphere");
	o->nbr_vecs = 2 + (row * col);
	o->nbr_trgles = (row - 2) * col * 2 + 2 * col;
	make_sphere_vertex(o, row, col);
	sphere_vecs_relative(o);
	make_sphere_trgles(o, row, col);
	o->nbr_lines = 0;
	o->scale = vec4(1.0, 1.0, 1.0, 1.0);
	return (o);
}
