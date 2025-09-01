/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:35:04 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/01 15:19:27 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long int n)
{
	int	i;

	i = 0;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	if (n <= -1 && -9 <= n)
		i++;
	return (i + 1);
}

static int	ft_mul_len(int i, long int n)
{
	int	nb;

	nb = 1;
	if (n < 0)
		i--;
	i--;
	while (i--)
		nb = nb * 10;
	return (nb);
}

static char	*ft_conv_i_to_s(char *str, long int n, int nb, int size)
{
	int	i;

	i = 0;
	if (n >= -9 && n < 0)
	{
		str[i++] = '-';
		str[i++] = 48 + (-(n / nb));
	}
	while (size > i)
	{
		if (n / nb < 0)
		{
			str[i++] = '-';
			str[i++] = 48 + (-(n / nb));
			n = -n % nb;
			nb = nb / 10;
		}
		str[i++] = 48 + (n / nb);
		n = n % nb;
		nb = nb / 10;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			size;
	int			nb;
	char		p1[2];
	long int	j;

	j = (long int)n;
	if (j >= 0 && j <= 9)
	{
		p1[0] = 48 + j;
		p1[1] = '\0';
		return (ft_strdup(p1));
	}
	size = ft_intlen(j);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	nb = ft_mul_len(size, j);
	str = ft_conv_i_to_s(str, j, nb, size);
	return (str);
}
