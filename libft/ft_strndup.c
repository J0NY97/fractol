/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:47:24 by jsalmi            #+#    #+#             */
/*   Updated: 2020/09/17 16:21:35 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t len)
{
	size_t	counter;
	char	*sdest;

	counter = 0;
	if (!(sdest = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s1[counter] != '\0' && counter < len)
	{
		sdest[counter] = s1[counter];
		counter++;
	}
	sdest[counter] = '\0';
	return (sdest);
}
