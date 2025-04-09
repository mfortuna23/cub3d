/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:15:35 by mfortuna          #+#    #+#             */
/*   Updated: 2025/03/12 11:01:12 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	mlx_put_image_to_window(game->mlx_ptr, game->win->ptr, \
	game->win->img, 0, 0);
	return (0);
}
