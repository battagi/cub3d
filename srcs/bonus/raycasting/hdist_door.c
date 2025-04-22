/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdist_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:02:53 by abattagi          #+#    #+#             */
/*   Updated: 2025/04/22 16:50:17 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/parsing.h"

void	check_h(float dst, t_game *data, int i, int j)
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