/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:56:53 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 16:25:16 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

# include <string.h>

typedef struct s_array
{
	void	**items;
	size_t	length;
	size_t	capacity;
}			t_array;

void		array_extend(t_array *arr);
void		array_push(t_array **list, void *new_item);
t_array		*creat_array(void);
void		array_clear(t_array *arr);

#endif