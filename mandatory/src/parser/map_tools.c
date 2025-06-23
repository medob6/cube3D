/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:09:52 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/23 07:51:43 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// t_map	*map_lstnew(char *content)
// {
// 	t_map	*l;

// 	l = (t_map *)ft_malloc(sizeof(t_map), 1);
// 	if (!l)
// 		return (NULL);
// 	l->prev = NULL;
// 	l->line = content;
// 	l->next = NULL;
// 	return (l);
// }

// void	map_lstadd(t_map **lst, t_map *new)
// {
// 	if (!new)
// 		return ;
// 	if (!(*lst))
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	(*lst)->next = new;
// 	(*lst)->next->prev = *lst;
// }

// t_map	*list_map(char *line, int fd)
// {
// 	t_map	*h_map;
// 	t_map	*l_map;
// 	t_map	*tmp;

// 	h_map = map_lstnew(line);
// 	l_map = h_map;
// 	while (1)
// 	{
//         line = get_next_line(fd);
//         if (!line)
//             break;
// 	    tmp = l_map;
// 	    l_map = map_lstnew(line);
// 		map_lstadd(&tmp, l_map);
// 	}
// 	return (h_map);
// }
