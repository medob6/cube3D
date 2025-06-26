/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:18:08 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/26 17:18:47 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

typedef struct s_data
{
    char *n_path;    
    char *s_path;    
    char *w_path;    
    char *e_path;    
    char *f_color;    
    char *c_color;    
    char **map;  
} t_fcub;


void	print_and_exit(char *str);
void is_only_one_space(char *line);
char	*check_newline(int fd);
void check_nswe(int fd);
void	get_val_of_element(t_fcub *fcub, int fd);
void check_content_fc(t_fcub *fcub);
int	add_val(t_fcub *fcub, char *line);
int	check_and_get_val(t_fcub *fcub, char **list);
void	sup_newline(t_fcub *fcub);
int	set_line_map(t_fcub *fcub, char *line, int size_of_map);
int	check_struct_fcub_val(t_fcub *fcub);
void	print_error_map_and_exit(t_fcub *fcub);
void	print_and_exit(char *str);
void	print_error_file_and_exit(void);
void	print_error_argument(void);
void	print_cub_rules(void);
int	count_line(char *str);
int	get_size_of_long_line(t_fcub *fcub);
int	check_nwes(t_fcub *fcub, char *line);
int count_list(char **list);
void print_error_argument();
void print_error_argument();
void	print_cub_rules();
void freeing_list(char **list);
void freeing_data(t_fcub *fcub);
int	check_nwes(t_fcub *fcub, char *line);
//int	check_name(t_fcub *fcub, char *line);
void	parse_and_get_data(t_fcub *fcub, int ac, char **av);
void check_content_map(t_fcub *fcub);

#endif