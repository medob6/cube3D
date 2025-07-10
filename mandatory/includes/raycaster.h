#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub.h"

typedef struct s_sec
{
	double	wall_h;
	double	wall_x;
	double raw_dist; // Add this field to store uncorrected distance

	int		dir;
}			t_sec;

typedef struct s_raycaster
{
	int		num_rays;
	double	angle_step;
	t_sec	*lines;
	t_sec	*prev_lines;
	double	start_angle;
}			t_raycaster;

typedef struct s_sec_inf
{
	t_sec	sec;
	int		win_x;
	int		tex_offset;
}			t_sec_inf;

void		cast_rays(t_game *game);
void		draw_3d_view(t_game *game, t_raycaster *caster);

#endif