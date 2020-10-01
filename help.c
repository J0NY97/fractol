/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:55:52 by jsalmi            #+#    #+#             */
/*   Updated: 2020/10/01 11:56:15 by jsalmi           ###   ########.fr       */
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

t_complex	set_complex(float re, float im)
{
	t_complex	comp;
	comp.re = re;
	comp.im = im;
	return comp;
}
