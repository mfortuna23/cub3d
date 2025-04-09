/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:47:09 by mfortuna          #+#    #+#             */
/*   Updated: 2025/03/12 10:49:18 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	n_readlines(t_info *game, int fd, char *line, char *tmp)
{
	free2(line);
	free2(tmp);
	close(fd);
	sanitize(game, "File too big\n", NULL);
}

void	read_map(t_info *game, int fd, int r)
{
	char	*tmp;
	char	*tmp2;
	char	*line;

	tmp = ft_strdup("");
	line = ft_oneline(fd);
	while (line)
	{
		r++;
		if (r > 200)
			n_readlines(game, fd, line, tmp);
		if (line[0] == '\n')
		{
			tmp2 = line;
			line = ft_strdup(" \n");
			free2(tmp2);
		}
		tmp = str_join(tmp, line);
		line = ft_oneline(fd);
	}
	close(fd);
	game->full_file = ft_split(tmp, '\n');
	free2(line);
	free2(tmp);
}

bool	valid_filename(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (false);
	if (ft_strnstr(filename + (len - 4), ".cub", 4) != NULL)
		return (true);
	else
		return (false);
}

void	get_info(t_info *game, t_iter *x, bool end)
{
	get_textures(game, x);
	if (!game->full_file[x->y] || !game->full_file[x->y][x->x])
		sanitize(game, "Empty map\n", x);
	game->map->arr = ft_calloc((ft_countarr(game->full_file) - x->y) + 1, \
	sizeof(char *));
	game->map->x = ft_strlen(game->full_file[x->y]);
	while (game->full_file[x->y])
	{
		end = nothing_line(game, game->full_file[x->y], x->y, end);
		if (!end)
		{
			game->map->arr[x->i] = ft_strdup(game->full_file[x->y]);
			if (ft_strlen(game->full_file[x->y]) > game->map->x)
				game->map->x = ft_strlen(game->full_file[x->y]);
			x->i++;
		}
		else
			str_space(game, game->full_file[x->y], x);
		x->y++;
	}
	if (game->map->y == 0)
		game->map->y = x->i;
	free2(x);
}

void	get_map(t_info *game, char *map_name)
{
	int		fd;

	if (!valid_filename(map_name))
		sanitize(game, "Invalid file extension\n", NULL);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		sanitize(game, "Map not found\n", NULL);
	read_map(game, fd, 0);
	close(fd);
	get_info(game, init_iter(), false);
	game->map->y = ft_countarr(game->map->arr);
	if (!game || !game->map || !game->map->arr || \
		!game->map->arr[0] || !game->map->arr[0][0])
		sanitize(game, "Map is empty\n", NULL);
	if (game->map->x > 50 || game->map->y > 50)
		sanitize(game, "Map is too long\n", NULL);
	valid_characters(game);
	find_player(game);
	check_map_closed(game);
}
