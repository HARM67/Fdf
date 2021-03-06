/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 09:27:50 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 14:26:31 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_y(t_app *app, t_vec4 tmp, t_line *line, t_obj *o)
{
	float	f;
	t_vec4	tmp2;

	f = 0;
	while (f <= ABS((int)(tmp.y)))
	{
		if ((*line->p[0]).y < (*line->p[1]).y)
		{
			tmp2 = vec4((*line->p[1]).x + ((-f / tmp.y) * tmp.x),
					(*line->p[1]).y - f,
					(*line->p[1]).z + ((-f / tmp.y) * tmp.z), 0);
			tmp2.color = color_pos((*line->p[0]).color, (*line->p[1]).color,
					-f / tmp.y);
		}
		else if ((*line->p[0]).y > (*line->p[1]).y)
		{
			tmp2 = vec4((*line->p[1]).x + ((f / tmp.y) * tmp.x),
					(*line->p[1]).y + f,
					(*line->p[1]).z + ((f / tmp.y) * tmp.z), 0);
			tmp2.color = color_pos((*line->p[0]).color, (*line->p[1]).color,
					f / tmp.y);
		}
		f += 1;
		draw_vec4(app, tmp2, o);
	}
}

void	draw_line_x(t_app *app, t_vec4 tmp, t_line *line, t_obj *o)
{
	float	f;
	t_vec4	tmp2;

	f = 0;
	while (f <= ABS((int)(tmp.x)))
	{
		if ((*line->p[0]).x < (*line->p[1]).x)
		{
			tmp2 = vec4((*line->p[1]).x - f,
					(*line->p[1]).y + ((-f / tmp.x) * tmp.y),
					(*line->p[1]).z + ((-f / tmp.x) * tmp.z), 0);
			tmp2.color = color_pos((*line->p[0]).color,
					(*line->p[1]).color, -f / tmp.x);
		}
		else if ((*line->p[0]).x > (*line->p[1]).x)
		{
			tmp2 = vec4((*line->p[1]).x + f,
				(*line->p[1]).y + ((f / tmp.x) * tmp.y),
				(*line->p[1]).z + ((f / tmp.x) * tmp.z), 0);
			tmp2.color = color_pos((*line->p[0]).color,
					(*line->p[1]).color, f / tmp.x);
		}
		f += 1;
		draw_vec4(app, tmp2, o);
	}
}

void	draw_line(t_app *app, t_line *line, t_obj *o)
{
	t_vec4	tmp;

	tmp = sous_vec4(*line->p[0], *line->p[1]);
	if (ABS(tmp.x) < ABS(tmp.y))
		draw_line_y(app, tmp, line, o);
	else
		draw_line_x(app, tmp, line, o);
}
