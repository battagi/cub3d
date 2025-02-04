/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:38:10 by abattagi          #+#    #+#             */
/*   Updated: 2025/02/04 15:48:55 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

#define COLOR_WALL 0xFF6347     // Green
#define COLOR_FLOOR 0x00FFFFFF  // Blue
#define COLOR_PLAYER 0xFF91D2FF // Pink

void	player_movement(t_game *data)
{
	double new_x, new_y;
	int grid_x, grid_y;
	if (data->player->move_up)
	{
		new_x = data->player->pos_x + cos(data->player->dir) * 3;
		new_y = data->player->pos_y + sin(data->player->dir) * 3;
		grid_x = (int)(new_x / data->square_size);
		grid_y = (int)(new_y / data->square_size);
		if (grid_x >= 0 && grid_x < data->map_width && grid_y >= 0
			&& grid_y < data->map_height && data->map[grid_y][grid_x] != '1')
		{
			data->player->pos_x = new_x;
			data->player->pos_y = new_y;
		}
	}
	if (data->player->move_down)
	{
		new_x = data->player->pos_x - cos(data->player->dir) * 3;
		new_y = data->player->pos_y - sin(data->player->dir) * 3;
		grid_x = (int)(new_x / data->square_size);
		grid_y = (int)(new_y / data->square_size);
		if (grid_x >= 0 && grid_x < data->map_width && grid_y >= 0
			&& grid_y < data->map_height && data->map[grid_y][grid_x] != '1')
		{
			data->player->pos_x = new_x;
			data->player->pos_y = new_y;
		}
	}
	if (data->player->move_left)
	{
		new_x = data->player->pos_x + cos(data->player->dir - M_PI_2) * 3;
		new_y = data->player->pos_y + sin(data->player->dir - M_PI_2) * 3;
		grid_x = (int)(new_x / data->square_size);
		grid_y = (int)(new_y / data->square_size);
		if (grid_x >= 0 && grid_x < data->map_width && grid_y >= 0
			&& grid_y < data->map_height && data->map[grid_y][grid_x] != '1')
		{
			data->player->pos_x = new_x;
			data->player->pos_y = new_y;
		}
	}
	if (data->player->move_right)
	{
		new_x = data->player->pos_x + cos(data->player->dir + M_PI_2) * 3;
		new_y = data->player->pos_y + sin(data->player->dir + M_PI_2) * 3;
		grid_x = (int)(new_x / data->square_size);
		grid_y = (int)(new_y / data->square_size);
		if (grid_x >= 0 && grid_x < data->map_width && grid_y >= 0
			&& grid_y < data->map_height && data->map[grid_y][grid_x] != '1')
		{
			data->player->pos_x = new_x;
			data->player->pos_y = new_y;
		}
	}
}

void	draw_square_border(mlx_image_t *image, int x, int y, int size)
{
	int			i;
	uint32_t	border_color;

	border_color = 0x00000000;
	for (i = 0; i < size; i++)
	{
		mlx_put_pixel(image, x + i, y, border_color);
		mlx_put_pixel(image, x + i, y + size - 1, border_color);
		mlx_put_pixel(image, x, y + i, border_color);
		mlx_put_pixel(image, x + size - 1, y + i, border_color);
	}
}

void	draw_square(mlx_image_t *image, int x, int y, int size, uint32_t color)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			mlx_put_pixel(image, x + i, y + j, color);
	}
	draw_square_border(image, x, y, size);
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
            mlx_put_pixel(image, center_x + i, center_y + y, color);
            mlx_put_pixel(image, center_x + i, center_y - y, color);
            i++;
        }
        i = -y;
        while (i <= y)
        {
            mlx_put_pixel(image, center_x + i, center_y + x, color);
            mlx_put_pixel(image, center_x + i, center_y - x, color);
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
		x = 0;
		while (data->map[y][x])
			x++;
		if (x > data->map_width)
			data->map_width = x;
		y++;
	}
	data->map_height = y;
}

void	draw_map(t_game *data)
{
	uint32_t	color;

	int x, y;
	for (y = 0; y < data->map_height; y++)
	{
		for (x = 0; x < data->map_width; x++)
		{
			if (x < (int)ft_strlen(data->map[y]) && data->map[y][x] == '1')
				color = COLOR_WALL;
			else
				color = COLOR_FLOOR;
			draw_square(data->textures->image, x * data->square_size, y
				* data->square_size, data->square_size, color);
		}
	}
	draw_circle(data->textures->image, data->player->pos_x, data->player->pos_y,
		5, COLOR_PLAYER);
}

void	render_game(void *param)
{
	t_game	*data;

	data = (t_game *)param;
	player_movement(data);
	ft_memset(data->textures->image->pixels, 0, data->textures->image->width
		* data->textures->image->height * sizeof(uint32_t));
	draw_map(data);
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
				data->player->dir = 3 * M_PI_2;
				data->player->dir = 3 * M_PI_2;
				data->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	main(int ac, char **av)
{
	t_game *data;

	if (ac == 2 && av[1])
	{
		data = parse_textures(av[1]);
		if (!data)
			return (1);

		get_map_size(data);
		player_position(data);
		data->square_size = calculate_square_size(data);
		data->player->pos_x = data->player->grid_x * data->square_size
			+ data->square_size / 2;
		data->player->pos_y = data->player->grid_y * data->square_size
			+ data->square_size / 2;

		data->mlx_ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
		if (!data->mlx_ptr)
			return (1);

		data->textures->image = mlx_new_image(data->mlx_ptr, WIN_WIDTH,
				WIN_HEIGHT);
		if (!data->textures->image)
			return (1);

		mlx_image_to_window(data->mlx_ptr, data->textures->image, 0, 0);
		mlx_key_hook(data->mlx_ptr, release_key, data);
		mlx_key_hook(data->mlx_ptr, move_player, data);
		mlx_loop_hook(data->mlx_ptr, render_game, data);
		mlx_loop(data->mlx_ptr);
	}
	return (0);
}
