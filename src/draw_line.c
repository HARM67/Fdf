/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   ->y: mfroeh->y <mfroeh->y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 03:20:05 ->y mfroeh->y          #+#    #+#             */
/*   Updated: 2016/01/14 18:09:57 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_y(t_app *app, t_vec4 tmp, t_line *line)
{
	float f;
	t_vec4	tmp2;

	f = 0;
	while (f <= ABS(tmp.y))
	{
		if ((*line->p[0]).y < (*line->p[1]).y)
		{
			tmp2 = vec4((*line->p[1]).x + ((-f / tmp.y) * tmp.x), (*line->p[1]).y - f, 0, 0);
			tmp2.color = color_pos((*line->p[0]).color, (*line->p[1]).color, -f / tmp.y);
		}
		else if ((*line->p[0]).y > (*line->p[1]).y)
		{
			tmp2 = vec4((*line->p[1]).x + ((f / tmp.y) * tmp.x), (*line->p[1]).y + f, 0, 0);
			tmp2.color = color_pos((*line->p[0]).color, (*line->p[1]).color, f / tmp.y);
		}
		f += 1;
		draw_vec4(app, tmp2);
	}
}


void	draw_line_x(t_app *app, t_vec4 tmp, t_line *line)
{
	float f;
	t_vec4	tmp2;

	f = 0;
	while (f <= ABS(tmp.x))
	{
		if ((*line->p[0]).x < (*line->p[1]).x)
		{
			tmp2 = vec4((*line->p[1]).x - f, (*line->p[1]).y + ((-f / tmp.x) * tmp.y), 0, 0);
			tmp2.color = color_pos((*line->p[0]).color, (*line->p[1]).color, -f / tmp.x);
		}
		else if ((*line->p[0]).x > (*line->p[1]).x)
		{
			tmp2 = vec4((*line->p[1]).x + f, (*line->p[1]).y + ((f / tmp.x) * tmp.y), 0, 0);
			tmp2.color = color_pos((*line->p[0]).color, (*line->p[1]).color, f / tmp.x);
		}
		f += 1;
		draw_vec4(app, tmp2);
	}
}

void	draw_line(t_app *app, t_line *line)
{
	t_vec4	tmp;
	t_vec4	tmp2;

	tmp = sous_vec4(*line->p[0], *line->p[1]);
	if (ABS(tmp.x) < ABS(tmp.y))
		draw_line_y(app, tmp, line);
	else
		draw_line_x(app, tmp, line);
}
