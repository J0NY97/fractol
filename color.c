/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:55:20 by jsalmi            #+#    #+#             */
/*   Updated: 2020/10/01 14:11:36 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

	saturation == 0 ? set_color(color, value, value, value) : 0;
	if (saturation == 0)
		return ;
	region = hue / 43;
	remainder = (hue - (region * 43)) * 6;
	p = (value * (255 - saturation)) >> 8;
	q = (value * (255 - ((saturation * remainder) >> 8))) >> 8;
	t = (value * (255 - ((saturation * (255 - remainder)) >> 8))) >> 8;
	if (region == 1 || region == 2 || region == 3 || region == 4)
	{
		region == 0 ? set_color(color, value, t, p) : 0;
		region == 1 ? set_color(color, q, value, p) : 0;
		region == 2 ? set_color(color, p, value, t) : 0;
		region == 3 ? set_color(color, p, q, value) : 0;
		region == 4 ? set_color(color, t, p, value) : 0;
	}
	else
		set_color(color, value, p, q);
}
