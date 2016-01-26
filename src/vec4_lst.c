/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 16:39:40 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/26 06:57:30 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec4	*new_vec4(t_vec4 v)
{
	t_vec4 *rt;

	rt = (t_vec4*)ft_memalloc(sizeof(t_vec4));
	if (rt == 0)
		exit(1);
	*rt = v;
	rt->next = 0;
	return (rt);
}

void	push_back_vec4(t_vec4_lst *lst, t_vec4 *elem)
{
	elem->color = color(255, 255, 255, 255);
	if (lst->size == 0)
	{
		lst->first = elem;
		lst->last = elem;
	}
	else
	{
		lst->last->next = elem;
		lst->last = elem;
	}
}
