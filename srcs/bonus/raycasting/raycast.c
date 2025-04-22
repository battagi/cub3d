/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:53:30 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/03/26 12:08:15 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

char	locate_wall(t_rays *ray, t_game *data)
{
	if (ray->is_horz && ray->vert_v.yintercept < data->player->pos_y)
		return ('N');
	else if (ray->is_horz && ray->vert_v.yintercept >= data->player->pos_y)
		return ('S');
	else if (!ray->is_horz && ray->horz_v.xintercept >= data->player->pos_x)
		return ('E');
	else if (!ray->is_horz && ray->horz_v.xintercept < data->player->pos_x)
		return ('W');
	return ('F');
}

void	cast_rays(t_game *data)
{
	float	ang;
	int		i;

	ang = data->player->dir - ((FOV / 2) * (M_PI / 180));
	ang = normalize_angle(ang);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		data->rays[i].ang = ang;
		data->rays[i].hdist = INT_MAX;
		data->rays[i].vdist = INT_MAX;
		calculate_hdist(data, &data->rays[i]);
		calculate_vdist(data, &data->rays[i]);
		if (data->rays[i].hdist < data->rays[i].vdist)
			data->rays[i].is_horz = true;
		else
			data->rays[i].is_horz = false;
		data->rays[i].wall_txt = locate_wall(&data->rays[i], data);
		ang += ((FOV * M_PI) / 180) / WIN_WIDTH;
		ang = normalize_angle(ang);
	}
}
