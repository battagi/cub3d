/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vdist_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:02:48 by abattagi          #+#    #+#             */
/*   Updated: 2025/04/22 16:50:35 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/parsing.h"

//  if (data->door_key == true)
// 			{
// 				dst = calcul_dist(data->player->pos_x, data->player->pos_y,
// 						ray->vert_v.xintercept, ray->vert_v.yintercept);
// 				printf("%f\n", dst);
// 				if (data->map[(int)ray->vwallhity][(int)ray->vwallhitx] == 'D'
// 					&& dst <= 50)
// 				{
// 					data->map[(int)ray->vwallhity][(int)ray->vwallhitx] = 'd';
// 					data->door_key = false;
// 				}
// 			}

void	check_v(float dst, t_game *data, int i, int j)
{
	if (data->map[i][j] == 'D')
	{
		data->rays->is_door = true;
		if (data->door_key == true && dst <= 100)
		{
			printf("close\n");
			data->map[i][j] = 'd';
			data->door_key = false;
		}
	}
}