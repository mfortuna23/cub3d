/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:26:44 by alfreire          #+#    #+#             */
/*   Updated: 2025/04/09 09:22:16 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>

# if defined(__linux__)
# define W 119
# define UP 65362
# define A 97
# define LEFT 65361
# define S 115
# define DOWN 65364
# define D 100
# define RIGHT 65363
# define ESC 65307
# define ONLYLINUX mlx_destroy_display(game->mlx_ptr)

# elif defined(__APPLE__) && defined(__MACH__)
# define W 13
# define UP 126
# define A 0
# define LEFT 123
# define S 1
# define DOWN 125
# define D 2
# define RIGHT 124
# define ESC 53
# define ONLYLINUX (void)something
# endif

# define HEIGHT 1000
# define WIDTH 1900
# define PI 3.14159265358979
# define PR 0.05

typedef struct s_wall
{
	int		wall_height;
	int		draw_start;
	int		draw_end;
	double	wallx;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_wall;

typedef struct s_ray
{
	int		map_x;	// Posição na grade do mapa (coordenada X da grade)
	int		map_y;	// Posição na grade do mapa (coordenada Y da grade)
	double	dir_x;	// Direção do raio no eixo X
	double	dir_y;	// Direção do raio no eixo Y
	double	delta_x;// tempo ate as interseções verticais
	double	delta_y;// tempo ate as interseções horizontais
	double	side_x;	// Distância até a próxima linha vertical
	double	side_y;	// Distância até a próxima linha horizontal
	int		step_x;	// Direção do raio no eixo X (+1 ou -1)
	int		step_y;	// Direção do raio no eixo Y (+1 ou -1)
	int		side;	// armazena se a última borda cruzada foi vertical
	double	distance;// Distância corrigida do raio até a parede
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	char	c;
	double	plane_x;
	double	plane_y;
	double	dir_x;
	double	dir_y;
	double	angle;
}		t_player;

typedef struct s_info
{
	char			**full_file;
	struct s_map	*map;
	struct s_tex	*tex;
	struct s_win	*win;
	t_player		player;
	void			*mlx_ptr;
}	t_info;

typedef struct s_win
{
	void	*ptr;
	void	*img;
	char	*addr;
	int		bits_pp;
	int		endian;
	int		line_len;
}			t_win;

enum	e_type
{
	NO,
	SO,
	WE,
	EA,
	FL,
	CE,
};

typedef struct s_map
{
	char	**arr;
	int		y;
	int		x;
	int		b_size;
}	t_map;

typedef struct s_tex
{
	enum e_type		type;
	char			*tex;// Caminho do arq de textura
	void			*img;// Ponteiro para a imagem carregada pela MLX
	char			*addr;// Endereço do buffer de pixels da imagem
	int				width;// Largura da imagem
	int				height;// Altura da imagem
	int				bits_pp;// Bits por pixel (usado em get_data_addr)
	int				line_len;// Tamanho da linha (em bytes)
	int				endian;// Endianness
	int				color;
	struct s_tex	*next;
}	t_tex;

typedef struct s_iter
{
	char	c;
	int		i;
	int		j;
	int		x;
	int		y;
}	t_iter;

typedef struct s_paint
{
	int		x_start;
	int		x_finish;
	int		y_start;
	int		y_finish;
}	t_paint;

// CLEANER
void	sanitize(t_info *game, char *msg, void *something);

//utils
int		ft_countarr(char **arr);
char	*ft_oneline(int fd);
char	*str_join(char *s1, char *s2);
void	free2(void *ptr);
char	safe_get_cell(t_info *game, int row, int col);

// MAP CHECKER
void	valid_characters(t_info *game);
void	check_map_closed(t_info *game);

// MAP CHECKER AUX
void	space_wall(t_info *game, char c, char v, char b);
void	first_row(t_info *game, char **arr, int x, int y);
bool	nothing_line(t_info *game, char *s, int y, bool end);
void	str_space(t_info *game, char *s, t_iter *x);

//MAP FILE CHECKER
bool	valid_filename(char *filename);
void	read_map(t_info *game, int fd, int r);
void	get_map(t_info *game, char *map_name);

//P_PLAYER
void	find_player(t_info *game);
bool	player_char(char c);

//TEXTURES
int		get_textures(t_info *game, t_iter *x);

//INIT
void	init_game(t_info *game, char *map);
t_iter	*init_iter(void);
t_paint	*init_paint(int x_start, int x_finish, int y_start, int y_finish);

//GAME
void	ft_game(t_info *game);
int		on_destroy(t_info *game);

//PIXEL
void	paint_celling(t_info *game, int color);
void	paint_floor(t_info *game, int color);
void	put_pixel(t_win *window, int x, int y, int color);
void	paint_block(t_info *game, t_paint *p, int color);
int		get_tex_pixel(t_tex *tex, int tex_x, int tex_y);

//render
int		render_game(void *game);
void	load_all_textures(t_info *game);
void	load_texture(t_info *game, t_tex *tex);

//player_vision
void	perform_dda(t_ray *ray, t_info *game);
void	init_ray(t_ray *ray, t_info *game, double ray_dir_x, double ray_dir_y);
double	calculate_distance(t_ray *ray, t_info *game);
void	cast_ray(t_info *game, int x, double ray_dir_x, double ray_dir_y);
void	render_frame(t_info *game);

// player_aux
void	set_player_direction(t_info *game);
void	set_player_plane(t_info *game);
int		fix_angle(int a);
void	update_dir(double *x, double *y, int a);
void	step_side_y(t_ray *ray, double side_y);

//player_move
void	move_front(t_info *game);
void	move_back(t_info *game);
void	move_left(t_info *game);
void	move_right(t_info *game);
void	rotate(t_info *game, double x, double y, bool rigth);

//vision_aux
void	draw_wall(t_info *game, int x, t_ray *ray, int tex_id);
int		get_texture_id(t_ray *ray);
t_tex	*get_texture_from_id(t_info *game, int tex_id);

#endif
