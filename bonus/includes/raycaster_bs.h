/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:22:34 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/18 09:29:22 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_BS_H
# define RAYCASTER_BS_H

# include "cub_bs.h"

typedef struct s_door_inf
{
	double		*wall_x;
	int			*dir;
	double		ray_ang;
	bool		left;
	bool		up;
}				t_door_inf;

typedef struct s_doorhit
{
	double		*wall_x;
	int			*dir;
	int			*door_x;
	int			*door_y;
	bool		left;
}				t_doorhit;

typedef struct s_hit_data
{
	double		x;
	double		y;
	int			h_dir;
	int			v_dir;
	double		h_x;
	double		v_x;
}				t_hit_data;

typedef struct s_draw_bounds
{
	int			wall_top;
	int			wall_bottom;
	int			old_wt;
	int			old_wb;
}				t_draw_bounds;

typedef struct s_sec_params
{
	double		wall_h;
	int			wall_x;
	t_graphic	dir;
	t_door		door;
}				t_sec_params;

typedef struct s_rayinfo
{
	t_point		next;
	t_point		map_p;
	double		ray_ang;
	bool		left;
	bool		up;
	double		result;
}				t_rayinfo;

typedef struct s_sec
{
	double		wall_h;
	double		wall_x;
	double		raw_dist;
	int			dir;
	t_door		door;
	int			n;
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

typedef struct s_wall_inf
{
	t_image		tex;
	t_point		tex_p;
	int			raw_dist;
	double		h_factor;
	int			offset;
	int			win_h;
}				t_wall_inf;

typedef struct s_frame_state
{
	bool		pos_changed;
	int			ray_offset;
	double		old_ang;
	double		start_angle;
	double		proj_dist;
}				t_frame_state;

typedef struct s_vray
{
	t_pair		step;
	t_point		map_p;
	t_point		next;
	t_rayinfo	ray;
	t_doorhit	h;
	int			door_x;
	int			door_y;
}				t_vray;

typedef struct s_hray
{
	t_pair		step;
	t_point		map_p;
	t_point		next;
	t_rayinfo	ray;
	t_doorhit	h;
	int			door_x;
	int			door_y;
}				t_hray;

typedef struct s_floorcast
{
	t_game		*game;
	t_image		floor_tex;
	t_image		sky_tex;
	int			winw;
	int			winh;
	double		raydirx0;
	double		raydiry0;
	double		raydirx1;
	double		raydiry1;
	double		eyeheight;
	double		mid;
	int			win_x;
}				t_floorcast;

typedef struct s_door_ctx
{
	t_rayinfo	*ray;
	double		*wall_x;
	int			*dir;
	t_pair		*door;
	int			px;
	int			py;
	int			direction;
	t_game		*g;
}				t_door_ctx;

bool			is_wall_hit(t_point map_p);
t_rayinfo		init_vertical_ray(t_point next, t_point map_p, double ray_ang,
					bool left);
void			draw_3d_view(t_game *game, t_raycaster *caster);
t_sec_inf		*init_section(int w_x, t_sec_params p);
unsigned int	get_slice_color(int x, int y, int dir, int section);
void			draw_section(int start, int end, int num, t_sec_inf *section);
bool			in_minimap_range(int w_x);
void			calculate_old_boundaries(int old_wh, int w_x, int *old_wt,
					int *old_wb);
void			process_ray(t_raycaster *c, t_frame_state *state,
					int ray_index);
double			verti_dist(double ray_ang, double *wall_x, int *dir,
					t_door *next_door);
void			init_raycaster(t_raycaster *c);
void			get_steps_h(t_pair *step, bool up, double ray_ang);
double			horiz_dist(double ray_ang, double *wall_x, int *dir,
					t_door *next_door);
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
bool			is_valid_door_position(int px, int py, t_rayinfo *ray);
void			get_h_inter(t_point *next, bool facing_up, double ray_ang);
int				get_direction(int up);
double			check_door_hhit(t_rayinfo *ray, double *wall_x, int *dir,
					t_pair *door);
bool			is_player_on_vertical_door(t_pair p, t_game *g);
void			apply_door_offset(t_rayinfo *ray);
void			get_v_inter(t_point *next, bool left, double ray_ang);
void			get_steps_v(t_pair *step, bool left, double ray_ang);

t_floorcast		init_floorcast(t_sec_inf *section);
bool			in_minimap_range(int w_x);
void			initialize_wall_inf(t_wall_inf *inf, t_sec_inf *section,
					int start);
int				apply_shading(int color, double dist);
void			display_scean(t_game *game);
int				get_tex_color(t_floorcast *fc, t_point world_p, double rowDist,
					int num);
void			get_world_coords(t_floorcast *fc, double rowDist,
					double *worldx, double *worldy);
void			update_next_point(t_point *next, t_pair *step);
double			check_door_vhit(t_rayinfo *ray, double *wall_x, int *dir,
					t_pair *door);
bool			is_valid_vdoor_position(int px, int py, t_rayinfo *ray);

#endif
