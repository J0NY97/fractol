/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:02:57 by jsalmi            #+#    #+#             */
/*   Updated: 2020/10/01 11:59:01 by jsalmi           ###   ########.fr       */
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
	double		re;
	double		im;
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

	double		zoom;

	// color modifiers
	unsigned int	hue;
	unsigned int	saturation;
	unsigned int	color_value;

	// not actually zoom, change these to something else
	double		zoom_re;
	double		zoom_im;

	double		re_start;
	double		re_end;
	double		im_start;
	double		im_end;

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
void			zoom(t_fractol *fractol, int x, int y, int dir);
void			window_init(t_fractol *fractol);
void			default_mandelbrot(t_fractol *fractol);
void			default_julia(t_fractol *fractol);
void			default_own(t_fractol *fractol);
void			default_newton(t_fractol *fractol);
void			ft_error(char *msg);
void			ft_usage(char *prog_name);
int				mouse_input(int key, int x, int y, t_fractol *fractol);
int				julia_input(int x, int y, t_fractol *fractol);
void			set_pixel(t_fractol *fractol, int x, int y, int *rgb);
t_complex		set_complex(float re, float im);
void			get_color(int *color, int hue, int saturation, int value);

#endif
