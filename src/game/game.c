/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:10:34 by mfortuna          #+#    #+#             */
/*   Updated: 2025/03/12 10:49:16 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	on_destroy(t_info *game)
{
	sanitize(game, NULL, NULL);
	return (0);
}

int	on_keypress(int keysym, t_info *game)
{
	if (keysym == W)
		move_front(game);
	else if (keysym == A)
		move_left(game);
	else if (keysym == S)
		move_back(game);
	else if (keysym == D)
		move_right(game);
	else if (keysym == ESC)
		on_destroy(game);
	else if (keysym == LEFT)
		rotate(game, game->player.dir_x, game->player.dir_y, false);
	else if (keysym == RIGHT)
		rotate(game, game->player.dir_x, game->player.dir_y, true);
	return (0);
}

void	ft_game(t_info *game)
{
	set_player_direction(game);
	set_player_plane(game);
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return ;
	load_all_textures(game);
	game->win->ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "CUB3D");
	if (!game->win->ptr)
		return (free2(game->mlx_ptr));
	game->win->img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	game->win->addr = mlx_get_data_addr(game->win->img, &game->win->bits_pp, \
		&game->win->line_len, &game->win->endian);
	mlx_hook(game->win->ptr, 2, (1L << 0), on_keypress, game);
	mlx_hook(game->win->ptr, 17, 0L, on_destroy, game);
	mlx_loop_hook(game->mlx_ptr, &render_game, game);
	mlx_loop(game->mlx_ptr);
	on_destroy(game);
}
