/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 18:45:24 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/23 04:47:08 by mfroehly         ###   ########.fr       */
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

void	clean_fdf(t_fdf *fdf)
{
	t_vec4 *tmp;
	t_vec4 *tmp2;

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
	unsigned int i;
	t_vec4 *tmp;
	float		c;

	i = 0;
	o->vecs = (t_vec4*)ft_memalloc(sizeof(t_vec4) * fdf->lst.size);
	o->vecs_orig = (t_vec4*)ft_memalloc(sizeof(t_vec4) * fdf->lst.size);
	if (!o->vecs_orig)
		exit (1);
	tmp = fdf->lst.first;
	while (i < fdf->lst.size && tmp)
	{
		c = (float)(tmp->y / fdf->max);
		
		tmp->color = color(55 + 200 * c,55 + 200 * c,55 + 200 * c, 255);
		if (c <= 0.003)
		{
			tmp->color = color(0, 0, 100, 255);
		}
		/*else if (c > 0.003 && c <= 0.01)
		{
			tmp->color = color(50, 100, 50, 255);
		}*/
		else if (c > 0.003 && c <= 0.2)
		{
			tmp->color = color(75, 75 + (unsigned char)(c * 300), 20, 255);
		}
		tmp->y /= fdf->max;
		tmp->x -= fdf->lst.x / 2;
		tmp->z -= fdf->lst.y / 2;
		tmp->x =  tmp->x /( (fdf->lst.x > fdf->lst.y) ? fdf->lst.x : fdf->lst.y);
		tmp->z =  tmp->z / ((fdf->lst.x > fdf->lst.y) ? fdf->lst.x : fdf->lst.y);
		tmp->y =  tmp->y / ((fdf->lst.x > fdf->lst.y) ? fdf->lst.x : fdf->lst.y);
		o->vecs_orig[i] = *tmp;
		i++;
		tmp = tmp->next;
	}
}
t_vec4	calc_normal(t_trgle t)
{
	t_vec4	rt;

	rt = prod_vec(sous_vec4(*t.p[1], *t.p[0]), sous_vec4(*t.p[2], *t.p[0]));
	return (rt);
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
	//		o->trgles[j] = trgle(&o->vecs[(y * fdf->lst.x) + x + 1], &o->vecs[(y * fdf->lst.x) + x], &o->vecs[(y * fdf->lst.x) + x + fdf->lst.x]);
			o->trgles[j] = trgle(&o->vecs[(y * fdf->lst.x) + x + fdf->lst.x], &o->vecs[(y * fdf->lst.x) + x], &o->vecs[(y * fdf->lst.x) + x + 1]);

	//		o->trgles[j + 1] = trgle(&o->vecs[(y * fdf->lst.x) + x + fdf->lst.x], &o->vecs[(y * fdf->lst.x) + x + fdf->lst.x + 1], &o->vecs[(y * fdf->lst.x) + x +1]);
			o->trgles[j + 1] = trgle(&o->vecs[(y * fdf->lst.x) + x +1], &o->vecs[(y * fdf->lst.x) + x + fdf->lst.x + 1],&o->vecs[(y * fdf->lst.x) + x + fdf->lst.x] );
		//	o->trgles[j].normal = calc_normal(o->trgles[j]);
		//	o->trgles[j + 1].normal = calc_normal(o->trgles[j + 1]);
			//ft_printf("%f %f %f\n", o->trgles[j].normal.x, o->trgles[j].normal.y, o->trgles[j].normal.z);
			x++;
			j += 2;
		}
		x = 0;
		y++;
	}
}

void	make_fdf_line(t_obj *o, t_fdf *fdf)
{
	int x;
	int y;
	int j;
	o->nbr_lines = (fdf->lst.x - 1) * fdf->lst.y;

	o->lines = (t_line*)ft_memalloc(sizeof(t_line) * o->nbr_lines);
	x = 0;
	y = 0;
	j = 0;
	while (y < fdf->lst.y)
	{
		while (x < fdf->lst.x - 1)
		{
			o->lines[j] = line(&o->vecs[(y * fdf->lst.x) + x], &o->vecs[(y * fdf->lst.x) + x + 1]);
			x++;
			j++;
		}
		x = 0;
		y++;
	}
}

void	make_fdf_line2(t_obj *o, t_fdf *fdf)
{
	int x;
	int y;
	int j;
	o->nbr_lines2 = (fdf->lst.y - 1) * fdf->lst.x;

	o->lines2 = (t_line*)ft_memalloc(sizeof(t_line) * o->nbr_lines2);
	x = 0;
	y = 0;
	j = 0;
	while (x < fdf->lst.x)
	{
		while (y < fdf->lst.y - 1)
		{
		o->lines2[j] = line(&o->vecs[(y * fdf->lst.x) + x], &o->vecs[(y * fdf->lst.x) + x +fdf->lst.x]);
			y++;
			j++;
		}
		y = 0;
		x++;
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
	ft_strcpy(o->name, filename);
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
	make_fdf_line(o, &fdf);
	make_fdf_line2(o, &fdf);
	clean_fdf(&fdf);
	o->render_type = 0;
	o->nbr_vecs = fdf.lst.size;
	close (fd);
	return (o);
}
