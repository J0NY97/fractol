/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:44:24 by jsalmi            #+#    #+#             */
/*   Updated: 2020/10/01 11:44:56 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	window_init(t_fractol *fractol)
{
	fractol->thread_amount = 8;
	fractol->run = 1;
	fractol->win_info.width = 1920;
	fractol->win_info.height = 1080;
	fractol->zoom = 1;
	fractol->max_iteration = 50;
	fractol->hue = 255;
	fractol->saturation = 255;
	fractol->color_value = 255;
	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, fractol->win_info.width, fractol->win_info.height, "fractol");
	fractol->img = mlx_new_image(fractol->mlx, fractol->win_info.width, fractol->win_info.height);
	fractol->data = mlx_get_data_addr(fractol->img, &fractol->bpp, &fractol->size_line, &fractol->endian);
}

void	default_mandelbrot(t_fractol *fractol)
{
	fractol->re_start = -2.0f;
	fractol->re_end = 1.0f;
	fractol->im_start = -1.0f;
	fractol->im_end = 1.0f;
	fractol->zoom_re = 0.0f;
	fractol->zoom_im = 0.0f;
}

void	default_julia(t_fractol *fractol)
{
	fractol->re_start = -1.0f;
	fractol->re_end = 1.0f;
	fractol->im_start = -1.2f;
	fractol->im_end = 1.2f;
	fractol->julia_locked = 1;
	fractol->zoom_re = 0.285f;
	fractol->zoom_im = 0.01f;
}

void	default_own(t_fractol *fractol)
{
	fractol->re_start = -2.5f;
	fractol->re_end = 1.0f;
	fractol->im_start = -1.0f;
	fractol->im_end = 1.0f;
	fractol->zoom_re = 0.0f;
	fractol->zoom_im = 0.0f;
}

void	default_newton(t_fractol *fractol)
{
	fractol->re_start = -1.0f;
	fractol->re_end = 1.0f;
	fractol->im_start = -1.0f;
	fractol->im_end = 1.0f;
	fractol->zoom_re = 2.5f;
	fractol->zoom_im = 0.15f;
}
