/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_aux_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:09:45 by alfreire          #+#    #+#             */
/*   Updated: 2025/03/12 10:49:45 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	space_wall(t_info *game, char c, char v, char b)
{
	if (c != 0 && c != ' ' && c != '1')
		sanitize(game, "Map not surrounded by walls\n", NULL);
	if (v != 0 && v != ' ' && v != '1')
		sanitize(game, "Map not surrounded by walls\n", NULL);
	if (b != 0 && b != ' ' && b != '1')
		sanitize(game, "Map not surrounded by walls\n", NULL);
}

void	first_row(t_info *game, char **arr, int x, int y)
{
	if (!arr || !arr[0] || !arr[0][0])
		sanitize(game, "Missing map", NULL);
	while (arr[y][x])
	{
		if (arr[y][x] != '1' && arr[y][x] != ' ')
			sanitize(game, "Map not surrounded by walls\n", NULL);
		x++;
	}
}

void	str_space(t_info *game, char *s, t_iter *x)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] > 32)
			sanitize(game, "Map can't be separated by a new line\n", x);
		i++;
	}
}

bool	nothing_line(t_info *game, char *s, int y, bool end)
{
	int	i;

	i = 0;
	if (end)
		return (end);
	while (s[i])
	{
		if (s[i] > 32)
			return (false);
		i++;
	}
	game->map->y = y - 1;
	return (true);
}
