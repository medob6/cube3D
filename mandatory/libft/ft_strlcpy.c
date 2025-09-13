/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:10:47 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/01 15:10:52 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*sr;

	sr = src;
	if (size == 0)
		return (ft_strlen(src));
	else if (!src)
		return (ft_strlen(src));
	else
	{
		size--;
		while (size-- > 0 && *sr != '\0')
			*(dst++) = *(sr++);
		*(dst) = '\0';
	}
	return (ft_strlen(src));
}
