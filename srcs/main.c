/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 07:36:14 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/28 13:56:38 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_app	app;

	if (ac < 2)
		return (1);
	ft_bzero(&app, sizeof(t_app));
	app.ac = ac;
	app.av = av;
	app_init(&app);
	app_run(&app);
	return (0);
}
