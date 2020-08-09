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

// @Fix: max_iter cant be less than 1
int		input(int keycode, t_fractol *fractol)
{
	if (keycode == 53)
		exit(1);
	else if (keycode == 15 || keycode == 17) // r
		fractol->hue += keycode == 15 ? 1 : -1;
	else if (keycode == 5 || keycode == 4) // g
		fractol->saturation += keycode == 5 ? 1 : -1;
	else if (keycode == 11 || keycode == 45) // b
		fractol->color_value += keycode == 11 ? 1 : -1;
	else if (keycode == 43) // < and >
	{
		fractol->zoom_re += 0.01f;
	}
	else if (keycode == 47)
	{
		fractol->zoom_im += 0.01f;
	}
	// else if (keycode == 45) // n and m
	// {
	// 	fractol->zoom_re -= 0.01f;
	// }
	// else if (keycode == 46)
	// {
	// 	fractol->zoom_im -= 0.01f;
	// }
	else if (keycode == 126 || keycode == 125) // movement keys arrow keys, up and down
	{
		if (keycode == 125)
		{
			fractol->im_start -= 0.01f;
			fractol->im_end -= 0.01f;
		}
		else if (keycode == 126)
		{
			fractol->im_start += 0.01f;
			fractol->im_end += 0.01f;
		}
	}
	else if (keycode == 123 || keycode == 124) // left and right
	{
		if (keycode == 124)
		{
			fractol->re_start -= 0.01f;
			fractol->re_end -= 0.01f;
		}
		else if (keycode == 123)
		{
			fractol->re_start += 0.01f;
			fractol->re_end += 0.01f;
		}
	}
	else if (keycode == 69 || keycode == 78) // zoom + and -
	{
		if (keycode == 78) // zoom out
		{
			fractol->im_start -= 0.01f;
			fractol->im_end += 0.01f;
			fractol->re_start -= 0.01f;
			fractol->re_end += 0.01f;

			fractol->max_iteration -= fractol->max_iteration - 1 > 0 ? 1 : 0;
		}
		else if (keycode == 69) // zoom in
		{
			fractol->im_start += 0.01f;
			fractol->im_end -= 0.01f;
			fractol->re_start += 0.01f;
			fractol->re_end -= 0.01f;

			fractol->max_iteration += 1;
		}
	}
	main_loop(fractol);
	return (0);
}
