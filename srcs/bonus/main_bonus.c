/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:05:07 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/22 16:28:33 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/parsing.h"
#include "../../includes/render.h"

#include <stdio.h>

#define COLOR_WALL 0xFF6347     // Green
#define COLOR_FLOOR 0x00FFFFFF  // Blue
#define COLOR_PLAYER 0xFF91D2FF // Pink

void    player_movement(t_game *data)
{
    double new_x, new_y;
    double grid_x, grid_y;
    
    // Forward/Backward Movement (W/S or Up/Down arrows)
    if (data->player->move_up)
    {
        new_x = data->player->pos_x + cos(data->player->dir) * 7;
        new_y = data->player->pos_y + sin(data->player->dir) * 7;
        grid_x = (int)(new_x / TILE_SIZE) ;
        grid_y = (int)(new_y / TILE_SIZE);
        if (grid_x >= 0 && grid_x < data->map_width && grid_y >= 0
            && grid_y < data->map_height && data->map[(int)grid_y ][(int)grid_x ] != '1'&& data->map[(int)grid_y][(int)grid_x] != 'D')
        {
            data->player->pos_x = new_x;
            data->player->pos_y = new_y;
        } 
    }
    if (data->player->move_down)
    {
        new_x = data->player->pos_x - cos(data->player->dir) * 7;
        new_y = data->player->pos_y - sin(data->player->dir) * 7;
        grid_x = (int)(new_x / TILE_SIZE);
        grid_y = (int)(new_y / TILE_SIZE);
        if (grid_x >= 0 && grid_x < data->map_width && grid_y >= 0
            && grid_y < data->map_height && data->map[(int)grid_y][(int)grid_x] != '1' && data->map[(int)grid_y][(int)grid_x] != 'D')
        {
            data->player->pos_x = new_x;
            data->player->pos_y = new_y;
        }
    }
	for (int i = 0; i < data->key_count; i++)
	{
		if (!data->sprites[i]->collected && fabs(data->sprites[i]->pos_x - data->player->pos_x) < 25.f && fabs(data->sprites[i]->pos_y - data->player->pos_y) < 25.f)
		{
			data->sprites[i]->collected = true;
			data->key_collected++;
		}
	}
    // Rotation (A/D or Left/Right arrows)
    if (data->player->move_right)
    {
        data->player->dir += ROT_SPEED;
        data->player->dir = fmod(data->player->dir, 2 * M_PI);
        if (data->player->dir < 0)
            data->player->dir += 2 * M_PI;
    }
    if (data->player->move_left)
    {
        data->player->dir -= ROT_SPEED;
        data->player->dir = fmod(data->player->dir, 2 * M_PI);
        if (data->player->dir < 0)
            data->player->dir += 2 * M_PI;
    }
}
	

void draw_square_border(mlx_image_t *image, int x, int y, t_game *data)
{
    int i, j;
	i = 0;
    uint32_t border_color = 0x00000000;
    int square_width = WIN_WIDTH / data->map_width;
    int square_height = WIN_HEIGHT / data->map_height;

    while (i < square_height)
    {
		j = 0; 
        while (j < square_width)
        {
            if (i == 0 || i == square_height - 1 || j == 0 || j == square_width - 1)
            {
                mlx_put_pixel(image, x + j, y + i, border_color);
            }
			j++;
        }
		i++;
    }
}

	void	draw_square(mlx_image_t *image, int x, int y, t_game *data, uint32_t color)
	{
		int i, j;
		i = 0;
		while (i < WIN_WIDTH / data->map_width)
		{
			j = 0;
			while ( j < WIN_HEIGHT / data->map_height)
				{
					mlx_put_pixel(image, (x + i) , (y + j), color);
					j++;
				}
			i++;
		}
		draw_square_border(image, x, y, data);
	}

	void	draw_circle(mlx_image_t *image, int center_x, int center_y, int radius,
			uint32_t color)
	{
		int	x;
		int	y;
		int	err;
		int	i;

		x = radius;
		y = 0;
		err = 0;
		while (x >= y)
		{
			i = -x;
			while (i <= x)
			{
				mlx_put_pixel(image, (center_x + i), (center_y + y), color);
				mlx_put_pixel(image, (center_x + i), (center_y - y), color);
				i++;
			}
			i = -y;
			while (i <= y)
			{
				mlx_put_pixel(image, (center_x + i), (center_y + x) , color);
				mlx_put_pixel(image, (center_x + i), (center_y - x), color);
				i++;
			}
			if (err <= 0)
			{
				y++;
				err += 2 * y + 1;
			}
			if (err > 0)
			{
				x--;
				err -= 2 * x + 1;
			}
		}
	}

	int	calculate_square_size(t_game *data)
	{
		int	tile_size_width;
		int	tile_size_height;

		tile_size_width = WIN_WIDTH / data->map_width;
		tile_size_height = WIN_HEIGHT / data->map_height;
		return ((tile_size_width < tile_size_height) ? tile_size_width : tile_size_height);
	}

