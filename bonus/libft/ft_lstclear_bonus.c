/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:18:22 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/03 16:18:23 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lnext;
	t_list	*ls;

	if (lst == NULL || *lst == NULL || !del)
		return ;
	ls = *lst;
	while (ls != NULL)
	{
		lnext = ls->next;
		del(ls->content);
		free(ls);
		ls = lnext;
	}
	*lst = NULL;
}
