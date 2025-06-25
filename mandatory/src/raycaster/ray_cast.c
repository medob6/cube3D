#include "cub.h"

//? NOTES :
// the number of rays that we trace is the width of the window because ( win_width = the number of horizontal pixels on the window )
// FOV (fieled of view is a constent angel that the player see from) == 60
// the unit of angel between each ray is determened by the number of rays in this formule ( d(alpha) = FOV/ray_num )
// hieght of player is predefined as 32 units ,a units maybe a pixel or more depened on how is the hieght of wall,... read more

//! in game loop :
// cast_rays(game);
// draw_3d_view(game);


void	cast_rays(t_game *game)
{
	(void)game;
}