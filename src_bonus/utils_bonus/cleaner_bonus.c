/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:50:17 by alfreire          #+#    #+#             */
/*   Updated: 2025/04/09 09:26:15 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	del_tex(t_tex **list, t_info *game)
{
	t_tex	*del;
	t_tex	*tmp;

	if (!list || !(*list))
		return ;
	del = (*list);
	while (del)
	{
		tmp = del->next;
		if (del->img)
			mlx_destroy_image(game->mlx_ptr, del->img);
		free2(del->tex);
		free2(del);
		del = tmp;
	}
	*list = NULL;
	list = NULL;
}

void	ft_destroy_info(t_info *game)
{
	if (!game)
		exit(0);
	del_tex(&game->tex, game);
	if (game->full_file)
		ft_freearr(game->full_file);
	if (game->map)
	{
		ft_freearr(game->map->arr);
		free2(game->map);
	}
}

void	sanitize(t_info *game, char *msg, void *something)
{
	ft_destroy_info(game);
	free2(something);
	if (game->win->img && game->mlx_ptr)
		mlx_destroy_image(game->mlx_ptr, game->win->img);
	if (game->win->ptr && game->mlx_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win->ptr);
	if (game->mlx_ptr)
	{
		ONLYLINUX;
		free2(game->mlx_ptr);
	}
	free2(game->win);
	if (!msg)
		exit(EXIT_SUCCESS);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
