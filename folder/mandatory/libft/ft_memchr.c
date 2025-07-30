/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:05:36 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/01 15:05:37 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				a;
	unsigned char	*sa;

	sa = (unsigned char *)s;
	a = 0;
	while (n-- > 0)
	{
		if (sa[a] == (unsigned char)c)
			return ((void *)&sa[a]);
		a++;
	}
	return (NULL);
}
