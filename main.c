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

void	change_fractol_type(t_fractol *fractol, char *type)
{
	fractol->toggle_julia = 0;
	fractol->toggle_mandelbrot = 0;
	fractol->toggle_own = 0;
	if (ft_strcmp(type, "julia") == 0)
		fractol->toggle_julia = 1;
	else if (ft_strcmp(type, "mandelbrot") == 0)
		fractol->toggle_mandelbrot = 1;
	else if (ft_strcmp(type, "own") == 0)
		fractol->toggle_own = 1;
	else
		ft_error("That fractol is not available.");
	ft_putstr("Fractol type set to ");
	ft_putstr(type);
	ft_putstr(".\n");
}

void	init(t_fractol *fractol)
{
	fractol->run = 1;
	fractol->win_info.width = 600;
	fractol->win_info.height = 400;
	fractol->win_info.title = ft_strdup("fractol");

	fractol->max_iteration = 50;
	fractol->opacity = 255;
	fractol->r = 255;
	fractol->g = 255;
	fractol->b = 255;

	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, fractol->win_info.width, fractol->win_info.height, fractol->win_info.title);
	ft_putstr("Initialized.\n");
}

// @Fix: figure out to which function these belong to
int		main_loop(t_fractol *fractol)
{
	// init img
	fractol->img = mlx_new_image(fractol->mlx, fractol->win_info.width, fractol->win_info.height);
	fractol->data = mlx_get_data_addr(fractol->img, &fractol->bpp, &fractol->size_line, &fractol->endian);
	// calculate
	calculate(fractol);
	// render img
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
	mlx_destroy_image(fractol->mlx, fractol->img);
	return (0);
}

int main(int argc, char **argv)
{
	t_fractol *fractol;

	if (argc != 2)
		ft_error("Fractol not given.");
	if (!(fractol = (t_fractol *)malloc(sizeof(t_fractol))))
		ft_error("Fractol struct couldn\'t be malloced");
	change_fractol_type(fractol, argv[1]);
	init(fractol);
	main_loop(fractol);
	mlx_hook(fractol->win, 2, 0, input, fractol);
	mlx_loop_hook(fractol->mlx, main_loop, fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
