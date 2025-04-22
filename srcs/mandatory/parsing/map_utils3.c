/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:31:59 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/03/26 12:14:16 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/parsing.h"

bool	surrounded_zero(t_game *data, int j, int i, int len)
{
	bool	ret;
	char	**map;

	ret = true;
	map = data->map;
	if (j > 0 && map[j - 1][i] != '1' && map[j - 1][i] != '0' && map[j
		- 1][i] != data->pov)
		ret = false;
	if (j < len - 1 && map[j + 1][i] != '1' && map[j + 1][i] != '0' && map[j
		+ 1][i] != data->pov)
		ret = false;
	if (i > 0 && map[j][i - 1] != '1' && map[j][i - 1] != '0' && map[j][i
		- 1] != data->pov)
		ret = false;
	if (i < ft_strlen(map[j]) - 1 && map[j][i + 1] != '1' && map[j][i
		+ 1] != '0' && map[j][i + 1] != data->pov)
		ret = false;
	return (ret);
}

bool	surrounded_player(t_game *data, int j, int i, int len)
{
	bool	ret;
	char	**map;

	ret = true;
	map = data->map;
	if (j > 0 && map[j - 1][i] != '1' && map[j - 1][i] != '0' && map[j
		- 1][i] != data->pov)
		ret = false;
	if (j < len - 1 && map[j + 1][i] != '1' && map[j + 1][i] != '0' && map[j
		+ 1][i] != data->pov)
		ret = false;
	if (i > 0 && map[j][i - 1] != '1' && map[j][i - 1] != '0' && map[j][i
		- 1] != data->pov)
		ret = false;
	if (i < ft_strlen(map[j]) - 1 && map[j][i + 1] != '1' && map[j][i
		+ 1] != '0' && map[j][i + 1] != data->pov)
		ret = false;
	return (ret);
}

void	check_zeros(t_game *data, int len)
{
	int	i;
	int	j;

	j = -1;
	while (data->map[++j])
	{
		i = -1;
		while (data->map[j][++i])
		{
			if (data->map[j][i] == '0')
			{
				if (!surrounded_zero(data, j, i, len))
					err_func(data);
			}
			if (data->map[j][i] == 'N' || data->map[j][i] == 'S'
				|| data->map[j][i] == 'E' || data->map[j][i] == 'W')
			{
				if (!surrounded_player(data, j, i, len))
					err_func(data);
			}
		}
	}
}

void	check_map(t_game *data, int len)
{
	enclosed_hmap(data, len);
	enclosed_vmap(data, len);
	valid_chars(data, data->map);
	check_zeros(data, len);
}

bool	load_pngs(t_game *data, t_txts *txts)
{
	int	i;

	i = -1;
	txts->north_txt = mlx_load_png(txts->north);
	txts->south_txt = mlx_load_png(txts->south);
	txts->east_txt = mlx_load_png(txts->east);
	txts->west_txt = mlx_load_png(txts->west);
	if (!txts->north_txt || !txts->south_txt 
		|| !txts->east_txt || !txts->west_txt)
		return (false);
	return (true);
}
