/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:38:33 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/26 14:53:23 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"



int	main(int ac, char **av)
{
	t_fcub	fcub;
	int		i;

	i = 0;
	parse_and_get_data(&fcub, ac, av);
	printf("E - \"%s\" \n", fcub.e_path);
	printf("W - \"%s\" \n", fcub.w_path);
	printf("S - \"%s\" \n", fcub.s_path);
	printf("N - \"%s\" \n", fcub.n_path);
	printf("\n\n\n\n");
	printf("F - \"%s\" \n", fcub.f_color);
	printf("C - \"%s\" \n", fcub.c_color);
	printf("\n\n\n\n");
	while (fcub.map[i])
	{
		printf(">> \"%s\" \n", fcub.map[i]);
		i++;
	}
	freeing_data(&fcub);
}
