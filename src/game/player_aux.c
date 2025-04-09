/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:45:36 by alfreire          #+#    #+#             */
/*   Updated: 2025/03/12 10:49:17 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_dir(double *y, double *x, int a)
{
	double	old_x;

	old_x = *x;
	*x = *x * cos(a) - *y * sin(a);
	*y = old_x * sin(a) + *y * cos(a);
}

int	fix_angle(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

void	set_player_direction(t_info *game)
{
	if (game->player.c == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (game->player.c == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (game->player.c == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	else if (game->player.c == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
}

void	set_player_plane(t_info *game)
{
	if (game->player.c == 'N')
	{
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->player.c == 'S')
	{
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (game->player.c == 'E')
	{
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (game->player.c == 'W')
	{
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

void	step_side_y(t_ray *ray, double side_y)
{
	ray->step_y = 1;
	ray->side_y = side_y;
}
