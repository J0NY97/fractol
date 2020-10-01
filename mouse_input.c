/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:47:14 by jsalmi            #+#    #+#             */
/*   Updated: 2020/10/01 11:47:42 by jsalmi           ###   ########.fr       */
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
		fractol->zoom_re = w * 0.005f;
		fractol->zoom_im = h * 0.005f;
	}
	main_loop(fractol);
	return (0);
}

double interpolate(double start, double end, double interpolation)
{
    return start + ((end - start) * interpolation);
}

void	zoom(t_fractol *fractol, int x, int y, int dir)
{
	double speed;
	double mouse_re;
	double mouse_im;

	speed = dir == 1 ? 1.05f : 1.0f / 1.05f;
	mouse_re = (double)x / ((double)fractol->win_info.width /
		(fractol->re_end - fractol->re_start)) + fractol->re_start;
	mouse_im = (double)y / ((double)fractol->win_info.height /
		(fractol->im_end - fractol->im_start)) + fractol->im_start;
	fractol->re_start = interpolate(mouse_re, fractol->re_start, 1.0 / speed);
	fractol->re_end = interpolate(mouse_re, fractol->re_end, 1.0 / speed);
	fractol->im_start = interpolate(mouse_im, fractol->im_start, 1.0 / speed);
	fractol->im_end = interpolate(mouse_im, fractol->im_end, 1.0 / speed);
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
