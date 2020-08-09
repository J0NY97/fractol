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
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "mlx.h"
# include "libft/libft.h"

typedef struct s_complex
{
	float		re;
	float		im;
}				t_complex;


typedef struct	s_win_info
{
	int			width;
	int			height;
	char		*title;
}				t_win_info;

typedef	struct	s_calc_info
{
	int			start_x;
	int			start_y;
	int			max_height;
}				t_calc_info;


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

	float		zoom;

	// color modifiers
	unsigned int	hue;
	unsigned int	saturation;
	unsigned int	color_value;

	// not actually zoom, change these to something else
	float		zoom_re;
	float		zoom_im;

	float		re_start;
	float		re_end;
	float		im_start;
	float		im_end;

	int			julia_locked;

	int			toggle_julia;
	int			toggle_mandelbrot;
	int			toggle_own;
	int			toggle_newton;

// thread stuff
	int			thread_amount;
	t_calc_info	calc_info;
}				t_fractol;

void			ft_error(char *msg);
int				input(int keycode, t_fractol *fractol);
void			*calculate(void *fractol);
int				main_loop(t_fractol *fractol);

#endif
