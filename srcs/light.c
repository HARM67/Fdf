/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 05:28:28 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 15:37:34 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	do_light(t_app *app, t_trgle t)
{
	t_light	light;
	float	lum;
	float	amb;
	int		i;

	amb = app->ambient;
	light.d = vec4(-0.5, 1, 0.5, 0);
	i = 0;
	if (app->a_light)
	{
		lum = prod_scal(normalize(t.normal), normalize(light.d)) *
			app->light_coef;
		lum = (lum < 0) ? 0 : lum;
		while (i < 3)
		{
			t.p[i]->color.r = (t.p[i]->color.r * (1 - amb) * lum) +
								(t.p[i]->color.r * amb);
			t.p[i]->color.g = (t.p[i]->color.g * (1 - amb) * lum) +
								(t.p[i]->color.g * amb);
			t.p[i]->color.b = (t.p[i]->color.b * (1 - amb) * lum) +
								(t.p[i]->color.b * amb);
			i++;
		}
	}
}
