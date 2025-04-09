/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:05:38 by mfortuna          #+#    #+#             */
/*   Updated: 2025/03/12 10:49:18 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned long	get_color(t_info *game, char *color, t_iter *x);

void	w_textures(t_info *game, t_iter *x, enum e_type type)
{
	t_tex	*current;
	int		i;

	i = 0;
	current = game->tex;
	while (current->next && current->type != type)
		current = current->next;
	if (current->tex)
		sanitize(game, "Duplicated textures\n", x);
	if (type == CE || type == FL)
		i = 1;
	else
		i = 2;
	while (game->full_file[x->y][x->x + i] && \
		game->full_file[x->y][x->x + i] < 33)
		x->x++;
	current->tex = ft_strdup(game->full_file[x->y] + x->x + i);
	if (!current->tex || current->tex[0] == '\0')
		sanitize(game, "Missing texture path or color\n", x);
	if (type == NO || type == SO || type == WE || type == EA)
		return ;
	current->color = get_color(game, current->tex, x);
}

void	all_tex(t_info *game, t_iter *x)
{
	t_tex	*new;

	new = game->tex;
	if (!new)
		sanitize(game, "Missing textures \n", x);
	while (new)
	{
		if (!new->tex)
			sanitize(game, "Missing textures \n", x);
		new = new->next;
	}
}

int	get_textures(t_info *game, t_iter *x)
{
	while (game->full_file[x->y])
	{
		while (game->full_file[x->y][x->x] && game->full_file[x->y][x->x] <= 32)
			x->x++;
		if (game->full_file[x->y][x->x] == 0)
			x->x = 0;
		else if (ft_strncmp(game->full_file[x->y] + x->x, "NO", 2) == 0)
			w_textures(game, x, NO);
		else if (ft_strncmp(game->full_file[x->y] + x->x, "SO", 2) == 0)
			w_textures(game, x, SO);
		else if (ft_strncmp(game->full_file[x->y] + x->x, "WE", 2) == 0)
			w_textures(game, x, WE);
		else if (ft_strncmp(game->full_file[x->y] + x->x, "EA", 2) == 0)
			w_textures(game, x, EA);
		else if (ft_strncmp(game->full_file[x->y] + x->x, "F", 1) == 0)
			w_textures(game, x, FL);
		else if (ft_strncmp(game->full_file[x->y] + x->x, "C", 1) == 0)
			w_textures(game, x, CE);
		else
			break ;
		x->y++;
		x->x = 0;
	}
	all_tex(game, x);
	return (x->y);
}

bool	is_allnbr(char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (false);
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

unsigned long	get_color(t_info *game, char *color, t_iter *x)
{
	int		i;
	int		r;
	int		g;
	int		b;
	char	**arr;

	i = 0;
	if (color[0] == ',' || color[ft_strlen(color) - 1] == ',')
		sanitize(game, "Invalid color\n", x);
	while (color[i])
	{
		if (color[i] == ',' && color[i + 1] == ',')
			sanitize(game, "Invalid color\n", x);
		i++;
	}
	arr = ft_split(color, ',');
	if (!arr || !arr[0] || !arr[1] || !arr[2] || arr[3])
		return (ft_freearr(arr), sanitize(game, "Invalid color\n", x), 1);
	if (!is_allnbr(arr[0]) || !is_allnbr(arr[1]) || !is_allnbr(arr[2]))
		return (ft_freearr(arr), sanitize(game, "Invalid color\n", x), 1);
	r = ft_atoi(arr[0]);
	g = ft_atoi(arr[1]);
	b = ft_atoi(arr[2]);
	ft_freearr(arr);
	return ((r << 16) | (g << 8) | b);
}
