/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:45:15 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/02/06 18:55:23 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIN_WIDTH 1800
# define WIN_HEIGHT (16 * 1800) / 35
# define TILE_SIZE 64
# define FOV 60
# define RAY_ANGLE (FOV * M_PI / 180) / WIN_WIDTH
# define RES 64
# define MOVE_SPEED 1
#define COLOR_PLAYER 0xFF91D2FF
#define ROT_SPEED 0.2

# include "../MLX/include/MLX42/MLX42.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_txts
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	mlx_image_t	*image;
	int			*floor;
	int			*ceiling;
}				t_txts;
typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	int 	grid_x;
	int 	grid_y;
	float		dir;
	bool		move_up;
	bool		move_down;
	bool		move_left;
	bool		move_right;
}				t_player;
typedef struct s_game
{
	mlx_t		*mlx_ptr;
	t_txts		*textures;
	char		**map;
	char		pov;
	int			map_width;
	int			map_height;
	t_player	*player;
	int square_size;
}				t_game;

t_game			*parse_textures(char *path);

// tests
void			print_textures(t_txts *textures);
void			print_map(t_game *data);

// draw
void			draw_map(t_game *data);

// player
// void    game_loop(void *param);
// void	release_key(struct mlx_key_data keycode, void *param);
// void	move_player(struct mlx_key_data keycode, void *param)	;
// void	player_position(t_game *data);
// void	player_movement(t_game *data);
void	draw_circle(mlx_image_t *image, int center_x, int center_y, int radius,
		uint32_t color);

#endif