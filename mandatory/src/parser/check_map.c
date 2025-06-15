/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:27:03 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/15 18:56:29 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void check_nswe_data(char *line, char *arg)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (line[i] == arg[0] && line[i + 1] == arg[1] && line[i + 2] == ' ')
        i+=3;
    else if (line[i] == arg[0] && line[i + 2] == ' ')
        i+=2;
    else
    {
        free(line);
        print_error_map("nswe- error name");
    }
    if (!line[i] || line[i] == ' ')
    {
        free(line);
        print_error_map("nswe- error path");
    }
}
void check_newline(int fd)
{
    char *line;

    line = get_next_line(fd);
    if (!line || line[0] != '\n')
    {
        free(line);
        print_error_map("1- error");
    }
    else
        free(line);
        
}
void check_nswe(fd)
{
    char **list_name;
    char *line;
    int i;

    i = 0;
    list_name = (char **)malloc(5 * sizeof(char *));
    if (!list_name)
        print_error_map("nswe- error malloc");
    list_name[0] = "NO";
    list_name[1] = "SO";
    list_name[2] = "WE";
    list_name[3] = "EA";
    list_name[4] = NULL;
    while (i < 5)
    {
        line = get_next_line(fd);
        if (!line)
        {
            free(line);
            print_error_map("1- error");
        }
        check_nswe_data(line, list_name[i]);
        free(line);
        i++;
    }
}

void check_element(char *file_name)
{
    //char **file_data;
    int fd;
    
    fd = open(file_name, O_RDONLY);
    if (fd == -1)
        print_error_map(strerror(errno));
    check_nswe(fd);
    check_newline(fd);
    // check_fc();
    // check_newline(fd);
    // check_map();
}
