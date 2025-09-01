/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:00:29 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/03 12:00:34 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ls;
	t_list	*swp;

	if (*lst == NULL)
	{
		*(lst) = new;
		return ;
	}
	ls = *lst;
	while (ls->next != NULL)
	{
		swp = ls->next;
		ls = swp;
	}
	ls->next = new;
}
