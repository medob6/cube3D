#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub.h"
typedef struct s_raycaster
{
	int     num_rays;
	double  fov;
	double  angle_step;
	double  start_angle; 
	double *distances;
}	t_raycaster;

void cast_rays(t_game *game);
void draw_3d_view(t_game *game, t_raycaster *caster);

#endif