/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:09:41 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/15 15:56:21 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ds;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	ds = malloc((len + 1) * sizeof(char));
	if (ds == NULL)
		return (NULL);
	ft_strlcpy(ds, s1, len + 1);
	return (ds);
}
