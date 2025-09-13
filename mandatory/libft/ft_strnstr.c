/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:11:29 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/04 14:52:40 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (!needle[k])
		return ((char *)&haystack[i]);
	while (len > i && haystack[i])
	{
		k = 0;
		while ((needle[k] == haystack[i + k]) && needle[k] && len > i + k)
			k++;
		if (!needle[k])
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
