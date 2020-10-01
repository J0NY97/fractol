/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:02:53 by jsalmi            #+#    #+#             */
/*   Updated: 2020/10/01 12:38:36 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move(int keycode, t_fractol *fractol, float move_speed)
{
	if (keycode == 125)
	{
		fractol->start.im -= move_speed;
		fractol->end.im -= move_speed;
	}
	else if (keycode == 126)
	{
		fractol->start.im += move_speed;
		fractol->end.im += move_speed;
	}
	else if (keycode == 124)
	{
		fractol->start.re -= move_speed;
		fractol->end.re -= move_speed;
	}
	else if (keycode == 123)
	{
		fractol->start.re += move_speed;
		fractol->end.re += move_speed;
	}
}

void	change_color(int keycode, t_fractol *fractol)
{
	if (keycode == 15 || keycode == 17)
		fractol->hue += keycode == 15 ? 1 : -1;
	else if (keycode == 5 || keycode == 4)
		fractol->saturation += keycode == 5 ? 1 : -1;
	else if (keycode == 11 || keycode == 45)
		fractol->color_value += keycode == 11 ? 1 : -1;
}

int		input(int keycode, t_fractol *fractol)
{
	float	move_speed;

	move_speed = 0.05f / (float)fractol->zoom;
	move(keycode, fractol, move_speed);
	keycode == 78 ? zoom(fractol, fractol->win_info.width / 2,
			fractol->win_info.height / 2, -1) : 0;
	keycode == 69 ? zoom(fractol, fractol->win_info.width / 2,
			fractol->win_info.height / 2, 1) : 0;
	keycode == 53 ? exit(1) : 0;
	change_color(keycode, fractol);
	if (keycode == 37)
		fractol->julia_locked = fractol->julia_locked == 0;
	else if (keycode == 0)
		fractol->max_iteration - 1 > 0 ? fractol->max_iteration -= 1 : 0;
	else if (keycode == 1)
		fractol->max_iteration += 1;
	main_loop(fractol);
	return (0);
}
