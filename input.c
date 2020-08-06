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
	else if (keycode == 126 || keycode == 125) // arrow up and down
	{
		fractol->max_iteration += keycode == 126 ? 1 : -1;
		printf("max_iteration set to %d\n", fractol->max_iteration);
	}
	else if (keycode == 8 || keycode == 9) // c and v
	{
		fractol->opacity = ((fractol->opacity + (keycode == 8 ? 1 : -1)) % 255);
		printf("color set to %d\n", fractol->opacity);
	}
	else if (keycode == 15 || keycode == 5 || keycode == 11)
	{
		if (keycode == 15) // r
			fractol->r = (fractol->r + 1) % 255;
		else if (keycode == 5) // g
			fractol->g = (fractol->g + 1) % 255;
		else if (keycode == 11) // b
			fractol->b = (fractol->b + 1) % 255;
		printf("r: %d, g: %d, b: %d\n", fractol->r, fractol->g, fractol->b);
	}
	return (0);
}
