/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 18:31:10 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/14 18:57:13 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_obj	*new_obj(t_app *app, t_obj *o)
{
	t_obj *tmp;

	if (0 == app->scene.first_obj)
	{
		app->scene.first_obj = o;
		app->scene.last_obj = o;
		return (o);
	}
	
	tmp = app->scene.first_obj;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = o;
	o->previous = tmp;
	app->scene.last_obj = o;
	return (o);
}

