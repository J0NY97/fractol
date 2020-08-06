/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:02:57 by jsalmi            #+#    #+#             */
/*   Updated: 2020/08/06 13:02:58 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "libft/libft.h"

typedef struct s_complex
{
	double		re;
	double		im;
}				t_complex;


typedef struct	t_win_info
{
	int			width;
	int			height;
	char		*title;
}				t_win_info;

typedef struct	s_fractol
{
	int			run;

	t_win_info	win_info;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;

	int			max_iteration;
	int			opacity;
	int			r;
	int			g;
	int			b;

	int			toggle_julia;
	int			toggle_mandelbrot;
	int			toggle_own;
}				t_fractol;

int				input(int keycode, t_fractol *fractol);
void			calculate(t_fractol *fractol);
void			filled_rect(t_fractol *info, int x, int y, int w, int h);

#endif
