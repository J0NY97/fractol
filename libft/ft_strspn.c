/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:54:05 by exam              #+#    #+#             */
/*   Updated: 2019/11/12 15:09:11 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	charset_i;
	size_t	str_i;
	int		found;

	str_i = 0;
	found = 0;
	while (s[str_i])
	{
		charset_i = 0;
		while (accept[charset_i])
		{
			if (accept[charset_i] == s[str_i])
				found = 1;
			charset_i++;
		}
		if (!found)
			return (str_i);
		found = 0;
		str_i++;
	}
	return (str_i);
}
