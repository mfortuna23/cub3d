/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:53:43 by alfreire          #+#    #+#             */
/*   Updated: 2025/03/12 10:49:18 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
orientation

The map must be closed/surrounded by walls, if not the program must return
an error.

EXCEPT FOR THE MAP CONTENT, each type of element can be separated by one or
more empty line(s).

EXCEPT FOR THE MAP CONTENT which always has to be the last, each type of
element can be set in any order in the file.

EXCEPT FOR THE MAP, each type of information from an element can be separated
by one or more space(s).*/

void	valid_characters(t_info *game)
{
	int		y;
	int		x;
	int		c;
	char	**map;

	y = 0;
	x = 0;
	map = game->map->arr;
	while (map[y])
	{
		while (map[y][x])
		{
			c = map[y][x];
			if (c != '1' && c != '0' && c != ' ' && c != 'N' && c != 'S' \
				&& c != 'E' && c != 'W')
				sanitize(game, "Invalid char found\n", NULL);
			x++;
		}
		x = 0;
		y++;
	}
}

static void	check_neighbor_cell(t_info *game, int y, int x)
{
	char	**map;
	int		row_len;

	map = game->map->arr;
	if (!map[y])
		sanitize(game, "Map not surrounded by walls\n", NULL);
	row_len = ft_strlen(map[y]);
	if (row_len == 0)
		sanitize(game, "Map not surrounded by walls\n", NULL);
	if (x - 1 < 0 || (map[y] && map[y][x - 1] == ' '))
		sanitize(game, "Map not surrounded by walls\n", NULL);
	if (x + 1 >= row_len || (map[y] && map[y][x + 1] == ' '))
		sanitize(game, "Map not surrounded by walls\n", NULL);
	if (y - 1 < 0 || !map[y - 1] || x >= (int)ft_strlen(map[y - 1]) \
		|| map[y - 1][x] == ' ')
		sanitize(game, "Map not surrounded by walls\n", NULL);
	if (y + 1 >= game->map->y || !map[y + 1] || \
		x >= (int)ft_strlen(map[y + 1]) || map[y + 1][x] == ' ')
		sanitize(game, "Map not surrounded by walls\n", NULL);
}

void	check_map_closed(t_info *game)
{
	int		y;
	int		x;
	char	**map;

	map = game->map->arr;
	y = 0;
	while (y < game->map->y)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || player_char(map[y][x]))
				check_neighbor_cell(game, y, x);
			x++;
		}
		y++;
	}
}
