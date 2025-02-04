/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:14:12 by abattagi          #+#    #+#             */
/*   Updated: 2025/02/04 12:21:01 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	player_movement(t_game *data)
// {
// 	double	new_x;
// 	double	new_y;

// 	// Temporary variables to store the new position
// 	new_x = data->player->pos_x;
// 	new_y = data->player->pos_y;
// 	if (data->player->move_up)
// 	{
// 		new_x += cos(data->player->dir) * MOVE_SPEED;
// 		new_y += sin(data->player->dir) * MOVE_SPEED;
// 	}
// 	if (data->player->move_down)
// 	{
// 		new_x -= cos(data->player->dir) * MOVE_SPEED;
// 		new_y -= sin(data->player->dir) * MOVE_SPEED;
// 	}
// 	if (data->player->move_left)
// 	{
// 		new_x += cos(data->player->dir - M_PI_2) * MOVE_SPEED;
// 		new_y += sin(data->player->dir - M_PI_2) * MOVE_SPEED;
// 	}
// 	if (data->player->move_right)
// 	{
// 		new_x += cos(data->player->dir + M_PI_2) * MOVE_SPEED;
// 		new_y += sin(data->player->dir + M_PI_2) * MOVE_SPEED;
// 	}
// 	data->player->pos_x = new_x;
// 	data->player->pos_y = new_y;
// }

// void	player_position(t_game *data)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (data->map[j])
// 	{
// 		i = 0;
// 		while (data->map[j][i])
// 		{
// 			if (data->map[j][i] == 'N' || data->map[j][i] == 'S'
// 				|| data->map[j][i] == 'E' || data->map[j][i] == 'W')
// 			{
// 				data->player->pos_x = i * TILE_SIZE + TILE_SIZE / 2;
// 				data->player->pos_y = j * TILE_SIZE + TILE_SIZE / 2;
// 				if (data->map[j][i] == 'N')
// 					data->player->dir = M_PI / 2; // North
// 				else if (data->map[j][i] == 'S')
// 					data->player->dir = 3 * M_PI / 2; // South
// 				else if (data->map[j][i] == 'E')
// 					data->player->dir = 0; // East
// 				else if (data->map[j][i] == 'W')
// 					data->player->dir = M_PI; // West
// 				data->map[j][i] = '0';
// 				// Clear the player's starting position
// 			}
// 			i++;
// 		}
// 		j++;
// 	}
// }

// void	move_player(struct mlx_key_data keycode, void *param)
// {
// 	t_game	*data;

// 	data = (t_game *)param;
// 	if (keycode.key == 13) // W key
// 	{
// 		data->player->move_up = true;
// 		player_movement(data);
// 		printf("%d\n", keycode.key);
// 	}
// 	else if (keycode.key == 1) // S key
// 	{
// 		data->player->move_down = true;
// 		player_movement(data);
// 		printf("%d\n", keycode.key);
// 	}
// 	else if (keycode.key == 0) // A key
// 	{
// 		data->player->move_left = true;
// 		player_movement(data);
// 		printf("%d\n", keycode.key);
// 	}
// 	else if (keycode.key == 2) // D key
// 	{
// 		data->player->move_right = true;
// 		player_movement(data);
// 		printf("%d\n", keycode.key);
// 	}
// 	else if (keycode.key == 53) // Esc key
// 		exit(0);
// 	return ;
// }

// void	release_key(struct mlx_key_data keycode, void *param)
// {
// 	t_game	*data;

// 	data = (t_game *)param;
// 	if (keycode.key == 13) // W key
// 		data->player->move_up = false;
// 	else if (keycode.key == 1) // S key
// 		data->player->move_down = false;
// 	else if (keycode.key == 0) // A key
// 		data->player->move_left = false;
// 	else if (keycode.key == 2) // D key
// 		data->player->move_right = false;
// }
// void    draw_player(t_game *data)
// {
//     printf("pos_x: %d\n", data->player->pos_x);
//     printf("pos_y: %d\n", data->player->pos_y);
    

//    draw_circle(data->textures->image, data->player->pos_x * 34 + 34 / 2,
//                    data->player->pos_y * 34 + 34 / 2, 34 / 4, COLOR_PLAYER);
// }
// void	render_game(t_game *data)
// {
// 	// Clear the screen
// 	// Draw the map (you need to implement this)
// 	draw_map(data);

// 	// Draw the player (you need to implement this)
// 	draw_player(data);
// 	// Display the frame
// 	mlx_image_to_window(data->mlx_ptr, data->textures->image, 0, 0);
// }
// void	game_loop(void *param)
// {
// 	t_game *data = (t_game *)param;
// 	player_movement(data);
// 	render_game(data);
// }