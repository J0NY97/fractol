/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoiner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 11:15:52 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/01 11:07:36 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

char	*ft_strjoiner(char *first, ...)
{
	char	*tmp;
	char	*str;
	char	*curr;
	va_list	ap;

	if (first == NULL)
		return (NULL);
	va_start(ap, first);
	str = ft_strdup(first);
	curr = va_arg(ap, char *);
	while (curr != NULL)
	{
		tmp = ft_strdup(str);
		free(str);
		str = ft_strjoin(tmp, curr);
		free(tmp);
		curr = va_arg(ap, char *);
	}
	va_end(ap);
	return (str);
}
