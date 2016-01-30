/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 18:45:24 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/30 17:52:13 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_file(char c)
{
	if (ft_isdigit(c))
		return (1);
	if (c != ' ' && c != '\0')
		put_error();
	return (0);
}

void		read_first_line(char *line, t_fdf *fdf)
{
	int				i;
	unsigned int	x;

	i = 0;
	x = 0;
	while (*line != '\0')
	{
		while (*line == ' ')
			line++;
		i = ft_atoi(line);
		if (*line == '-' && i < 0)
			line++;
		while (check_file(*line))
			line++;
		push_back_vec4(&fdf->lst, new_vec4(vec4((float)x, i, fdf->lst.y, 1)));
		fdf->max = (ABS(i) > (int)fdf->max) ? (unsigned int)ABS(i) : fdf->max;
		x++;
		fdf->lst.size++;
		while (*line == ' ')
			line++;
	}
	if (fdf->lst.y && x != fdf->lst.x)
		put_error();
	else
		fdf->lst.x = x;
}

void		read_fdf2(t_obj *o, t_fdf *fdf)
{
	if (fdf->lst.x == 0 || fdf->lst.y == 0)
		put_error();
	fdf_lst_to_array(o, fdf);
	o->nbr_trgles = (fdf->lst.x - 1) * (fdf->lst.y - 1) * 2;
	o->trgles = (t_trgle*)ft_memalloc(sizeof(t_trgle) * o->nbr_trgles);
	if (o->trgles == 0)
		put_error();
	make_fdf_trgle(o, fdf);
	make_fdf_line(o, fdf);
	make_fdf_line2(o, fdf);
	clean_fdf(fdf);
	o->render_type = 0;
	o->nbr_vecs = fdf->lst.size;
}

t_obj		*read_fdf(t_app *app, char *filename)
{
	int		fd;
	t_fdf	fdf;
	t_vec4	*tmp;
	char	*line;
	t_obj	*o;

	tmp = 0;
	fdf.max = 1;
	o = (t_obj*)ft_memalloc(sizeof(t_obj));
	fd = open(filename, O_RDONLY);
	if (o == 0 || fd == -1)
		put_error();
	ft_strcpy(o->name, filename);
	ft_bzero(&fdf, sizeof(t_fdf));
	while ((get_next_line(fd, &line)) > 0)
	{
		read_first_line(line, &fdf);
		fdf.lst.y++;
		free(line);
	}
	read_fdf2(o, &fdf);
	close(fd);
	o->obj_color = 0;
	do_color(app, o);
	return (o);
}

void		load_all_fdf(t_app *app)
{
	int		i;
	t_obj	*o;

	i = 1;
	while (i < app->ac)
	{
		o = new_obj(app, read_fdf(app, app->av[i]));
		o->scale = vec4(800, 800, 800, 1);
		o->rot = vec4(0, -M_PI / 4, 0, 1);
		o->have_color = 0;
		o->render_type = 3;
		i++;
	}
}
