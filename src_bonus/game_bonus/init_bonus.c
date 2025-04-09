/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:04:48 by mfortuna          #+#    #+#             */
/*   Updated: 2025/03/12 11:05:48 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

t_tex	*create_tex(enum e_type type)
{
	t_tex	*new;

	new = malloc(sizeof(t_tex));
	new->next = NULL;
	new->tex = NULL;
	new->addr = NULL;
	new->img = NULL;
	new->type = type;
	return (new);
}

void	init_player(t_info *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->player.angle = 0;
}

void	init_game(t_info *game, char *map)
{
	enum e_type	type;
	t_tex		*tmp;

	type = NO;
	game->map = ft_calloc(1, sizeof(t_map));
	game->win = ft_calloc(1, sizeof(t_win));
	init_player(game);
	game->mlx_ptr = NULL;
	game->tex = NULL;
	game->full_file = NULL;
	game->tex = create_tex(type);
	tmp = game->tex;
	while (++type <= CE)
	{
		tmp->next = create_tex(type);
		tmp = tmp->next;
	}
	get_map(game, map);
	ft_game(game);
}

t_iter	*init_iter(void)
{
	t_iter	*new;

	new = malloc(sizeof(t_iter));
	new->c = 'a';
	new->i = 0;
	new->j = 0;
	new->x = 0;
	new->y = 0;
	return (new);
}

t_paint	*init_paint(int x_start, int x_finish, int y_start, int y_finish)
{
	t_paint	*new;

	new = malloc(sizeof(t_paint));
	new->x_start = x_start;
	new->x_finish = x_finish;
	new->y_start = y_start;
	new->y_finish = y_finish;
	return (new);
}
