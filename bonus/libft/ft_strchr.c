/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:08:12 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/22 15:35:22 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	a;
	int	i;

	a = 0;
	i = ft_strlen(s);
	while (i >= a)
	{
		if (s[a] == (char)c)
			return ((char *)(s + a));
		a++;
	}
	return (NULL);
}
