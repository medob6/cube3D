/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_door_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:32:35 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:33:12 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

static void	move_ray_forward(t_rayinfo *ray, int direction)
{
	ray->next.y -= (WALL_WIDTH / 2) * direction;
	ray->next.x -= (WALL_WIDTH / 2) / tan(ray->ray_ang) * direction;
}

static void	move_ray_back(t_rayinfo *ray, int direction)
{
	ray->next.y += (WALL_WIDTH / 2) * direction;
	ray->next.x += (WALL_WIDTH / 2) / tan(ray->ray_ang) * direction;
}

static double	process_door_hit(t_door_ctx *ctx)
{
	*(ctx->door) = (t_pair){ctx->px, ctx->py};
	*(ctx->wall_x) = ctx->ray->next.x;
	*(ctx->dir) = DOOR;
	if (get_door(ctx->px, ctx->py).frame == ctx->g->graphics[DOOR].frames - 1)
	{
		move_ray_back(ctx->ray, ctx->direction);
		return (-1);
	}
	return (get_dist(ctx->g->player.p, ctx->ray->next));
}

static double	process_map_door(t_door_ctx *ctx)
{
	char	tile;

	tile = ctx->g->data.map.arr[(int)ctx->ray->map_p.y][(int)ctx->ray->map_p.x];
	if (ft_strchr("DX", tile))
	{
		move_ray_back(ctx->ray, ctx->direction);
		*(ctx->door) = (t_pair){(int)(ctx->ray->next.x / WALL_WIDTH),
			(int)(ctx->ray->next.y / WALL_WIDTH)};
		*(ctx->wall_x) = ctx->ray->next.x;
		*(ctx->dir) = DOOR;
		return (get_dist(ctx->g->player.p, ctx->ray->next));
	}
	return (-1);
}

double	check_door_hhit(t_rayinfo *ray, double *wall_x, int *dir, t_pair *door)
{
	t_door_ctx	ctx;
	double		dist;

	ctx.g = get_game();
	ctx.px = (int)(ctx.g->player.p.x / WALL_WIDTH);
	ctx.py = (int)(ctx.g->player.p.y / WALL_WIDTH);
	ctx.direction = get_direction(ray->up);
	ctx.ray = ray;
	ctx.wall_x = wall_x;
	ctx.dir = dir;
	ctx.door = door;
	if (is_valid_door_position(ctx.px, ctx.py, ctx.ray))
	{
		move_ray_forward(ctx.ray, ctx.direction);
		if ((int)(ctx.ray->next.x / WALL_WIDTH) == ctx.px
			&& (int)(ctx.ray->next.y / WALL_WIDTH) == ctx.py)
		{
			dist = process_door_hit(&ctx);
			if (dist != -1)
				return (dist);
		}
		else
			move_ray_back(ctx.ray, ctx.direction);
	}
	return (process_map_door(&ctx));
}
