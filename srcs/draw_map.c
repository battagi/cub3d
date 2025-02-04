/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:27:05 by abattagi          #+#    #+#             */
/*   Updated: 2025/02/04 12:32:25 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// #define COLOR_WALL 0xFF6347     // green
// #define COLOR_FLOOR 0x00FFFFFF  //  blue
// #define COLOR_PLAYER 0xFF91D2FF // pink

// void	draw_square_border(mlx_image_t *image, int x, int y, int size)
// {
// 	int	i;

// 	uint32_t border_color = 0x00000000; // Black border
// 	i = 0;
// 	while (i < size)
// 	{
// 		mlx_put_pixel(image, x + i, y, border_color); // Top border
// 		mlx_put_pixel(image, x + i, y + size - 1, border_color);
// 		// Bottom border
// 		mlx_put_pixel(image, x, y + i, border_color);            // Left border
// 		mlx_put_pixel(image, x + size - 1, y + i, border_color); // Right border
// 		i++;
// 	}
// }
// void	draw_square(mlx_image_t *image, int x, int y, int size, uint32_t color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	// Draw the main square
// 	while (i < size)
// 	{
// 		j = 0;
// 		while (j < size)
// 		{
// 			mlx_put_pixel(image, x + i, y + j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// 	// Draw the border
// 	draw_square_border(image, x, y, size);
// }

// void	draw_circle(mlx_image_t *image, int center_x, int center_y, int radius,
// 		uint32_t color)
// {
// 	int	x;
// 	int	y;
// 	int	err;
// 	int	i;

// 	x = radius;
// 	y = 0;
// 	err = 0;
// 	while (x >= y)
// 	{
// 		// Draw horizontal lines to fill the circle
// 		i = -x;
// 		while (i <= x)
// 		{
// 			mlx_put_pixel(image, center_x + i, center_y + y, color);
// 			mlx_put_pixel(image, center_x + i, center_y - y, color);
// 			i++;
// 		}
// 		i = -y;
// 		while (i <= y)
// 		{
// 			mlx_put_pixel(image, center_x + i, center_y + x, color);
// 			mlx_put_pixel(image, center_x + i, center_y - x, color);
// 			i++;
// 		}
// 		// Update y and error
// 		if (err <= 0)
// 		{
// 			y++;
// 			err += 2 * y + 1;
// 		}
// 		if (err > 0)
// 		{
// 			x--;
// 			err -= 2 * x + 1;
// 		}
// 	}
// }

// int	calculate_square_size(t_game *data)
// {
// 	int	square_size;
// 	int	tile_size_width;
// 	int	tile_size_height;

// 	if (data->map_width == 0 || data->map_height == 0)
// 		return (64); // Default size
// 	tile_size_width = WIN_WIDTH / data->map_width;
// 	tile_size_height = WIN_HEIGHT / data->map_height;
// 	// Use the smaller tile size to ensure the map fits in the window
// 	if (tile_size_width < tile_size_height)
// 		square_size = tile_size_width;
// 	else
// 		square_size = tile_size_height;
// 	return (square_size);
// }

// void	get_map_size(t_game *data)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	x = 0;
// 	data->map_width = 0;
// 	data->map_height = 0;
// 	while (data->map[y])
// 	{
// 		x = 0;
// 		while (data->map[y][x])
// 		{
// 			x++;
// 		}
// 		if (x > data->map_width)
// 			data->map_width = x;
// 		y++;
// 	}
// 	data->map_height = y;
// }

// void	draw_map(t_game *data)
// {
// 	int			x;
// 	int			y;
// 	int			square_size;
// 	uint32_t	color;

// 	get_map_size(data);
// 	square_size = calculate_square_size(data);
// 	y = 0;
// 	printf("%d\n", square_size);
// 	while (data->map[y])
// 	{
// 		x = 0;
// 		while (data->map[y][x])
// 		{
// 			if (data->map[y][x] == '1')
// 				color = COLOR_WALL;
// 			else if (data->map[y][x] == '0')
// 				color = COLOR_FLOOR;
// 			else if (data->map[y][x] == ' ')
// 				color = COLOR_WALL;
// 			else if (data->map[y][x] == 'N')
// 			{
// 				color = COLOR_FLOOR;
// 				printf("x=%d -------------------------------------y =%d\n", x,
// 					y);
// 			}
// 		draw_square(data->textures->image, x * square_size, y * square_size,
// 			square_size, color);
// 		if (data->map[y][x] == 'N')
// 		    draw_circle(data->textures->image, x * square_size + square_size
// 			/ 2,
// 		        y * square_size + square_size / 2, square_size / 4,
// 			COLOR_PLAYER);
// 		x++;
// 	}
// 	y++;
// }
// }
