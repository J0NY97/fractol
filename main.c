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

void	ft_error(char *msg)
{
	ft_putstr("\x1b[31m[Error] \x1b[0m");
	ft_putstr(msg);
	ft_putstr("\n");
	exit(1);
}

void	ft_usage(char *prog_name)
{
	ft_putstr("Usage: ");
	ft_putstr(prog_name);
	ft_putstr(" [mandelbrot | julia | own | newton]");
	ft_putstr("\n");
	exit(1);
}

void	change_fractol_type(t_fractol *fractol, char **argv)
{
	fractol->toggle_julia = 0;
	fractol->toggle_mandelbrot = 0;
	fractol->toggle_own = 0;
	fractol->toggle_newton = 0;
	if (ft_strcmp(argv[1], "julia") == 0)
		fractol->toggle_julia = 1;
	else if (ft_strcmp(argv[1], "mandelbrot") == 0)
		fractol->toggle_mandelbrot = 1;
	else if (ft_strcmp(argv[1], "own") == 0)
		fractol->toggle_own = 1;
	else if (ft_strcmp(argv[1], "newton") == 0)
		fractol->toggle_newton = 1;
	else
		ft_usage(argv[0]);
}

// @Improvement: make function "init_fractol" that will set the default values for different fractals
void	init(t_fractol *fractol)
{
	fractol->thread_amount = 8;
	fractol->run = 1;
	fractol->win_info.width = 1080;
	fractol->win_info.height = 720;
	fractol->win_info.title = ft_strdup("fractol"); // this could be moved in the the new window thing so we dont have to worry about this char *

	fractol->zoom = 1;
	fractol->max_iteration = 50;

	// colors
	fractol->hue = 255;
	fractol->saturation = 255;
	fractol->color_value = 255;

	if (fractol->toggle_mandelbrot)	// mandelbrot
	{
		fractol->re_start = -2.0f;
		fractol->re_end = 1.0f;
		fractol->im_start = -1.0f;
		fractol->im_end = 1.0f;

		fractol->zoom_re = 0.0f;
		fractol->zoom_im = 0.0f;
	}
	else if (fractol->toggle_julia) // julia
	{
		fractol->re_start = -1.0f;
		fractol->re_end = 1.0f;
		fractol->im_start = -1.2f;
		fractol->im_end = 1.2f;

		fractol->julia_locked = 1;
		fractol->zoom_re = 0.285f;
		fractol->zoom_im = 0.01f;
	}
	else if (fractol->toggle_own)	// burning ship
	{
		fractol->re_start = -2.5f;
		fractol->re_end = 1.0f;
		fractol->im_start = -1.0f;
		fractol->im_end = 1.0f;

		fractol->zoom_re = 0.0f;
		fractol->zoom_im = 0.0f;
	}
	else if (fractol->toggle_newton)	// newton
	{
		fractol->re_start = -1.0f;
		fractol->re_end = 1.0f;
		fractol->im_start = -1.0f;
		fractol->im_end = 1.0f;

		fractol->zoom_re = 2.5f;
		fractol->zoom_im = 0.15f;
	}

	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, fractol->win_info.width, fractol->win_info.height, fractol->win_info.title);
	fractol->img = mlx_new_image(fractol->mlx, fractol->win_info.width, fractol->win_info.height);
	fractol->data = mlx_get_data_addr(fractol->img, &fractol->bpp, &fractol->size_line, &fractol->endian);
}

int		main_loop(t_fractol *fractol)
{
	int i;
	pthread_t	threads[fractol->thread_amount];
	t_fractol	fractol_copy[fractol->thread_amount];

	i = 0;
	while (i < fractol->thread_amount)
	{
		ft_memcpy(&fractol_copy[i], fractol, sizeof(t_fractol));
		fractol_copy[i].calc_info.start_y = i * (fractol->win_info.height /
			fractol->thread_amount);
		fractol_copy[i].calc_info.max_height = fractol_copy[i].calc_info.start_y
			+ (fractol->win_info.height / fractol->thread_amount);
		if (pthread_create(&threads[i], NULL, calculate, &fractol_copy[i]) != 0)
			ft_error("Couldnt create thread.");
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);// @Note: this has to be called like this after all the threads have been made
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
	return (0);
}

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
	int w;
	int h;
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
		if (key == 4) // zoom in
		{
			fractol->zoom += 1;
			zoom(fractol, x, y, 1);
		}
		else if (key == 5) // zoom out
		{
			fractol->zoom -= 1;
			zoom(fractol, x, y, -1);
		}
	}
	main_loop(fractol);
	return (0);
}

int main(int argc, char **argv)
{
	t_fractol *fractol;

	if (argc != 2)
		ft_usage(argv[0]);
	if (!(fractol = (t_fractol *)malloc(sizeof(t_fractol))))
		ft_error("Fractol struct couldn\'t be malloced");
	change_fractol_type(fractol, argv);
	init(fractol);
	main_loop(fractol);
	mlx_hook(fractol->win, 2, 0, input, fractol);
	if (fractol->toggle_julia)
		mlx_hook(fractol->win, 6, 0, julia_input, fractol);
	mlx_hook(fractol->win, 4, 0, mouse_input, fractol);
	mlx_loop(fractol->mlx);
	mlx_destroy_image(fractol->mlx, fractol->img);
	return (0);
}
