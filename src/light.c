/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 05:28:28 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 05:34:40 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "fdf.h"

void	do_light(t_app *app, t_trgle t)
{
	t_light	light;
	float	lum;
	t_vec4	normal;

	light.d = vec4(-0.5, 1, 0.5, 0);
	if (app->a_light)
	{
		normal = normalize(t.normal);
		light.d = normalize(light.d);
		lum = prod_scal(normal, light.d) * app->light_coef;
		if (lum < app->ambient)
			lum = app->ambient;
		t.p[0]->color.r *= lum;
		t.p[0]->color.g *= lum;
		t.p[0]->color.b *= lum;
		t.p[1]->color.r *= lum;
		t.p[1]->color.g *= lum;
		t.p[1]->color.b *= lum;
		t.p[2]->color.r *= lum;
		t.p[2]->color.g *= lum;
		t.p[2]->color.b *= lum;
	}
}
