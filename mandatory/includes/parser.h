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
} t_data;


void	print_and_exit(char *str);
void is_only_one_space(char *line);
int nb_args(char **args);
//void check_name_of_arg(char *line, char *arg);
char	*check_newline(int fd);
void check_nswe(int fd);
void	get_val_of_element(t_data *data, int fd);
void check_content_fc(t_data *data);


/* FUNCTIONS */
void freeing_list(char **list);
void freeing_data(t_data *data);
int	check_nwes(t_data *data, char *line);
//int	check_name(t_data *data, char *line);
void	get_data(t_data *data, int ac, char **av);
void check_content_map(t_data *data);

#endif