/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:15:35 by mfortuna          #+#    #+#             */
/*   Updated: 2025/03/12 11:00:10 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	load_texture(t_info *game, t_tex *tex)
{
	tex->img = mlx_xpm_file_to_image(game->mlx_ptr, tex->tex,
			&tex->width, &tex->height);
	if (!tex->img)
		sanitize(game, "Loading texture\n", NULL);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_pp, \
		&tex->line_len, &tex->endian);
}

void	load_all_textures(t_info *game)
{
	t_tex	*tmp;

	tmp = get_texture_from_id(game, NO);
	if (!tmp)
		sanitize(game, "Missing texture NO\n", NULL);
	load_texture(game, tmp);
	tmp = get_texture_from_id(game, SO);
	if (!tmp)
		sanitize(game, "Missing texture SO\n", NULL);
	load_texture(game, tmp);
	tmp = get_texture_from_id(game, WE);
	if (!tmp)
		sanitize(game, "Missing texture WE\n", NULL);
	load_texture(game, tmp);
	tmp = get_texture_from_id(game, EA);
	if (!tmp)
		sanitize(game, "Missing texture EA\n", NULL);
	load_texture(game, tmp);
}

void	render_mini(t_info *game, int x_max, int y_max, t_iter *t)
{
	int		b;

	if (game->map->x > game->map->y)
	{
		b = x_max / game->map->x;
		if (b * game->map->y > y_max)
			b = y_max / game->map->y;
	}
	else
		b = y_max / game->map->y;
	paint_block(game, init_paint(0, game->map->x * b, 0, game->map->y * b), 0);
	while (game->map->arr[t->y])
	{
		while (game->map->arr[t->y][t->x])
		{
			if (game->map->arr[t->y][t->x] == '1')
				paint_block(game, init_paint((t->x * b) + 1, (t->x * b) + b, \
				(t->y * b) + 1, (t->y * b) + b), 16448250);
			t->x++;
		}
		t->x = 0;
		t->y++;
	}
	game->map->b_size = b;
	free2(t);
}

void	player_on_mini(t_info *game)
{
	int	x_s;
	int	y_s;
	int	x_f;
	int	y_f;
	int	ps;

	ps = game->map->b_size / 8;
	x_s = (game->player.x * game->map->b_size) - ps;
	y_s = (game->player.y * game->map->b_size) - ps;
	x_f = (game->player.x * game->map->b_size) + ps;
	y_f = (game->player.y * game->map->b_size) + ps;
	paint_block(game, init_paint(x_s, x_f, y_s, y_f), 2685690);
	return ;
}

int	render_game(void *old)
{
	t_info	*game;
	t_tex	*color;

	game = (t_info *)old;
	color = game->tex;
	while (color->type != CE)
		color = color->next;
	paint_block(game, init_paint(0, WIDTH, 0, HEIGHT / 2), color->color);
	color = game->tex;
	while (color->type != FL)
		color = color->next;
	paint_block(game, init_paint(0, WIDTH, HEIGHT / 2, HEIGHT), color->color);
	render_frame(game);
	render_mini(game, WIDTH / 4, HEIGHT / 4, init_iter());
	player_on_mini(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win->ptr, \
	game->win->img, 0, 0);
	return (0);
}
