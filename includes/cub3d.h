/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:45:15 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/22 16:43:58 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIN_WIDTH 1500
# define WIN_HEIGHT 800
# define TILE_SIZE 64
# define FOV 60
# define RES 64
# define MOVE_SPEED 6.f
# define COLOR_PLAYER 0xFF91D2FF
# define ROT_SPEED 0.05f
# define SCALE_FACTOR 0.2f
#define WALL_STRIP_WIDTH (WIN_WIDTH / WIN_WIDTH)
#define MINIMAP_WIDTH 200
#define MINIMAP_HEIGHT 200
#define MINIMAP_SCALE 30
#define COLOR_WALL 0xFF6347 
#define COLOR_FLOOR 0x00FFFFFF  

# include "../MLX/include/MLX42/MLX42.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_txts
{
	mlx_texture_t	*north_txt;
	mlx_texture_t	*south_txt;
	mlx_texture_t	*east_txt;
	mlx_texture_t	*west_txt;
	mlx_texture_t	**key_txt;
	mlx_texture_t	*door_txt;
	mlx_image_t		*image;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			**key;
	int				*floor;
	char			*door;
	int				*ceiling;
}					t_txts;

typedef struct s_sprite_vars
{
	float		sp_top_pos;
	float		sp_bot_pos;
	float		sp_xpos;
	float		sp_left_pos;
	float		sp_right_pos;
	float		sp_ang;
	int			tex_offsetx;
	int			tex_offsety;
	int			tex_width;
	int			tex_height;
	int			pos;
	uint32_t	color;
}				t_sprite_vars;

typedef struct s_sprites
{
	float			pos_x;
	float			pos_y;
	float			angle;
	float			dist;
	float			height;
	float			width;
	bool			is_vsbl;
	bool			collected;
	t_sprite_vars	vars;
}			t_sprites;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir;
	int		grid_x;
	int		grid_y;
	bool	move_up;
	bool	move_down;
	bool	move_left;
	bool	move_right;
}			t_player;

typedef struct s_vars
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
}			t_vars;

typedef struct s_rays
{
	float	ang;
	bool	is_door;
	char	wall_txt;
	bool	is_horz;
	float	hdist;
	float	vdist;
	t_vars	horz_v;
	t_vars	vert_v;
	int		hwallhitx;
	int		hwallhity;
	int		vwallhitx;
	int		vwallhity;
	float	wall_height;
}			t_rays;

typedef struct s_game
{
	t_sprites	**sprites;
	t_txts		*textures;
	mlx_t		*mlx_ptr;
	t_player	*player;
	t_rays		*rays;
	char		**map;
	char		pov;
	int			key_count;
	int			key_collected;
	int			map_width;
	int			map_height;
	int			square_size;
	int			sprite_flag;
	int			sprite_counter;
	float		fov_rad;
	float		proj_dist;
	bool	door_key;
}				t_game;
typedef struct s_increment
{
	float		x;
	float		y;
	int			steps;
}				t_increment;

t_game	*parse_data(char *path);

// tests
void	print_textures(t_txts *textures);
void	print_map(t_game *data);
// parsing
void	check_door(t_game *data);

// draw
void	draw_map(t_game *data);
bool	ang_to_right(float ang);
bool	ang_to_left(float ang);
bool	ang_up(float ang);
bool	ang_down(float ang);
float	normalize_angle(float ang);
float	calcul_dist(float x1, float y1, float x2, float y2);
void	calculate_hdist(t_game *data, t_rays *ray);
void	calculate_vdist(t_game *data, t_rays *ray);
void	cast_rays(t_game *data);
void	draw_line(mlx_image_t *image, int x0, int y0, int x1, int y1, int maxH, int maxW);
char	locate_wall(t_rays *ray, t_game *data);
void	draw_circle(mlx_image_t *image, int center_x, int center_y, int radius,
		uint32_t color);
bool	load_pngs(t_game *data, t_txts *txts);
float	calculate_wheight(t_game *data, int i, mlx_texture_t **txt);

// minimap
void	mini_map(t_game *data);
void	check_door(t_game *data);
// door
void	check_h(float dst,t_game *data, int i, int j);
void check_v(float dst,t_game *data, int i, int j);

#endif