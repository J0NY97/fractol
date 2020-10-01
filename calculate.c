/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:02:53 by jsalmi            #+#    #+#             */
/*   Updated: 2020/10/01 11:59:37 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		calculate_mandelbrot(t_fractol *fractol, t_complex begin)
{
	t_complex z;
	t_complex temp;
	int n;

	z.re = begin.re;
	z.im = begin.im;
	n = 0;
	while (z.re * z.re + z.im * z.im <= 4 && n < fractol->max_iteration)
	{
		temp.re = z.re;
		z.re = z.re * z.re - z.im * z.im + begin.re;
		z.im = 2.0 * temp.re * z.im + begin.im;
		n++;
	}
    return n;
}

int		calculate_julia(t_fractol *fractol, t_complex comp,  t_complex begin)
{
	t_complex z;
	t_complex temp;
    int n;

	z = set_complex(begin.re, begin.im);
	n = 0;
    while (z.re * z.re + z.im * z.im <= 4 && n < fractol->max_iteration)
	{
		temp.re = z.re;
		z.re = z.re * z.re - z.im * z.im + comp.re;
		z.im = 2.0 * temp.re * z.im + comp.im;
        n += 1;
	}
    if (n == fractol->max_iteration)
        return (fractol->max_iteration);
    return (n + 1 - log(log2(z.re * z.re + z.im * z.im)));
}

int		calculate_own(t_fractol *fractol, t_complex begin)
{
	t_complex z;
	t_complex temp;
	int n;

	z = set_complex(begin.re, begin.im);
	n = 0;
	while (z.re * z.re + z.im * z.im <= 4 && n < fractol->max_iteration)
	{
		temp.re = z.re;
		z.re = fabs(z.re * z.re - z.im * z.im + begin.re);
		z.im = fabs(2.0f * temp.re * z.im + begin.im);
		n += 1;
	}
    if (n == fractol->max_iteration)
        return fractol->max_iteration;
    return n;
}

int		calculate_newton(t_fractol *fractol, t_complex begin)
{
	t_complex	z;
	t_complex	temp;
	int			i;

	z.re = begin.re;
	z.im = begin.im;
	i = 0;
	while ((z.re - begin.re) * (z.re - begin.re) +
			(z.im - begin.im) * (z.im - begin.im) <= 99 &&
			i < fractol->max_iteration)
	{
		temp.re = z.re;
		z.re = 3 * z.re / 4 - z.re *
			(z.re * z.re - 3 * z.im * z.im) /
			(z.re * z.re + z.im * z.im) /
			(z.re * z.re + z.im * z.im) /
			(z.re * z.re + z.im * z.im) / 4;
		z.im = 3 * z.im / 4 - z.im *
			(z.im * z.im - 3 * temp.re * temp.re) /
			(temp.re * temp.re + z.im * z.im) /
			(temp.re * temp.re + z.im * z.im)/
			(temp.re * temp.re + z.im * z.im) / 4;
		i++;
	}
    return (i);
}

// @Improvement: make a "choose_fractal" function that returns the value
void	*calculate(void *thingelithong)
{
	t_fractol *fractol = thingelithong;
	t_complex comp;
	t_complex begin;
	int x;
	int y;
	int value;
	int color[3];

	x = 0;
	y = fractol->calc_info.start_y;
	comp = set_complex(fractol->zoom_re, fractol->zoom_im);
	while (x < fractol->win_info.width)
	{
		begin.re =
			fractol->re_start + ((double)x / (double)fractol->win_info.width)
				* (fractol->re_end - fractol->re_start);
		y = fractol->calc_info.start_y;
		while (y < fractol->calc_info.max_height)
		{
			begin.im =
				fractol->im_start + ((double)y / (double)fractol->win_info.height)
					* (fractol->im_end - fractol->im_start);
			if (fractol->toggle_mandelbrot)
				value = calculate_mandelbrot(fractol, begin);
			else if (fractol->toggle_julia)
				value = calculate_julia(fractol, comp, begin);
			else if (fractol->toggle_own)
				value = calculate_own(fractol, begin);
			else if (fractol->toggle_newton)
				value = calculate_newton(fractol, begin);
			get_color(color, (int)(value * fractol->hue /
				fractol->max_iteration), fractol->saturation,
					value < fractol->max_iteration ? fractol->color_value : 0);
			set_pixel(fractol, x, y, color);
			y++;
		}
		x++;
	}
	return (thingelithong);
}
