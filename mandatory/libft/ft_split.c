/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:07:59 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/16 14:36:39 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	freeing(char **s, int i)
{
	while (i >= 0)
		free(s[i--]);
	free(s);
}

static int	check(char s, char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (s == c[i])
			return (1);
		i++;
	}
	return (0);
}

static int	cw(char const *s, char *c)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	j = 1;
	while (s[i])
	{
		if (check(s[i], c) && j == 0)
			j = 1;
		if (check(s[i], c) == 0 && j == 1)
		{
			j = 0;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*alocation_str(char const *s, char *c, int *j)
{
	int		i;
	char	*p;
	int		start;

	p = NULL;
	i = 0;
	while (s[*j] && check(s[*j], c))
		(*j)++;
	start = *j;
	while (s[*j] && check(s[*j], c) == 0)
	{
		(*j)++;
		i++;
	}
	p = ft_substr(s, start, i);
	return (p);
}

char	**ft_split(char const *s, char *c)
{
	char	**sp;
	int		w;
	int		j;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	w = cw(s, c);
	sp = malloc((w + 1) * sizeof(char *));
	if (sp == NULL)
		return (NULL);
	j = 0;
	while (i < w)
	{
		sp[i] = alocation_str(s, c, &j);
		if (sp[i] == NULL)
		{
			freeing(sp, i);
			return (NULL);
		}
		i++;
	}
	sp[i] = NULL;
	return (sp);
}