void	get_map_size(t_game *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	data->map_width = 0;
	data->map_height = 0;
	while (data->map[y])
	{
		x = ft_strlen(data->map[y]);
		if (x > data->map_width)
			data->map_width = x;
		y++;
	}
	data->map_height = y;
}

	void	draw_line(mlx_image_t *image, int x0, int y0, int x1, int y1, int maxH, int maxW)
	{
		int dx;
		int dy;
		int sx;
		int sy;
		int err;
		int e2;

		dx = abs(x1 - x0);
		sx = x0 < x1 ? 1 : -1;
		dy = -abs(y1 - y0);
		sy = y0 < y1 ? 1 : -1;
		err = dx + dy;
		while (x0 != x1 || y0 != y1)
		{
			if (x0 > 0 && y0 > 0 && x0 < maxW && y0 < maxH)
				mlx_put_pixel(image, x0, y0, 0x000000FF);
			e2 = 2 * err;
			if (e2 >= dy)
			{
				err += dy;
				x0 += sx;
			}
			if (e2 <= dx)
			{
				err += dx;
				y0 += sy;
			}
		}
	}
	void	draw_map(t_game *data)
	{
		uint32_t	color;

		int x, y;
		y = 0;
		while (y < data->map_height)
		{
			x = 0;
			while(x < data->map_width)
			{
				if (x < (int)ft_strlen(data->map[y]) && data->map[y][x] == '1')
					color = COLOR_WALL;
				else
					color = COLOR_FLOOR;
				draw_square(data->textures->image, x * TILE_SIZE, y
					* TILE_SIZE, data, color);
				x++;
			}
			y++;
		}
		draw_circle(data->textures->image, data->player->pos_x, data->player->pos_y,
			5, COLOR_PLAYER);
	}
	void	render_3d_map(t_game *data)
	{
		int i = 0;
		double ray;
		while(i < WIN_WIDTH)
		{
			ray =// n7t data dial ray

			i++;
		}

	}


	void	release_key(mlx_key_data_t keycode, void *param)
	{
		t_game	*data;

		data = (t_game *)param;
		if (keycode.key == MLX_KEY_W)
			data->player->move_up = false;
		else if (keycode.key == MLX_KEY_S)
			data->player->move_down = false;
		else if (keycode.key == MLX_KEY_A)
			data->player->move_left = false;
		else if (keycode.key == MLX_KEY_D)
			data->player->move_right = false;
	}

	void	move_player(mlx_key_data_t keycode, void *param)
	{
		t_game	*data;

		data = (t_game *)param;
		if (keycode.key == MLX_KEY_W)
			data->player->move_up = true;
		else if (keycode.key == MLX_KEY_S)
			data->player->move_down = true;
		else if (keycode.key == MLX_KEY_A)
			data->player->move_left = true;
		else if (keycode.key == MLX_KEY_D)
			data->player->move_right = true;
		else if (keycode.key == MLX_KEY_ESCAPE)
			exit(0);
	}

