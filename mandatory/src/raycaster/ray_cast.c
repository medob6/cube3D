/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:30 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/12 15:39:27 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

#define WALL_HIGHT 64

bool	outside_map(int x, int y)
{
	if (x < 0 || x >= get_game()->data.map.map_w || y < 0
		|| y >= get_game()->data.map.map_h)
		return (true);
	return (false);
}

double	get_dist(t_point p, t_point next)
{
	return (hypot(next.x - p.x, next.y - p.y));
}
double	get_ray_angle(int ray, t_raycaster caster)
{
	return (caster.start_angle + ray * caster.angle_step);
}

void	get_steps_v(t_pair *step, bool left, double ray_ang)
{
	step->x = TILE_SIZE * (-left + !left);
	step->y = step->x * tan(ray_ang);
}

void	get_v_inter(t_point *next, bool left, double ray_ang)
{
	next->x = floor(get_game()->player.p.x / TILE_SIZE) * TILE_SIZE;
	if (!left)
		next->x += TILE_SIZE;
	next->y = get_game()->player.p.y + (next->x - get_game()->player.p.x)
		* tan(ray_ang);
}

static double	verti_dist(double ray_ang, double *wall_x, int *dir)
{
	t_point			map_p;
	t_point			next;
	t_pair			step;
	bool			left;
	const t_game	*g = get_game();

	left = cos(ray_ang) < 0;
	get_v_inter(&next, left, ray_ang);
	get_steps_v(&step, left, ray_ang);
	while (true)
	{
		map_p.x = ((next.x - 1) * (left) + next.x * (!left)) / TILE_SIZE;
		map_p.y = next.y / TILE_SIZE;
		if (outside_map(map_p.x, map_p.y))
			break ;
		if (g->data.map.arr[(int)map_p.y][(int)map_p.x] == '1')
			return (*wall_x = next.y, *dir = W_WALL * left + E_WALL * !left,
				get_dist(g->player.p, next));
		next.x += step.x;
		next.y += step.y;
	}
	return (INFINITY);
}

void	get_h_inter(t_point *next, bool facing_up, double ray_ang)
{
	next->y = floor(get_game()->player.p.y / TILE_SIZE) * TILE_SIZE;
	if (!facing_up)
		next->y += TILE_SIZE;
	next->x = get_game()->player.p.x + (next->y - get_game()->player.p.y)
		/ tan(ray_ang);
}

void	get_steps_h(t_pair *step, bool up, double ray_ang)
{
	step->y = TILE_SIZE * (-up + !up);
	step->x = step->y / tan(ray_ang);
}

static double	horiz_dist(double ray_ang, double *wall_x, int *dir)
{
	t_point			map_p;
	t_point			next;
	t_pair			step;
	bool			up;
	const t_game	*g = get_game();

	up = sin(ray_ang) < 0;
	get_h_inter(&next, up, ray_ang);
	get_steps_h(&step, up, ray_ang);
	while (true)
	{
		map_p.x = next.x / TILE_SIZE;
		map_p.y = ((next.y - 1) * (up) + next.y * (!up)) / TILE_SIZE;
		if (outside_map(map_p.x, map_p.y))
			break ;
		if (g->data.map.arr[(int)map_p.y][(int)map_p.x] == '1')
			return (*wall_x = next.x, *dir = N_WALL * up + S_WALL * !up,
				get_dist(g->player.p, next));
		next.x += step.x;
		next.y += step.y;
	}
	return (INFINITY);
}
unsigned int	get_slice_color(int x, int y, int dir, int section)
{
	if (section == 1)
		return (get_game()->data.ceiling_clr);
	else if (section == 2)
	{
		if (dir == -1)
			return (0x000000);
		if ((x >= 0 && x < get_game()->graphics[dir].w) && (y >= 0
				&& y < get_game()->graphics[dir].h))
			return (get_color(get_game()->graphics[dir], x, y));
	}
	else if (section == 3)
		return (get_game()->data.floor_clr);
	return (0xffffff);
}

void	draw_section(int start, int end, int num, t_sec_inf *section)
{
	int		i;
	t_image	tex;
	double	d_from_top;
	int		color;
	t_point	tex_p;

	i = start;
	if (section->sec.dir != -1)
		tex = get_game()->graphics[section->sec.dir];
	end = fmin(end, get_game()->win_h);
	while (i <= end)
	{
		if (num == 2 && section->sec.dir != -1)
		{
			d_from_top = i - start + section->tex_offset;
			tex_p.y = (d_from_top / section->sec.wall_h) * tex.h;
			tex_p.x = fmod(section->sec.wall_x, TILE_SIZE) / TILE_SIZE * tex.w;
		}
		color = get_slice_color(tex_p.x, tex_p.y, section->sec.dir, num);
		my_mlx_pixel_put(get_game()->display, section->win_x, i, color);
		i++;
	}
}

