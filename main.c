/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 13:02:53 by jsalmi            #+#    #+#             */
/*   Updated: 2020/10/01 11:51:12 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	init(t_fractol *fractol)
{
	if (fractol->toggle_mandelbrot)
		default_mandelbrot(fractol);
	else if (fractol->toggle_julia)
		default_julia(fractol);
	else if (fractol->toggle_own)
		default_own(fractol);
	else if (fractol->toggle_newton)
		default_newton(fractol);
	window_init(fractol);
}

int		main_loop(t_fractol *fractol)
{
	int			i;
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
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
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
