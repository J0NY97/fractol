/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 11:11:13 by jsalmi            #+#    #+#             */
/*   Updated: 2020/09/23 15:37:18 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	val(int c)
{
	if (c >= 0 && c <= 9)
		return ('0' + c);
	else
		return ('A' - 10 + c);
}

int		ft_nbrlen_base(size_t nbr, int base)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		len++;
	while (nbr != 0)
	{
		nbr = nbr / base;
		len++;
	}
	return (len);
}

char	*ft_itoa_base(size_t nbr, int base)
{
	char	*str;
	int		len;
	int		neg;

	neg = nbr < 0 ? -1 : 1;
	nbr *= neg;
	len = ft_nbrlen_base(nbr, base);
	len += neg == -1 ? 1 : 0;
	str = ft_strnew(len);
	if (neg == -1)
		str[0] = '-';
	else if (nbr == 0)
		str[0] = '0';
	while (nbr != 0)
	{
		len--;
		str[len] = val(nbr % base);
		nbr = nbr / base;
	}
	return (str);
}
