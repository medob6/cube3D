/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:15:14 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/01 15:16:37 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	char	*strim;
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (check(s1[i], set) && s1[i])
		i++;
	size = ft_strlen(s1);
	if (i == (int)size)
		return (ft_strdup(""));
	j = size - 1;
	while (check(s1[j], set) && s1[j])
		j--;
	strim = (char *)malloc(j - i + 2);
	if (strim == NULL)
		return (NULL);
	ft_strlcpy(strim, s1 + i, j - i + 2);
	return (strim);
}
