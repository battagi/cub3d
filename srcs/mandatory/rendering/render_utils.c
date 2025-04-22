/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:00:20 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/22 15:29:10 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/render.h"

t_wall_rs	assign_wall_rs(float wall_height, t_rays *ray, mlx_texture_t *txt)
{
	t_wall_rs	ret;

	ret.wall_top = (WIN_HEIGHT / 2) - (wall_height / 2);
	ret.wall_bot = (WIN_HEIGHT / 2) + (wall_height / 2);
	if (ret.wall_top < 0)
		ret.min_top = 0;
	else
		ret.min_top = ret.wall_top;
	if (ret.wall_bot > WIN_HEIGHT)
		ret.max_bot = WIN_HEIGHT;
	else
		ret.max_bot = ret.wall_bot;
	if (ray->is_horz)
		ret.tex_x = (((int)(ray->horz_v.xintercept) % TILE_SIZE) 
				* txt->width) / TILE_SIZE;
	else
		ret.tex_x = (((int)(ray->vert_v.yintercept) % TILE_SIZE) 
				* txt->width) / TILE_SIZE;
	ret.tex_y = 0;
	return (ret);
}

uint32_t	grab_color(mlx_texture_t *txt, t_wall_rs wall)
{
	uint32_t	color;
	int			index;

	index = (wall.tex_y * txt->width + wall.tex_x) * txt->bytes_per_pixel;
	color = (txt->pixels[index] << 24) | (txt->pixels[index + 1] << 16) 
		| (txt->pixels[index + 2] << 8) | txt->pixels[index + 3];
	return (color);
}

void	render_fl_cl(t_game *data)
{
	uint32_t	ceiling_color;
	uint32_t	floor_color;
	int			i;
	int			j;

	ceiling_color = get_color(data->textures->ceiling);
	floor_color = get_color(data->textures->floor);
	i = 0;
	while (i < WIN_HEIGHT / 2)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			mlx_put_pixel(data->textures->image, j, i, ceiling_color);
		i++;
	}
	i = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			mlx_put_pixel(data->textures->image, j, i, floor_color);
		i++;
	}
}

uint32_t	get_color(int *rgb)
{
	uint32_t	ret;

	ret = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | rgb[3];
	return (ret);
}

// u_int8_t	*get_txtbuff(t_txts *txts, char txt)
// {
// 	if (txt == 'N')
// 		return (txts->north_txt->pixels);
// 	if (txt == 'S')
// 		return (txts->south_txt->pixels);
// 	if (txt == 'E')
// 		return (txts->east_txt->pixels);
// 	if (txt == 'W')
// 		return (txts->west_txt->pixels);
// 	return (NULL);
// }
