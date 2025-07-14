/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:11:16 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/04 15:43:37 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;

	if (n == 0)
		return (0);
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (*ss1 && *ss2 && n-- > 0)
	{
		if (*ss1 != *ss2)
			return (*ss1 - *ss2);
		ss1++;
		ss2++;
		if (n == 0)
			return (0);
	}
	return (*ss1 - *ss2);
}
