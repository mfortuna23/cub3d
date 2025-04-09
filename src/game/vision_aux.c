/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:34:58 by alfreire          #+#    #+#             */
/*   Updated: 2025/03/12 10:49:17 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_wall	calc_wall_params(t_info *game, t_ray *ray, t_tex *tex)
{
	t_wall	w;

	w.wall_height = (int)(HEIGHT / ray->distance);
	w.draw_start = HEIGHT / 2 - w.wall_height / 2;
	if (w.draw_start < 0)
		w.draw_start = 0;
	w.draw_end = HEIGHT / 2 + w.wall_height / 2;
	if (w.draw_end >= HEIGHT)
		w.draw_end = HEIGHT - 1;
	if (ray->side == 0)
		w.wallx = game->player.y + ray->distance * ray->dir_y;
	else
		w.wallx = game->player.x + ray->distance * ray->dir_x;
	w.wallx = w.wallx - floor(w.wallx);
	w.tex_x = (int)(w.wallx * tex->width);
	if ((ray->side == 0) && (ray->dir_x > 0))
		w.tex_x = tex->width - w.tex_x - 1;
	if ((ray->side == 1) && (ray->dir_y < 0))
		w.tex_x = tex->width - w.tex_x - 1;
	w.step = (double)tex->height / w.wall_height;
	w.tex_pos = (w.draw_start - HEIGHT / 2 + w.wall_height / 2) * w.step;
	return (w);
}

t_tex	*get_texture_from_id(t_info *game, int tex_id)
{
	t_tex	*tmp;

	tmp = game->tex;
	while (tmp)
	{
		if ((int)tmp->type == tex_id)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	get_texture_id(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (EA);
		else
			return (WE);
	}
	else
	{
		if (ray->step_y > 0)
			return (SO);
		else
			return (NO);
	}
}

void	draw_textured_column(t_info *game, int x, t_wall wall, t_tex *tex)
{
	int	y;
	int	tex_y;

	y = wall.draw_start;
	while (y < wall.draw_end)
	{
		tex_y = (int)wall.tex_pos & (tex->height - 1);
		wall.tex_pos += wall.step;
		put_pixel(game->win, x, y, get_tex_pixel(tex, wall.tex_x, tex_y));
		y++;
	}
}

void	draw_wall(t_info *game, int x, t_ray *ray, int tex_id)
{
	t_tex	*tex;
	t_wall	wall;

	tex = get_texture_from_id(game, tex_id);
	if (!tex)
		return ;
	wall = calc_wall_params(game, ray, tex);
	draw_textured_column(game, x, wall, tex);
}
