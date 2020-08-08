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
	ft_putstr(" [mandelbrot | julia | own]");
	ft_putstr("\n");
	exit(1);
}

void	change_fractol_type(t_fractol *fractol, char **argv)
{
	fractol->toggle_julia = 0;
	fractol->toggle_mandelbrot = 0;
	fractol->toggle_own = 0;
	if (ft_strcmp(argv[1], "julia") == 0)
		fractol->toggle_julia = 1;
	else if (ft_strcmp(argv[1], "mandelbrot") == 0)
		fractol->toggle_mandelbrot = 1;
	else if (ft_strcmp(argv[1], "own") == 0)
		fractol->toggle_own = 1;
	else
		ft_usage(argv[0]);
	ft_putstr("Fractol type set to ");
	ft_putstr(argv[1]);
	ft_putstr(".\n");
}

void	init(t_fractol *fractol)
{
	fractol->run = 1;
	fractol->win_info.width = 600;
	fractol->win_info.height = 400;
	fractol->win_info.title = "fractol"; // this could be moved in the the new window thing so we dont have to worry about this char *

	fractol->max_iteration = 50;

	// colors
	fractol->hue = 255;
	fractol->saturation = 255;
	fractol->color_value = 255;
	fractol->r = 255;
	fractol->g = 255;
	fractol->b = 255;

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

		fractol->zoom_re = 0.285f;
		fractol->zoom_im = 0.01f;

		// fractol->zoom_re = -0.7269f;
		// fractol->zoom_im = 0.1889f;

		// fractol->zoom_re = -0.8;
		// fractol->zoom_im = 0.156f;

		// fractol->zoom_re = -0.4f;
		// fractol->zoom_im = 0.6f;
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

	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, fractol->win_info.width, fractol->win_info.height, fractol->win_info.title);
	fractol->img = mlx_new_image(fractol->mlx, fractol->win_info.width, fractol->win_info.height);
	fractol->data = mlx_get_data_addr(fractol->img, &fractol->bpp, &fractol->size_line, &fractol->endian);
	ft_putstr("Initialized.\n");
}

int		main_loop(t_fractol *fractol)
{
	calculate(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
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
	mlx_loop_hook(fractol->mlx, main_loop, fractol);
	mlx_loop(fractol->mlx);
	mlx_destroy_image(fractol->mlx, fractol->img);
	return (0);
}
