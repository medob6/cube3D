/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:10:30 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/01 15:10:37 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	t;
	size_t	d;

	if (size == 0 && dst == NULL)
		return (ft_strlen(src));
	if (ft_strlen(dst) >= size)
		return (size + ft_strlen(src));
	t = ft_strlen(dst) + ft_strlen(src);
	d = ft_strlen(dst);
	dst = dst + d;
	size = size - d;
	while (*src != '\0' && size-- > 1)
		*(dst++) = *(src++);
	*(dst) = '\0';
	return (t);
}
