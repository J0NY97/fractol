/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_calculation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:29:52 by jsalmi            #+#    #+#             */
/*   Updated: 2020/10/01 14:30:12 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		calculate_mandelbrot(t_fractol *fractol, t_complex begin)
{
	t_complex	z;
	t_complex	temp;
	int			i;

	z.re = begin.re;
	z.im = begin.im;
	i = 0;
	while (z.re * z.re + z.im * z.im <= 4 && i < fractol->max_iteration)
	{
		temp.re = z.re;
		z.re = z.re * z.re - z.im * z.im + begin.re;
		z.im = 2.0 * temp.re * z.im + begin.im;
		i++;
	}
	return (i);
}

int		calculate_julia(t_fractol *fractol, t_complex comp, t_complex begin)
{
	t_complex	z;
	t_complex	temp;
	int			i;

	z = set_complex(begin.re, begin.im);
	i = 0;
	while (z.re * z.re + z.im * z.im <= 4 && i < fractol->max_iteration)
	{
		temp.re = z.re;
		z.re = z.re * z.re - z.im * z.im + comp.re;
		z.im = 2.0 * temp.re * z.im + comp.im;
		i += 1;
	}
	if (i == fractol->max_iteration)
		return (fractol->max_iteration);
	return (i + 1 - log(log2(z.re * z.re + z.im * z.im)));
}

int		calculate_own(t_fractol *fractol, t_complex begin)
{
	t_complex	z;
	t_complex	temp;
	int			i;

	z = set_complex(begin.re, begin.im);
	i = 0;
	while (z.re * z.re + z.im * z.im <= 4 && i < fractol->max_iteration)
	{
		temp.re = z.re;
		z.re = fabs(z.re * z.re - z.im * z.im + begin.re);
		z.im = fabs(2.0f * temp.re * z.im + begin.im);
		i += 1;
	}
	if (i == fractol->max_iteration)
		return (fractol->max_iteration);
	return (i);
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
			(temp.re * temp.re + z.im * z.im) /
			(temp.re * temp.re + z.im * z.im) / 4;
		i++;
	}
	return (i);
}
