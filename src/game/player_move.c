/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:14:02 by mfortuna          #+#    #+#             */
/*   Updated: 2025/03/12 10:49:17 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_front(t_info *game)
{
	double	x;
	double	y;
	double	r_x;
	double	r_y;

	x = game->player.x + game->player.dir_x * 0.3;
	y = game->player.y + game->player.dir_y * 0.3;
	r_x = game->player.x + game->player.dir_x * 0.1;
	r_y = game->player.y + game->player.dir_y * 0.1;
	if (safe_get_cell(game, (int)game->player.y, (int)x) != '1')
		game->player.x = r_x;
	if (safe_get_cell(game, (int)y, (int)game->player.x) != '1')
		game->player.y = r_y;
}

void	move_back(t_info *game)
{
	double	x;
	double	y;
	double	r_x;
	double	r_y;

	x = game->player.x - game->player.dir_x * 0.3;
	y = game->player.y - game->player.dir_y * 0.3;
	r_x = game->player.x - game->player.dir_x * 0.1;
	r_y = game->player.y - game->player.dir_y * 0.1;
	if (safe_get_cell(game, (int)game->player.y, (int)x) != '1')
		game->player.x = r_x;
	if (safe_get_cell(game, (int)y, (int)game->player.x) != '1')
		game->player.y = r_y;
}

void	move_left(t_info *game)
{
	double	x;
	double	y;
	double	r_x;
	double	r_y;

	x = game->player.dir_y * 0.3;
	y = -game->player.dir_x * 0.3;
	r_x = game->player.dir_y * 0.1;
	r_y = -game->player.dir_x * 0.1;
	if (safe_get_cell(game, (int)(game->player.y + y), (int)game->player.x) \
		!= '1')
		game->player.y += r_y;
	if (safe_get_cell(game, (int)game->player.y, (int)(game->player.x + x)) \
		!= '1')
		game->player.x += r_x;
}

void	move_right(t_info *game)
{
	double	x;
	double	y;
	double	r_x;
	double	r_y;

	x = -game->player.dir_y * 0.3;
	y = game->player.dir_x * 0.3;
	r_x = -game->player.dir_y * 0.1;
	r_y = game->player.dir_x * 0.1;
	if (safe_get_cell(game, (int)(game->player.y + y), (int)game->player.x) \
		!= '1')
		game->player.y += r_y;
	if (safe_get_cell(game, (int)game->player.y, (int)(game->player.x + x)) \
		!= '1')
		game->player.x += r_x;
}

void	rotate(t_info *game, double dirx, double diry, bool rigth)
{
	double	pl_x;
	double	pl_y;

	pl_x = game->player.plane_x;
	pl_y = game->player.plane_y;
	if (rigth)
	{
		game->player.dir_x = dirx * cos(PR) - diry * sin(PR);
		game->player.dir_y = dirx * sin(PR) + diry * cos(PR);
		game->player.plane_x = pl_x * cos(PR) - pl_y * sin(PR);
		game->player.plane_y = pl_x * sin(PR) + pl_y * cos(PR);
		return ;
	}
	game->player.dir_x = dirx * cos(-PR) - diry * sin(-PR);
	game->player.dir_y = dirx * sin(-PR) + diry * cos(-PR);
	game->player.plane_x = pl_x * cos(-PR) - pl_y * sin(-PR);
	game->player.plane_y = pl_x * sin(-PR) + pl_y * cos(-PR);
}
