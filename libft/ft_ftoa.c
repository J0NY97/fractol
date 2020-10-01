/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:54:23 by jsalmi            #+#    #+#             */
/*   Updated: 2020/09/23 15:55:53 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char	*special_itoa(int nbr, int n)
{
	int		i;
	char	*str;

	str = ft_strnew(n);
	i = 0;
	while (nbr)
	{
		str[i++] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	while (i < n)
		str[i++] = '0';
	ft_reverse(str);
	return (str);
}

char	*ft_ftoa(double d, int precision)
{
	int		i;
	int		ipart;
	double	fpart;
	char	*str;
	char	*temp;

	ipart = (int)d;
	fpart = d - (double)ipart;
	fpart = fpart < 0 ? -fpart : fpart;
	temp = ft_itoa(ipart);
	i = ft_strlen(temp);
	str = ft_strnew(i + precision + 1);
	ft_strcpy(str, temp);
	if (precision > 0)
	{
		str[i] = '.';
		ft_strdel(&temp);
		temp = special_itoa(fpart * ft_pow(10, precision), precision);
		ft_strncpy(str + i + 1, temp, precision);
	}
	ft_strdel(&temp);
	return (str);
}
