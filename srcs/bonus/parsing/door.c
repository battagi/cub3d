/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:36:11 by abattagi          #+#    #+#             */
/*   Updated: 2025/04/22 15:51:32 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/parsing.h"

void	check_door(t_game *data)
{
	int i = 0;
	int j;

	while (data->map[i])
	{
		j = 0;

		while (data->map[i][j])
		{
			if (data->map[i][j] == 'D')
			{
				if (!((data->map[i - 1][j] == '1' && data->map[i + 1][j] == '1')
						|| (data->map[i][j - 1] == '1' && data->map[i][j
							+ 1] == '1')))
					err_func(data);
			}
			j++;
		}
		i++;
	}
}
