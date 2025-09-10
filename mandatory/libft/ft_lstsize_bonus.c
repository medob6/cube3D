/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:12:08 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/03 11:12:14 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*swp;
	int		i;

	i = 1;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		swp = lst->next;
		lst = swp;
		i++;
	}
	return (i);
}
