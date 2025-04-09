/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:09:53 by mfortuna          #+#    #+#             */
/*   Updated: 2025/03/12 10:49:46 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	ft_countarr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*str_join(char *s1, char *s2)
{
	size_t	size;
	char	*p;

	if (s1 == NULL)
		size = ft_strlen(s2) + 1;
	else
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = (char *)ft_calloc(sizeof(char), size);
	if (!p)
		return (0);
	ft_memcpy(p, s1, ft_strlen(s1));
	ft_strlcat(p, s2, size);
	free2(s1);
	free2(s2);
	return (p);
}

void	free2(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
	ptr = NULL;
}

// new get_next_line that does not store any thing
char	*ft_oneline(int fd)
{
	char	*line;
	char	*one;
	int		size;

	if (fd < 0)
		return (NULL);
	one = NULL;
	line = ft_calloc(1, sizeof(char));
	while (ft_strchr(line, '\n') == NULL)
	{
		one = ft_calloc(2, sizeof(char));
		size = read(fd, one, 1);
		if (size < 1)
		{
			free(one);
			if (ft_strlen(line) == 0)
			{
				free(line);
				return (NULL);
			}
			return (line);
		}
		line = str_join(line, one);
	}
	return (line);
}

char	safe_get_cell(t_info *game, int row, int col)
{
	int	len;

	if (row < 0 || row >= game->map->y)
		return ('1');
	len = ft_strlen(game->map->arr[row]);
	if (col < 0 || col >= len)
		return ('1');
	return (game->map->arr[row][col]);
}