void	player_position(t_game *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'W' || data->map[y][x] == 'E')
			{
				data->player->grid_x = x;
				data->player->grid_y = y;
				if (data->map[y][x] == 'N')
					data->player->dir = 3 * (M_PI / 2);
				else if (data->map[y][x] == 'S')
					data->player->dir = M_PI / 2;
				else if (data->map[y][x] == 'W')
					data->player->dir = M_PI;
				else if (data->map[y][x] == 'E')
					data->player->dir = 0;
				data->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

	void	handle_key_input(mlx_key_data_t keycode, void *param)
	{
		t_game	*data;

		data = (t_game *)param;
		if (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT)
		{
			if (keycode.key == MLX_KEY_W)
				data->player->move_up = true;
			else if (keycode.key == MLX_KEY_S)
				data->player->move_down = true;
			else if (keycode.key == MLX_KEY_A)
				data->player->move_left = true;
			else if (keycode.key == MLX_KEY_D)
				data->player->move_right = true;
			else if(keycode.key == MLX_KEY_Z)
				data->door_key = true;
			else if (keycode.key == MLX_KEY_ESCAPE)
				exit(0);
		}
		else if (keycode.action == MLX_RELEASE)
		{
			if (keycode.key == MLX_KEY_W)
				data->player->move_up = false;
			else if (keycode.key == MLX_KEY_S)
				data->player->move_down = false;
			else if (keycode.key == MLX_KEY_A)
				data->player->move_left = false;
			else if (keycode.key == MLX_KEY_D)
				data->player->move_right = false;
		}
	}

void	render_game(void *param)
{
	t_game	*data;

	data = (t_game *)param;
	player_movement(data);
	if (!data->sprite_flag)
		data->sprite_counter++;
	else
		data->sprite_counter--;
	if (data->sprite_counter == 24)
		data->sprite_flag = 1;
	else if (!data->sprite_counter)
		data->sprite_flag = 0;
	ft_memset(data->textures->image->pixels, 0, data->textures->image->width
		* data->textures->image->height * sizeof(uint32_t));
	cast_rays(data);
	render_fl_cl(data);
	render_walls(data);
	handle_sprites(data);
	mini_map(data);
}

void    cursor_cb(double x, double y, void *param)
{
    t_game          *data;
    double          delta;

    data = (t_game *)param;
    delta = x - (WIN_WIDTH / 2);
    data->player->dir += delta * 0.0005;
    data->player->dir = normalize_angle(data->player->dir);
    mlx_set_mouse_pos(data->mlx_ptr, WIN_WIDTH/2, WIN_HEIGHT/2);
    mlx_set_cursor_mode(data->mlx_ptr, MLX_MOUSE_HIDDEN);
}

int	main(int ac, char **av)
{
	t_game *data;

	if (ac == 2 && av[1])
	{
		data = parse_data(av[1]);
		if (!data)
			return (1);
		data->player->pos_x = data->player->grid_x * TILE_SIZE
			+ TILE_SIZE / 2;
		data->player->pos_y = data->player->grid_y * TILE_SIZE
			+ TILE_SIZE / 2;
		data->fov_rad = ((FOV * M_PI) / 180);
		data->proj_dist = (WIN_WIDTH / 2) / tan((FOV * M_PI / 180) / 2);
		data->mlx_ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
		if (!data->mlx_ptr)
			return (1);
		data->textures->image = mlx_new_image(data->mlx_ptr, WIN_WIDTH,
											WIN_HEIGHT);
		if (!data->textures->image)
			return (1);
		mlx_image_to_window(data->mlx_ptr, data->textures->image, 0, 0);
		mlx_key_hook(data->mlx_ptr, handle_key_input, data); // Single key hook
		mlx_loop_hook(data->mlx_ptr, render_game, data);
        mlx_cursor_hook(data->mlx_ptr, cursor_cb, data);
		mlx_loop(data->mlx_ptr);
	}
	return (0);
}
