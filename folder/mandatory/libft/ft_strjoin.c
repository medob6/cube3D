/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:10:20 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/01 15:10:24 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*s;
	int		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = (char *)malloc(size * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (*(s1))
		s[i++] = *(s1++);
	while (*(s2))
		s[i++] = *(s2++);
	s[i] = '\0';
	return (s);
}