t_sec_inf	*init_section(int w_x, double wall_h, int x, t_graphic dir)
{
	t_sec_inf	*section;

	section = malloc(sizeof(t_sec_inf));
	section->sec.wall_h = wall_h;
	section->sec.dir = dir;
	section->sec.wall_x = x;
	section->win_x = w_x;
	section->tex_offset = 0;
	return (section);
}

bool	in_minimap_range(int w_x)
{
	int	minimap_r;
	int	minima_c;
	int	var;

	minimap_r = get_game()->win_h * MINIMAP_SCREEN_SCALE;
	minima_c = minimap_r * 1.2;
	var = minimap_r + minimap_r * ICON_SCALE * 2;
	if (w_x < minima_c + var && w_x > minima_c - var)
		return (true);
	return (false);
}

void	calculate_old_boundaries(int old_wh, int w_x, int *old_wt, int *old_wb)
{
	*old_wt = (get_game()->win_h / 2 - old_wh / 2 - 1) * (old_wh != 0);
	*old_wb = *old_wt + old_wh;
	if (old_wh == 0 || in_minimap_range(w_x))
		*old_wb = get_game()->win_h;
	if (*old_wt < 0)
		*old_wt = 0;
}

void	calculate_wall_boundaries(t_sec *slice, int w_x, int *wall_top,
		int *wall_bottom)
{
	*wall_top = get_game()->win_h / 2 - slice[w_x].wall_h / 2
		+ get_game()->player.p.z;
	*wall_bottom = *wall_top + slice[w_x].wall_h;
	if (*wall_bottom > get_game()->win_h)
		*wall_bottom = get_game()->win_h;
}

void	apply_texture_offset(t_sec_inf *section, int *wall_top)
{
	if (*wall_top < 0)
	{
		section->tex_offset = -*wall_top;
		*wall_top = 0;
	}
}

void	draw_ceiling_section(t_sec_inf *section, int old_wt, int wall_top)
{
	if (old_wt < wall_top)
		draw_section(old_wt, wall_top, 1, section);
}

void	draw_wall_section(t_sec_inf *section, int wall_top, int wall_bottom)
{
	draw_section(wall_top, wall_bottom, 2, section);
}

void	draw_floor_section(t_sec_inf *section, int wall_bottom, int old_wb)
{
	if (wall_bottom < old_wb)
		draw_section(wall_bottom, old_wb, 3, section);
}

void	draw_jump_floor_section(t_sec_inf *section, int wall_bottom, int old_wb)
{
	int	jump_floor_end;

	if (get_game()->player.jumping)
	{
		jump_floor_end = old_wb + get_game()->player.p.z + JUMP_SPEED + 5;
		draw_section(wall_bottom, jump_floor_end, 3, section);
	}
}

void	draw_wall_slice(int w_x, t_sec *slice, int old_wh)
{
	t_sec_inf	*section;
	int			wall_top;
	int			wall_bottom;
	int			old_wt;
	int			old_wb;

	calculate_old_boundaries(old_wh, w_x, &old_wt, &old_wb);
	calculate_wall_boundaries(slice, w_x, &wall_top, &wall_bottom);
	section = init_section(w_x, slice[w_x].wall_h, slice[w_x].wall_x,
			slice[w_x].dir);
	apply_texture_offset(section, &wall_top);
	draw_ceiling_section(section, old_wt, wall_top);
	draw_wall_section(section, wall_top, wall_bottom);
	draw_floor_section(section, wall_bottom, old_wb);
	draw_jump_floor_section(section, wall_bottom, old_wb);
	free(section);
}

bool	check_position(t_game *g)
{
	static double	new_x = -1;
	static double	new_y = -1;

	if (new_x == -1)
	{
		new_x = g->player.p.x;
		new_y = g->player.p.y;
		return (true);
	}
	if ((new_x != g->player.p.x || new_y != g->player.p.y))
	{
		new_x = g->player.p.x;
		new_y = g->player.p.y;
		return (true);
	}
	else
		return (false);
}

double	get_old_angel(t_game *g)
{
	static double	old_ang = -1;
	double			tmp;

	if (old_ang == -1)
	{
		old_ang = g->player.angle;
		return (g->player.angle);
	}
	else
	{
		tmp = old_ang;
		old_ang = g->player.angle;
		return (tmp);
	}
}

