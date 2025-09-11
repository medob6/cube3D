/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:29:57 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/11 13:19:28 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void get_player_positon(t_fcub *fcub, int *position_player)
{
    int x;
    int y;

    x = 0;
    while (fcub->map[x])
    {
        y = 0;
        while (fcub->map[x][y])
        {
            if (ft_strchr( "NEWS" , fcub->map[x][y]))
            {
                position_player[0] = x;
                position_player[1] = y;
                return ;
            }
            y++;
        }
        x++;
    }
}

void free_map_flood_fill(char **map)
{
    int i;

    i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map[i]);
    free(map);
}

int get_size_lines_of_map(t_fcub *fcub)
{
    int x;
    x = 0;
    while (fcub->map[x])
    {
        x++;
    }
    return (x);
}

void dup_map(t_fcub *fcub, char **map)
{
    int x;

    x = 0;
    while (fcub->map[x])
    {
        map[x] = ft_strdup(fcub->map[x]);
        if (!map[x])
        {
            free_map_flood_fill(map);
            freeing_data(fcub);        
            print_and_exit("error malloc\n");
        }
        x++;
    }
    map[x] = NULL;
}

int check_news(int x, int y, int *steps_to_exit,char **map)
{
    if (map[x][y] == '1' || map[x][y] ==  'F')
        return (0);
    if (map[x][y] == 'X')
    {
        (*steps_to_exit)++;
        return (1);
    }
    if (map[x][y] == '0' || map[x][y] == 'D')
    {
        if (map[x][y] == '0')
        {
            (*steps_to_exit)++;
        }
        map[x][y] = 'F';
        if (check_news(x - 1 , y, steps_to_exit,map) || check_news(x , y + 1 , steps_to_exit, map) || check_news(x , y - 1, steps_to_exit, map) || check_news(x + 1, y , steps_to_exit, map))
            return (1);
        else
            (*steps_to_exit)--;
    }
    return (0);
}

int check_exit(int x, int y, int *steps_to_exit,char **map)
{
    map[x][y] = 'F';
    if (check_news(x - 1 , y, steps_to_exit, map) || check_news(x , y + 1, steps_to_exit, map) || check_news(x , y - 1, steps_to_exit, map) || check_news(x + 1, y , steps_to_exit, map))
        return (1);
    return (0);
}


void flood_fill(t_fcub *fcub, int rows, int colums)
{
    int position_player[2];
    char **map;
    char **l;

    fcub->steps_to_exit = 0;
    map = malloc(rows * sizeof(char *));
    if (!map)
    {
        freeing_data(fcub);        
        print_and_exit("error malloc\n");
    }
    get_player_positon(fcub, position_player);
    dup_map(fcub, map);
    if (check_exit(position_player[0],position_player[1],&fcub->steps_to_exit ,map))
    {
        printf("yes : the result is : %d \n", fcub->steps_to_exit);
        free_map_flood_fill(map);
    }
    else
    {
        printf("no: the result is : %d \n", fcub->steps_to_exit);
        free_map_flood_fill(map);
        freeing_data(fcub);        
        print_and_exit("");
    }
}
