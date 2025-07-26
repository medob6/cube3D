/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:22:34 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/12 19:02:45 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub.h"

typedef struct s_sec
{
	double		wall_h;
	double		wall_x;
	double		raw_dist;

	int			dir;
}				t_sec;

typedef struct s_raycaster
{
	int			num_rays;
	double		angle_step;
	t_sec		*lines;
	t_sec		*prev_lines;
	double		start_angle;
}				t_raycaster;

typedef struct s_sec_inf
{
	t_sec		sec;
	int			win_x;
	int			tex_offset;
}				t_sec_inf;

typedef struct s_frame_state
{
	bool		pos_changed;
	int			ray_offset;
	double		old_ang;
	double		start_angle;
	double		proj_dist;
}				t_frame_state;

void			display_scean(t_game *game);
void			draw_3d_view(t_game *game, t_raycaster *caster);
t_sec_inf		*init_section(int w_x, double wall_h, int x, t_graphic dir);
unsigned int	get_slice_color(int x, int y, int dir, int section);
void			draw_section(int start, int end, int num, t_sec_inf *section);
bool			in_minimap_range(int w_x);
void			calculate_old_boundaries(int old_wh, int w_x, int *old_wt,
					int *old_wb);
void			process_ray(t_raycaster *c, t_frame_state *state,
					int ray_index);
double			verti_dist(double ray_ang, double *wall_x, int *dir);
void			init_raycaster(t_raycaster *c);
void			get_steps_h(t_pair *step, bool up, double ray_ang);
double			horiz_dist(double ray_ang, double *wall_x, int *dir);
void			update_player(t_game *game);
double			pow_2(double n);
double			get_old_angel(t_game *g);
bool			check_position(t_game *g);
double			get_ray_angle(int ray, t_raycaster caster);
double			get_dist(t_point p, t_point next);
bool			outside_map(int x, int y);
void			cast_new_ray(t_raycaster *c, t_frame_state *state,
					int ray_index, double ray_ang);
void			reuse_ray_data(t_raycaster *c, t_frame_state *state,
					int ray_index, double ray_ang);
bool			can_reuse_ray(t_frame_state *state, t_raycaster *c,
					int ray_index);
double			calculate_ray_angle(t_frame_state *state, t_raycaster *c,
					int ray_index);
void			init_frame_state(t_game *g, t_raycaster *c,
					t_frame_state *state);
double			closest_hit(double ang, t_sec *line);
void			fill_line_inf(t_sec *line, int dir, double wall_x, double dist);
bool			check_in_range(int ray, int offset, int max_rays);
void			draw_wall_slice(int w_x, t_sec *slice, int old_wh);
void			draw_jump_floor_section(t_sec_inf *section, int wall_bottom,
					int old_wb);

void			calculate_wall_boundaries(t_sec *slice, int w_x, int *wall_top,
					int *wall_bottom);
void			apply_texture_offset(t_sec_inf *section, int *wall_top);
void			draw_ceiling_section(t_sec_inf *section, int old_wt,
					int wall_top);
void			draw_wall_section(t_sec_inf *section, int wall_top,
					int wall_bottom);
void			draw_floor_section(t_sec_inf *section, int wall_bottom,
					int old_wb);
int				get_rgb(t_fcub *fcub, char *color);
void			handle_exit(t_game *game);

#endif