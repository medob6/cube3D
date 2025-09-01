/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:59:53 by omben-ch          #+#    #+#             */
/*   Updated: 2024/11/03 18:03:16 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ls;
	t_list	*lnew;

	if (lst == NULL || !f)
		return ;
	ls = lst;
	while (ls->next != NULL)
	{
		lnew = ls->next;
		f(ls->content);
		ls = lnew;
	}
	f(ls->content);
}
