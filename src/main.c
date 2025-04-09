/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:16 by alfreire          #+#    #+#             */
/*   Updated: 2025/03/12 11:00:26 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//TESTER MAIN
int	main(int argc, char **argv)
{
	t_info	game;

	if (argc != 2)
		return (ft_putstr_fd("Error\nTwo arguments please.\n", 2), 1);
	init_game(&game, argv[1]);
	sanitize(&game, NULL, NULL);
	return (0);
}

/* 
int	main(int ac, char **av)
{
	t_info	game;

	if (ac != 2)
		ft_putstr_fd("Error\n Only one argument please.\n", 2);
	if (!valid_filename(av[1]))
		fail_message(NULL, "Not a valid file name\n");
	ft_bzero(&game, sizeof(t_info));
	read_map(av[1], &game);
	check_map(&game);

} */