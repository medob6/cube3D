#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <stdlib.h>
# include <math.h>

typedef struct s_raycaster
{
	int     num_rays;
	double  fov;
	double  angle_step;
	double  start_angle; 
	double *distances;
}	t_raycaster;



#endif