bool	check_in_range(int ray, int offset, int max_rays)
{
	if (offset > 0)
	{
		if (ray < max_rays - offset)
			return (true);
	}
	else if (offset < 0)
	{
		if (ray >= -offset)
			return (true);
	}
	return (false);
}

void	fill_line_inf(t_sec *line, int dir, double wall_x, double dist)
{
	line->dir = dir;
	line->wall_x = wall_x;
	line->raw_dist = dist;
}

double	closest_hit(double ang, t_sec *line)
{
	t_pair	distance;
	double	h_x;
	double	v_x;
	int		h_dir;
	int		v_dir;

	h_dir = -1;
	v_dir = -1;
	distance.x = horiz_dist(ang, &h_x, &h_dir);
	distance.y = verti_dist(ang, &v_x, &v_dir);
	if (distance.x < distance.y)
		fill_line_inf(line, h_dir, h_x, distance.x);
	else
		fill_line_inf(line, v_dir, v_x, distance.y);
	return (line->raw_dist * cos(normalize_angle(ang
				- get_game()->player.angle)));
}

void	init_frame_state(t_game *g, t_raycaster *c, t_frame_state *state)
{
	state->pos_changed = check_position(g);
	state->old_ang = get_old_angel(g);
	state->ray_offset = 0;
	if (state->old_ang != g->player.angle)
		state->ray_offset = (g->player.angle - state->old_ang) / c->angle_step;
	state->start_angle = g->player.angle - FOV_ANGLE / 2;
	state->proj_dist = (g->win_w / 2) / tan(FOV_ANGLE / 2);
}

double	calculate_ray_angle(t_frame_state *state, t_raycaster *c, int ray_index)
{
	return (normalize_angle(state->start_angle + ray_index * c->angle_step));
}

bool	can_reuse_ray(t_frame_state *state, t_raycaster *c, int ray_index)
{
	return (!state->pos_changed && check_in_range(ray_index, state->ray_offset,
			c->num_rays));
}

void	reuse_ray_data(t_raycaster *c, t_frame_state *state, int ray_index,
		double ray_ang)
{
	double	corrected_dist;

	c->lines[ray_index] = c->prev_lines[ray_index + state->ray_offset];
	corrected_dist = c->lines[ray_index].raw_dist * cos(normalize_angle(ray_ang
				- get_game()->player.angle));
	c->lines[ray_index].wall_h = (WALL_HIGHT / corrected_dist)
		* state->proj_dist;
}

void	cast_new_ray(t_raycaster *c, t_frame_state *state, int ray_index,
		double ray_ang)
{
	double	d;

	d = closest_hit(ray_ang, &c->lines[ray_index]);
	c->lines[ray_index].wall_h = (WALL_HIGHT / d) * state->proj_dist;
}

void	process_ray(t_raycaster *c, t_frame_state *state, int ray_index)
{
	double	ray_ang;

	ray_ang = calculate_ray_angle(state, c, ray_index);
	if (can_reuse_ray(state, c, ray_index))
		reuse_ray_data(c, state, ray_index, ray_ang);
	else
		cast_new_ray(c, state, ray_index, ray_ang);
}

double	get_previous_wall_height(t_raycaster *c, int ray_index)
{
	return (c->prev_lines[ray_index].wall_h);
}

static inline void	swap_buffers(t_raycaster *c)
{
	t_sec	*tmp;

	tmp = c->prev_lines;
	c->prev_lines = c->lines;
	c->lines = tmp;
}
void	process_all_rays(t_raycaster *c, t_frame_state *state)
{
	int		i;
	double	old_wh;

	i = -1;
	while (++i < c->num_rays)
	{
		old_wh = get_previous_wall_height(c, i);
		process_ray(c, state, i);
		draw_wall_slice(i, c->lines, old_wh);
	}
}

void	draw_3d_view(t_game *g, t_raycaster *c)
{
	t_frame_state	state;

	init_frame_state(g, c, &state);
	process_all_rays(c, &state);
	swap_buffers(c);
}

void	init_raycaster(t_raycaster *c)
{
	t_game	*g;

	g = get_game();
	c->num_rays = g->win_w;
	c->angle_step = FOV_ANGLE / c->num_rays;
	c->lines = malloc(sizeof(t_sec) * c->num_rays);
	c->prev_lines = malloc(sizeof(t_sec) * c->num_rays);
}
void	cast_rays(t_game *game)
{
	static bool			first = true;
	static t_raycaster	caster;

	if (first)
	{
		init_raycaster(&caster);
		first = false;
	}
	draw_3d_view(game, &caster);
}
