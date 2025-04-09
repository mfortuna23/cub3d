/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_vision_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:50:08 by a                 #+#    #+#             */
/*   Updated: 2025/03/12 10:49:45 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	perform_dda(t_ray *ray, t_info *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (safe_get_cell(game, ray->map_y, ray->map_x) == '1')
			hit = 1;
	}
}

void	init_ray(t_ray *ray, t_info *game, double ray_dir_x, double ray_dir_y)
{
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->dir_x = ray_dir_x;
	ray->dir_y = ray_dir_y;
	ray->delta_x = fabs(1 / ray_dir_x);
	ray->delta_y = fabs(1 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_x;
	}
	if (ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.y - ray->map_y) * ray->delta_y;
	}
	else
		step_side_y(ray, (ray->map_y + 1.0 - game->player.y) * ray->delta_y);
}

double	calculate_distance(t_ray *ray, t_info *game)
{
	if (ray->side == 0)
	{
		return ((ray->map_x - game->player.x + (1 - ray->step_x) / 2) \
			/ ray->dir_x);
	}
	return ((ray->map_y - game->player.y + (1 - ray->step_y) / 2) / ray->dir_y);
}

void	cast_ray(t_info *game, int x, double ray_dir_x, double ray_dir_y)
{
	t_ray	ray;
	int		tex_id;

	init_ray(&ray, game, ray_dir_x, ray_dir_y);
	perform_dda(&ray, game);
	ray.distance = calculate_distance(&ray, game);
	tex_id = get_texture_id(&ray);
	draw_wall(game, x, &ray, tex_id);
}

void	render_frame(t_info *game)
{
	int		x;
	double	ray_offset;
	double	ray_dir_x;
	double	ray_dir_y;

	x = 0;
	while (x < WIDTH)
	{
		ray_offset = 2 * x / (double)WIDTH - 1;
		ray_dir_x = game->player.dir_x + game->player.plane_x * ray_offset;
		ray_dir_y = game->player.dir_y + game->player.plane_y * ray_offset;
		cast_ray(game, x, ray_dir_x, ray_dir_y);
		x++;
	}
}
