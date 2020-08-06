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

void	set_pixel(t_fractol *info, int x, int y, int *rgb)
{
	int i;

	i = (x * info->bpp / 8) + (y * info->size_line);
	info->data[i] = (uint8_t)rgb[0];
	info->data[i + 1] = (uint8_t)rgb[1];
	info->data[i + 2] = (uint8_t)rgb[2];
	info->data[i + 3] = (uint8_t)0;
}

void	filled_rect(t_fractol *info, int x, int y, int w, int h)
{
	int x1;
	int y1;
	int color[3];

	color[0] = 255;
	color[1] = 255;
	color[2] = 255;
	y1 = y;
	while (y1 < y + h)
	{
		x1 = x;
		while (x1 < x + w)
		{
			set_pixel(info, x1, y1, color);
			x1++;
		}
		y1++;
	}
}

int		calculate_mandelbrot(t_fractol *fractol, t_complex complex)
{
	t_complex z;
	z.re = complex.re;
	z.im = complex.im;
	int n = 0;
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && n < fractol->max_iteration)
	{
		z.re = pow(z.re, 2.0) - pow(z.im, 2.0) + complex.re;
		z.im = 2.0 * z.re * z.im + complex.im;
		n++;
	}
    return n;
}

void	calculate(t_fractol *fractol)
{
	t_complex complex;
	int x = 0;
	int y = 0;
	int value;
	int color[3];

	float RE_START = -2.0f;
	float RE_END = 1.0f;
	float IM_START = -1.0f;
	float IM_END = 1.0f;
	while (x < fractol->win_info.width)
	{
		y = 0;
		while (y < fractol->win_info.height)
		{
			complex.re = RE_START + ((float)x / fractol->win_info.width) * (RE_END - RE_START);
        	complex.im = IM_START + ((float)y / fractol->win_info.height) * (IM_END - IM_START);
			if (fractol->toggle_mandelbrot)
				value = calculate_mandelbrot(fractol, complex);
			color[0] = 255 - (int)(value * 255 / fractol->max_iteration);
			color[1] = 255 - (int)(value * 255 / fractol->max_iteration);
			color[2] = 255 - (int)(value * 255 / fractol->max_iteration);
        	set_pixel(fractol, x, y, color);
			y++;
		}
		x++;
	}
}
