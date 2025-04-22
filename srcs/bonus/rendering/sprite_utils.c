/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:03:33 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/19 21:34:22 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/render.h"
#include "../../../includes/cub3d.h"

float	normalize_sprite_ang(float sprite_ang)
{
	if (sprite_ang > M_PI)
		sprite_ang -= 2 * M_PI;
	else if (sprite_ang < M_PI * -1)
		sprite_ang += 2 * M_PI;
	sprite_ang = fabs(sprite_ang);
	return (sprite_ang);
}

void	find_vsbl_sprites(t_game *data)
{
	float	sprite_ang;
	int		i;

	sprite_ang = 0;
	i = -1;
	while (++i < data->key_count)
	{
		sprite_ang = data->player->dir - atan2(data->sprites[i]->pos_y
				- data->player->pos_y, data->sprites[i]->pos_x
				- data->player->pos_x);
		sprite_ang = normalize_sprite_ang(sprite_ang);
		if (sprite_ang < data->fov_rad / 2)
		{
			data->sprites[i]->angle = sprite_ang;
			data->sprites[i]->dist = calcul_dist(data->sprites[i]->pos_x,
					data->sprites[i]->pos_y, data->player->pos_x,
					data->player->pos_y) * cos(sprite_ang);
			data->sprites[i]->is_vsbl = true;
		}
		else
		{
			data->sprites[i]->dist = 0;
			data->sprites[i]->is_vsbl = false;
		}
	}
}

void	sort_sprites(t_game *data)
{
	t_sprites	*tmp;
	int			i;
	int			j;

	tmp = NULL;
	i = 0;
	while (i < data->key_count - 1)
	{
		j = i + 1;
		while (j < data->key_count)
		{
			if (data->sprites[j]->dist > data->sprites[i]->dist)
			{
				tmp = data->sprites[i];
				data->sprites[i] = data->sprites[j];
				data->sprites[j] = tmp; 
			}
			j++;
		}
		i++;
	}
}

t_sprite_vars	assign_sprite_vars(t_game *data, int pos)
{
	t_sprite_vars	ret;

	data->sprites[pos]->height = ((TILE_SIZE / data->sprites[pos]->dist)
			* data->proj_dist) / 2;
	data->sprites[pos]->width = data->sprites[pos]->height;
	ret.sp_top_pos = (WIN_HEIGHT / 2) - (data->sprites[pos]->height / 2);
	ret.sp_bot_pos = (WIN_HEIGHT / 2) + (data->sprites[pos]->height / 2);
	if (ret.sp_top_pos < 0)
		ret.sp_top_pos = 0;
	if (ret.sp_bot_pos > WIN_HEIGHT)
		ret.sp_bot_pos = WIN_HEIGHT;
	ret.sp_ang = atan2(data->sprites[pos]->pos_y - data->player->pos_y,
			data->sprites[pos]->pos_x - data->player->pos_x)
		- data->player->dir;
	ret.sp_xpos = tan(ret.sp_ang) * data->proj_dist;
	ret.sp_left_pos = (WIN_WIDTH / 2) + ret.sp_xpos;
	ret.sp_left_pos -= data->sprites[pos]->width / 2;
	ret.sp_right_pos = ret.sp_left_pos + data->sprites[pos]->width;
	if (ret.sp_left_pos < 0)
		ret.sp_left_pos = 0;
	if (ret.sp_right_pos > WIN_WIDTH)
		ret.sp_right_pos = WIN_WIDTH;
	ret.tex_width = data->textures->key_txt[data->sprite_counter / 5]->width;
	ret.tex_height = data->textures->key_txt[data->sprite_counter / 5]->height;
	return (ret);
}

uint32_t	grab_spc(t_game *data, t_sprite_vars vars)
{
	uint32_t	ret;
	int			index;
	int			sp_counter;

	sp_counter = data->sprite_counter / 5;
	index = ((vars.tex_offsety * vars.tex_width) + vars.tex_offsetx)
		* data->textures->key_txt[sp_counter]->bytes_per_pixel;
	ret = (data->textures->key_txt[sp_counter]->pixels[index] << 24)
		| (data->textures->key_txt[sp_counter]->pixels[index + 1] << 16) 
		| (data->textures->key_txt[sp_counter]->pixels[index + 2] << 8)
		| data->textures->key_txt[sp_counter]->pixels[index + 3];
	return (ret);
}
