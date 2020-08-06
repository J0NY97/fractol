/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:02:53 by jsalmi            #+#    #+#             */
/*   Updated: 2020/08/06 13:02:54 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		input(int keycode, t_fractol *fractol)
{
	if (keycode == 53)
		exit(1);
	else if (keycode == 126 || keycode == 125)
	{
		fractol->max_iteration += keycode == 126 ? 1 : -1;
		printf("max_iteration set to %d\n", fractol->max_iteration);
	}
	return (0);
}
