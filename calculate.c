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

void	set_color(int *color, int r, int g, int b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void	get_color(int *color, int hue, int saturation, int value)
{
    unsigned char region;
	unsigned char remainder;
	unsigned char p;
	unsigned char q;
	unsigned char t;

    if (saturation == 0)
    {
		set_color(color, value, value, value);
        return ;
    }

    region = hue / 43;
    remainder = (hue - (region * 43)) * 6;

    p = (value * (255 - saturation)) >> 8;
    q = (value * (255 - ((saturation * remainder) >> 8))) >> 8;
    t = (value * (255 - ((saturation * (255 - remainder)) >> 8))) >> 8;

    if (region == 0)
		set_color(color, value, t, p);
    else if (region == 1)
		set_color(color, q, value, p);
	else if (region == 2)
		set_color(color, p, value, t);
	else if (region == 3)
		set_color(color, p, q, value);
	else if (region == 4)
		set_color(color, t, p, value);
	else
		set_color(color, value, p, q);
}

t_complex	set_complex(float re, float im)
{
	t_complex	complex;
	complex.re = re;
	complex.im = im;
	return complex;
}

int		calculate_mandelbrot(t_fractol *fractol, t_complex complex, t_complex begin)
{
	t_complex z;
	t_complex temp;
	int n;

	z = set_complex(begin.re, begin.im);
	n = 0;
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4 && n < fractol->max_iteration)
	{
		temp.re = z.re;
		z.re = pow(z.re, 2.0) - pow(z.im, 2.0) + begin.re;
		z.im = 2.0 * temp.re * z.im + begin.im;
		n++;
	}
    return n;
}

int		calculate_julia(t_fractol *fractol, t_complex complex, t_complex begin)
{
	t_complex z;
	t_complex temp;
    int n;

	z = set_complex(begin.re, begin.im);
	n = 0;
    while (pow(z.re, 2.0f) + pow(z.im, 2.0f) <= 4 && n < fractol->max_iteration)
	{
		temp.re = z.re;
		z.re = pow(z.re, 2.0) - pow(z.im, 2.0) + complex.re;
		z.im = 2.0 * temp.re * z.im + complex.im;
        n += 1;
	}
    if (n == fractol->max_iteration)
        return (fractol->max_iteration);
    return (n + 1 - log(log2(pow(z.re, 2.0f) + pow(z.im, 2.0f))));
}

int		calculate_own(t_fractol *fractol, t_complex complex, t_complex begin)
{
	t_complex z;
	t_complex temp;
	int n;

	z = set_complex(begin.re, begin.im);
	n = 0;
	while (pow(z.re, 2.0f) + pow(z.im, 2.0f) <= 4 && n < fractol->max_iteration)
	{
		temp.re = z.re;
		z.re = fabs(pow(z.re, 2.0f) - pow(z.im, 2.0f) + begin.re);
		z.im = fabs(2.0f * temp.re * z.im + begin.im);
		n += 1;
	}
    if (n == fractol->max_iteration)
        return fractol->max_iteration;
    return n;
}

void	calculate(t_fractol *fractol)
{
	t_complex complex;
	t_complex begin;
	int x;
	int y;
	int value;
	int color[3];

	x = 0;
	y = 0;
	complex = set_complex(fractol->zoom_re, fractol->zoom_im);
	while (x < fractol->win_info.width)
	{
		y = 0;
		while (y < fractol->win_info.height)
		{
			begin.re =
				fractol->re_start + ((float)x / (float)fractol->win_info.width)
					* (fractol->re_end - fractol->re_start);
			begin.im =
				fractol->im_start + ((float)y / (float)fractol->win_info.height)
					* (fractol->im_end - fractol->im_start);
			if (fractol->toggle_mandelbrot)
				value = calculate_mandelbrot(fractol, complex, begin);
			else if (fractol->toggle_julia)
				value = calculate_julia(fractol, complex, begin);
			else if (fractol->toggle_own)
				value = calculate_own(fractol, complex, begin);
			get_color(color,
					(int)(value * fractol->hue / fractol->max_iteration),
					fractol->saturation,
					value < fractol->max_iteration ? fractol->color_value : 0);
        	set_pixel(fractol, x, y, color);
			y++;
		}
		x++;
	}
}
