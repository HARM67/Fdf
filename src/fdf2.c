/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 06:22:52 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 06:49:43 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean_fdf(t_fdf *fdf)
{
	t_vec4	*tmp;
	t_vec4	*tmp2;

	tmp = fdf->lst.first;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = 0;
		tmp = tmp2;
	}
}

void	fdf_lst_to_array(t_obj *o, t_fdf *fdf)
{
	unsigned int	i;
	t_vec4			*tmp;

	i = 0;
	o->vecs = (t_vec4*)ft_memalloc(sizeof(t_vec4) * fdf->lst.size);
	o->vecs_orig = (t_vec4*)ft_memalloc(sizeof(t_vec4) * fdf->lst.size);
	if (!o->vecs_orig || !o->vecs)
		exit(1);
	tmp = fdf->lst.first;
	while (i < fdf->lst.size && tmp)
	{
		tmp->y /= fdf->max;
		tmp->x -= fdf->lst.x / 2;
		tmp->z -= fdf->lst.y / 2;
		tmp->x = tmp->x / ((fdf->lst.x > fdf->lst.y) ? fdf->lst.x : fdf->lst.y);
		tmp->z = tmp->z / ((fdf->lst.x > fdf->lst.y) ? fdf->lst.x : fdf->lst.y);
		tmp->y = tmp->y / ((fdf->lst.x > fdf->lst.y) ? fdf->lst.x : fdf->lst.y);
		o->vecs_orig[i] = *tmp;
		i++;
		tmp = tmp->next;
	}
}

void	make_fdf_trgle(t_obj *o, t_fdf *fdf)
{
	int	x;
	int	y;
	int	j;

	o->nbr_trgles = (fdf->lst.x - 1) * (fdf->lst.y - 1) * 2;
	o->trgles = (t_trgle*)ft_memalloc(sizeof(t_trgle) * o->nbr_trgles);
	x = 0;
	y = 0;
	j = 0;
	while (y < fdf->lst.y - 1)
	{
		while (x < fdf->lst.x - 1)
		{
			o->trgles[j] = trgle(&o->vecs[(y * fdf->lst.x) + x + fdf->lst.x],
					&o->vecs[(y * fdf->lst.x) + x],
					&o->vecs[(y * fdf->lst.x) + x + 1]);
			o->trgles[j + 1] = trgle(&o->vecs[(y * fdf->lst.x) + x + 1],
					&o->vecs[(y * fdf->lst.x) + x + fdf->lst.x + 1],
					&o->vecs[(y * fdf->lst.x) + x + fdf->lst.x]);
			x++;
			j += 2;
		}
		x = 0;
		y++;
	}
}

void	make_fdf_line(t_obj *o, t_fdf *fdf)
{
	int	x;
	int	y;
	int	j;

	o->nbr_lines = (fdf->lst.x - 1) * fdf->lst.y;
	o->lines = (t_line*)ft_memalloc(sizeof(t_line) * o->nbr_lines);
	x = 0;
	y = 0;
	j = 0;
	while (y < fdf->lst.y)
	{
		while (x < fdf->lst.x - 1)
		{
			o->lines[j] = line(&o->vecs[(y * fdf->lst.x) + x],
					&o->vecs[(y * fdf->lst.x) + x + 1]);
			x++;
			j++;
		}
		x = 0;
		y++;
	}
}

void	make_fdf_line2(t_obj *o, t_fdf *fdf)
{
	int	x;
	int	y;
	int	j;

	o->nbr_lines2 = (fdf->lst.y - 1) * fdf->lst.x;
	o->lines2 = (t_line*)ft_memalloc(sizeof(t_line) * o->nbr_lines2);
	x = 0;
	y = 0;
	j = 0;
	while (x < fdf->lst.x)
	{
		while (y < fdf->lst.y - 1)
		{
			o->lines2[j] = line(&o->vecs[(y * fdf->lst.x) + x],
					&o->vecs[(y * fdf->lst.x) + x + fdf->lst.x]);
			y++;
			j++;
		}
		y = 0;
		x++;
	}
}
