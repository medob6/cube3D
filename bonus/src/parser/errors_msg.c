/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:44:04 by omben-ch          #+#    #+#             */
/*   Updated: 2025/07/31 10:04:19 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	print_cub_rules(void)
{
	ft_putstr_fd(BOLD GREEN "=== .cub FILE RULES ===\n" RESET, 1);
	ft_putstr_fd(BLUE "1. TEXTURES:\n" RESET, 1);
	ft_putstr_fd("   NO ./path_to_north_texture\n", 1);
	ft_putstr_fd("   SO ./path_to_south_texture\n", 1);
	ft_putstr_fd("   WE ./path_to_west_texture\n", 1);
	ft_putstr_fd("   EA ./path_to_east_texture\n\n", 1);
	ft_putstr_fd(BLUE "2. COLORS:\n" RESET, 1);
	ft_putstr_fd("   F R,G,B   (Floor color)\n", 1);
	ft_putstr_fd("   C R,G,B   (Ceiling color)\n\n", 1);
	ft_putstr_fd(BLUE "3. MAP:\n" RESET, 1);
	ft_putstr_fd("   - Must use only: '0', '1', 'N', 'S', 'E', 'W', ' '\n", 1);
	ft_putstr_fd("   - Must be closed (surrounded by walls)\n", 1);
	ft_putstr_fd("   - Must have only one player start (N/S/E/W)\n", 1);
	ft_putstr_fd("   - Map must be the last element in the .cub file\n", 1);
	ft_putstr_fd(BLUE "4. FORMATTING:\n" RESET, 1);
	ft_putstr_fd("   - Elements (textures/colors) can appear in any order\n",
		1);
	ft_putstr_fd("   - Each element must appear only once\n", 1);
	ft_putstr_fd("   - Empty lines are allowed between elements\n\n", 1);
	ft_putstr_fd(BOLD GREEN "==========================\n" RESET, 1);
}

void	print_error_argument(void)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(RED BOLD "❌ Error Argument: " RESET, 2);
	ft_putstr_fd("invalid .cub configuration.\n", 2);
	ft_putstr_fd("➡️  Please run ", 2);
	ft_putstr_fd(BOLD "./cub --rules" RESET, 2);
	ft_putstr_fd(" to view the correct structure of a .cub file\n", 2);
}

void	print_error_file_and_exit(void)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(RED BOLD "❌ Error File Name: " RESET, 2);
	ft_putstr_fd("< File Name >", 2);
	ft_putstr_fd(BOLD ".cub\n" RESET, 2);
	cleanup(1);
}

void	print_and_exit(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	cleanup(1);
}

void	print_error_map_and_exit(t_fcub *fcub)
{
	print_error_argument();
	freeing_data(fcub);
	cleanup(1);
}
