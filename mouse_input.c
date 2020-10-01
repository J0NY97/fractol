/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:47:14 by jsalmi            #+#    #+#             */
/*   Updated: 2020/10/01 12:39:28 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		julia_input(int x, int y, t_fractol *fractol)
{
	int w;
	int h;

	if (!fractol->julia_locked)
	{
		w = x - fractol->win_info.width / 2;
		h = y - fractol->win_info.height / 2;
		fractol->extra.re = w * 0.005f;
		fractol->extra.im = h * 0.005f;
	}
	main_loop(fractol);
	return (0);
}

double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

void	zoom(t_fractol *fractol, int x, int y, int dir)
{
	double speed;
	double mouse_re;
	double mouse_im;

	speed = dir == 1 ? 1.05f : 1.0f / 1.05f;
	mouse_re = (double)x / ((double)fractol->win_info.width /
		(fractol->end.re - fractol->start.re)) + fractol->start.re;
	mouse_im = (double)y / ((double)fractol->win_info.height /
		(fractol->end.im - fractol->start.im)) + fractol->start.im;
	fractol->start.re = interpolate(mouse_re, fractol->start.re, 1.0 / speed);
	fractol->end.re = interpolate(mouse_re, fractol->end.re, 1.0 / speed);
	fractol->start.im = interpolate(mouse_im, fractol->start.im, 1.0 / speed);
	fractol->end.im = interpolate(mouse_im, fractol->end.im, 1.0 / speed);
}

int		mouse_input(int key, int x, int y, t_fractol *fractol)
{
	if (!fractol->toggle_julia || fractol->julia_locked)
	{
		if (key == 4)
		{
			fractol->zoom += 1;
			zoom(fractol, x, y, 1);
		}
		else if (key == 5)
		{
			fractol->zoom -= 1;
			zoom(fractol, x, y, -1);
		}
	}
	main_loop(fractol);
	return (0);
}
