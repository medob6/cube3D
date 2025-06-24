/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:38:33 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/24 18:09:35 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
    t_data data;
    int i;
    
    i = 0;
    get_data(&data, ac, av);
    printf("E - \"%s\" \n",data.e_path);
    printf("W - \"%s\" \n",data.w_path);
    printf("S - \"%s\" \n",data.s_path);
    printf("N - \"%s\" \n",data.n_path);
    printf("\n\n\n\n");
    printf("F - \"%s\" \n",data.f_color);
    printf("C - \"%s\" \n",data.c_color);
    printf("\n\n\n\n");
    while (data.map[i])
    {    
        printf(">> \"%s\" \n",data.map[i]);
        i++;
    }
    freeing_data(&data);
}
