/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nwse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:36:37 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/22 16:37:41 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void check_nswe(int fd)
// {
//     char **list_name;
//     char *line;
//     int i;

//     i = -1;
//     list_name = (char **)malloc(5 * sizeof(char *));
//     if (!list_name)
//         print_error_map("nswe- error malloc");
//     list_name[0] = "NO";
//     list_name[1] = "SO";
//     list_name[2] = "WE";
//     list_name[3] = "EA";
//     list_name[4] = NULL;
//     while (++i < 4)
//     {
//         line = get_next_line(fd);
//         if (!line)
//         {
//             free(line);
//             print_error_map("1- error");
//         }
//         check_name_of_arg(line, list_name[i]);
//         free(line);
//     }
//     free(list_name);
// }
