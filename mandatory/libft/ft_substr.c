/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:18:11 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/01 15:15:41 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*sub;

	sub = NULL;
	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (size <= start || size - start == 0 || len == 0)
		return (ft_strdup(""));
	if (size - start < len)
	{
		sub = (char *)malloc(size - start + 1);
		if (sub == NULL)
			return (NULL);
		ft_strlcpy(sub, &s[start], size - start + 1);
	}
	else
	{
		sub = (char *)malloc(len + 1);
		if (sub == NULL)
			return (NULL);
		ft_strlcpy(sub, (s + start), len + 1);
	}
	return (sub);
}
