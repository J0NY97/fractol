/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:02:53 by jsalmi            #+#    #+#             */
/*   Updated: 2020/10/01 14:30:26 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		select_fractol(t_fractol *fractol, t_complex begin)
{
	int value;

	value = 0;
	if (fractol->toggle_mandelbrot)
		value = calculate_mandelbrot(fractol, begin);
	else if (fractol->toggle_julia)
		value = calculate_julia(fractol, fractol->extra, begin);
	else if (fractol->toggle_own)
		value = calculate_own(fractol, begin);
	else if (fractol->toggle_newton)
		value = calculate_newton(fractol, begin);
	return (value);
}

void	*calculate(void *original_fractol)
{
	t_fractol	*fractol;
	int			x;
	int			y;
	int			value;
	int			color[3];

	x = -1;
	fractol = original_fractol;
	while (++x < fractol->win_info.width)
	{
		y = fractol->calc_info.start_y - 1;
		while (++y < fractol->calc_info.max_height)
		{
			value = select_fractol(fractol, set_complex(fractol->start.re +
			((double)x / (double)fractol->win_info.width) * (fractol->end.re -
			fractol->start.re), fractol->start.im + ((double)y /
			(double)fractol->win_info.height) * (fractol->end.im -
			fractol->start.im)));
			get_color(color, (int)(value * fractol->hue /
				fractol->max_iteration), fractol->saturation,
					value < fractol->max_iteration ? fractol->color_value : 0);
			set_pixel(fractol, x, y, color);
		}
	}
	return (original_fractol);
}
