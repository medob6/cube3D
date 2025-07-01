#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub.h"
typedef struct s_raycaster
{
	int			num_rays;
	double		angle_step;
	double		start_angle;
	double		*distances;
}				t_raycaster;

typedef struct s_sec_inf
{
	int			win_x;
	int			wall_x;
	int			wall_h;
	int	wall;

}				t_sec_inf;

void			cast_rays(t_game *game);
void			draw_3d_view(t_game *game, t_raycaster *caster);

#endif