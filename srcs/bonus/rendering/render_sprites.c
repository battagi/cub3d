/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:21:37 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/19 21:51:13 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/render.h"
#include "../../../includes/cub3d.h"

void	render_spx(t_game *data, int i, int j, t_sprite_vars vars)
{
	if (data->rays[i].is_horz && data->sprites[vars.pos]->dist
		<= data->rays[i].hdist && vars.color != 0xFF00DDFF)
		mlx_put_pixel(data->textures->image, i, j
			+ data->sprites[vars.pos]->height, vars.color);
	else if (!data->rays[i].is_horz && data->sprites[vars.pos]->dist
		<= data->rays[i].vdist && vars.color != 0xFF00DDFF)
		mlx_put_pixel(data->textures->image, i, j
			+ data->sprites[vars.pos]->height, vars.color);
}

void	render_sprites(t_game *data, t_sprite_vars vars, int pos)
{
	int	i;
	int	j;

	i = vars.sp_left_pos;
	while (i < vars.sp_right_pos)
	{
		vars.tex_offsetx = (i - vars.sp_left_pos + (data->sprites[pos]->width
					- (vars.sp_right_pos - vars.sp_left_pos)) / 2)
			* (vars.tex_width / data->sprites[pos]->width);
		j = vars.sp_top_pos;
		while (j < vars.sp_bot_pos)
		{
			vars.tex_offsety = (j + (data->sprites[pos]->height / 2)
					- (WIN_HEIGHT / 2)) * (vars.tex_height
					/ data->sprites[pos]->height);
			vars.color = grab_spc(data, vars);
			vars.pos = pos;
			if (i > 0 && i < WIN_WIDTH && j
				+ data->sprites[pos]->height > 0
				&& j + data->sprites[pos]->height < WIN_HEIGHT)
				render_spx(data, i, j, vars);
			j++;
		}
		i++;
	}
}

void	handle_sprites(t_game *data)
{
	int	i;

	find_vsbl_sprites(data);
	sort_sprites(data);
	i = 0;
	while (i < data->key_count)
	{
		if (data->sprites[i]->is_vsbl && !data->sprites[i]->collected)
		{
			data->sprites[i]->vars = assign_sprite_vars(data, i);
			render_sprites(data, data->sprites[i]->vars, i);
		}
		else
		{
			data->sprites[i]->height = 0;
			data->sprites[i]->width = 0;
		}
		i++;
	}
}
