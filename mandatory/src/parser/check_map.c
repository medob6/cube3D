/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:27:03 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/15 15:46:39 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void check_element(char *cub_file)
{
    int fd;
    
    fd = open(cub_file, O_RDONLY);
    if (fd == -1)
        print_error_map(strerror(errno));
    
}
