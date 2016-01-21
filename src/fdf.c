/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 18:45:24 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/20 23:27:28 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_arg(char *line)
{
	return (0);
}

void	read_first_line(char *line, t_fdf *fdf)
{
	int i;
	unsigned int	x;

	i = 0;
	x = 0;
	while (*line != '\0')
	{
		i = ft_atoi(line);
		if (*line == '-' && i < 0)
			line++;
		while (ft_isdigit(*line))
			line++;
		push_back_vec4(&fdf->lst,new_vec4(vec4((float)x, i, fdf->lst.y, 1)));
		fdf->max = (ABS(i) > fdf->max) ? ABS(i) : fdf->max;
		x++;
		fdf->lst.size++;
		if (*line == '\0')
			break ;
		while(*line == ' ')
			line++;
	}
	if (fdf->lst.y && x != fdf->lst.x)
		exit (1);
	else
		fdf->lst.x = x;
}

void	fdf_lst_to_array(t_obj *o, t_fdf *fdf)
{
	unsigned int i;
	t_vec4 *tmp;
	int		c;

	i = 0;
	o->vecs = (t_vec4*)ft_memalloc(sizeof(t_vec4) * fdf->lst.size);
	if (!o->vecs)
		exit (1);
	tmp = fdf->lst.first;
	while (i < fdf->lst.size && tmp)
	{
		c = tmp->y * 255 / fdf->max;
		tmp->color = color(c, 0, 255 - c, 255);
		tmp->y /= fdf->max;
		tmp->x -= fdf->lst.x / 2;
		tmp->z -= fdf->lst.y / 2;
		o->vecs[i] = *tmp;
		i++;
		tmp = tmp->next;
	}
}

void	make_fdf_trgle(t_obj *o, t_fdf *fdf)
{
	int x;
	int y;
	int j;
	o->nbr_trgles = (fdf->lst.x - 1) * (fdf->lst.y - 1) * 2 ;

	o->trgles = (t_trgle*)ft_memalloc(sizeof(t_trgle) *(fdf->lst.x - 1) *(fdf->lst.y - 1) * 2 );
	x = 0;
	y = 0;
	j = 0;
	while (y < fdf->lst.y - 1)
	{
		while (x < fdf->lst.x - 1)
		{
			o->trgles[j] = trgle(&o->vecs[(y * fdf->lst.x) + x + 1], &o->vecs[(y * fdf->lst.x) + x], &o->vecs[(y * fdf->lst.x) + x + fdf->lst.x]);
			o->trgles[j + 1] = trgle(&o->vecs[(y * fdf->lst.x) + x + fdf->lst.x], &o->vecs[(y * fdf->lst.x) + x + fdf->lst.x + 1], &o->vecs[(y * fdf->lst.x) + x +1]);
			x++;
			j += 2;
		}
		x = 0;
		y++;
	}
}

t_obj	*read_fdf(t_app *app, char *filename)
{
	int fd;
	t_fdf fdf;
	t_vec4	*tmp;
	char *line;
	t_obj *o;

	tmp = 0;
	fdf.max = 1;
	o = (t_obj*)ft_memalloc(sizeof(t_obj));
	ft_bzero(&fdf, sizeof(t_fdf));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit (1);
	while (get_next_line(fd, &line))
	{
		read_first_line(line, &fdf);
		fdf.lst.y++;
		free(line);
	}
	fdf_lst_to_array(o, &fdf);
	make_fdf_trgle(o, &fdf);
	o->render_type = 0;
	o->nbr_vecs = fdf.lst.size;
	close (fd);
	return (o);
}
