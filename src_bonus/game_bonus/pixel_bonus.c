/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:47:16 by mfortuna          #+#    #+#             */
/*   Updated: 2025/03/12 11:11:37 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	put_pixel(t_win *window, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
		return ;
	dst = window->addr + (y * window->line_len + x * (window->bits_pp / 8));
	*(int *)dst = color;
}

void	paint_block(t_info *game, t_paint *p, int color)
{
	int	x;

	x = p->x_start;
	while (p->y_start < p->y_finish)
	{
		while (p->x_start < p->x_finish)
			put_pixel(game->win, p->x_start++, p->y_start, color);
		p->x_start = x;
		p->y_start++;
	}
	free2(p);
}

int	get_tex_pixel(t_tex *tex, int tex_x, int tex_y)
{
	char	*pixel;

	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bits_pp / 8));
	return (*(unsigned int *)pixel);
}
