/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 07:38:27 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/15 20:23:44 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/render.h"

float	calculate_wheight(t_game *data, int i, mlx_texture_t **txt)
{
	float			ret;

	if (data->rays[i].hdist < data->rays[i].vdist)
		ret = (TILE_SIZE / data->rays[i].hdist) * data->proj_dist;
	else
		ret = (TILE_SIZE / data->rays[i].vdist) * data->proj_dist;
	if (data->rays[i].wall_txt == 'N')
		*txt = data->textures->north_txt;
	if (data->rays[i].wall_txt == 'S')
		*txt = data->textures->south_txt;
	if (data->rays[i].wall_txt == 'W')
		*txt = data->textures->west_txt;
	if (data->rays[i].wall_txt == 'E')
		*txt = data->textures->east_txt;
	return (ret);
}

void	render_walls(t_game *data)
{
	int				i;
	int				j;
	mlx_texture_t	*txt;
	t_wall_rs		wall;

	i = 0;
	while (i < WIN_WIDTH)
	{
		data->rays[i].wall_height = calculate_wheight(data, i, &txt);
		wall = assign_wall_rs(data->rays[i].wall_height, &data->rays[i], txt);
		j = wall.min_top;
		while (j < wall.max_bot)
		{
			wall.tex_y = (int)(((j - wall.wall_top) / data->rays[i].wall_height)
					* txt->height);
			if (i > 0 && i < WIN_WIDTH && j > 0 && j < WIN_HEIGHT)
				mlx_put_pixel(data->textures->image, i, j,
					grab_color(txt, wall));
			j++;
		}
		i++;
	}
}
