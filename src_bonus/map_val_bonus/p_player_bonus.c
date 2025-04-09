/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_player_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:24:22 by mfortuna          #+#    #+#             */
/*   Updated: 2025/03/12 10:49:46 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

bool	player_char(char c)
{
	if (c == 'S' || c == 'N' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

void	find_player(t_info *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (game->map->arr[y])
	{
		while (game->map->arr[y][x])
		{
			if (player_char(game->map->arr[y][x]))
			{
				if (game->player.x != 0)
					sanitize(game, "Multiple players\n", NULL);
				game->player.x = x + 0.4;
				game->player.y = y + 0.4;
				game->player.c = game->map->arr[y][x];
			}
			x++;
		}
		x = 0;
		y++;
	}
	if (game->player.x == 0)
		sanitize(game, "No player found\n", NULL);
}
