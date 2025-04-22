/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:31:59 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/22 16:36:43 by abattagi         ###   ########.fr       */
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
		- 1][i] != data->pov && map[j - 1][i] != 'K' && map[j - 1][i] != 'd'
		&& map[j - 1][i] != 'D')
		ret = false;
	if (j < len - 1 && map[j + 1][i] != '1' && map[j + 1][i] != '0' && map[j
		+ 1][i] != data->pov && map[j + 1][i] != 'K' && map[j + 1][i] != 'd'
		&& map[j + 1][i] != 'D')
		ret = false;
	if (i > 0 && map[j][i - 1] != '1' && map[j][i - 1] != '0' && map[j][i
		- 1] != data->pov && map[j][i - 1] != 'K' && map[j][i - 1] != 'd'
		&& map[j][i - 1] != 'D')
		ret = false;
	if (i < ft_strlen(map[j]) - 1 && map[j][i + 1] != '1' && map[j][i
		+ 1] != '0' && map[j][i + 1] != data->pov && map[j][i + 1] != 'K'
		&& map[j][i + 1] != data->pov && map[j][i + 1] != 'd' && map[j][i
		+ 1] != 'D')
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
		- 1][i] != data->pov && map[j - 1][i] != 'K')
		ret = false;
	if (j < len - 1 && map[j + 1][i] != '1' && map[j + 1][i] != '0' && map[j
		+ 1][i] != data->pov && map[j + 1][i] != 'K')
		ret = false;
	if (i > 0 && map[j][i - 1] != '1' && map[j][i - 1] != '0' && map[j][i
		- 1] != data->pov && map[j][i - 1] != 'K')
		ret = false;
	if (i < ft_strlen(map[j]) - 1 && map[j][i + 1] != '1' && map[j][i
		+ 1] != '0' && map[j][i + 1] != data->pov && map[j][i + 1] != 'K')
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
	data->sprites = parse_sprites(data, data->map);
}

bool	load_pngs(t_game *data, t_txts *txts)
{
	int	i;

	i = -1;
	txts->north_txt = mlx_load_png(txts->north);
	txts->south_txt = mlx_load_png(txts->south);
	txts->east_txt = mlx_load_png(txts->east);
	txts->west_txt = mlx_load_png(txts->west);
	txts->door_txt = mlx_load_png(txts->door);
	if (!txts->north_txt || !txts->south_txt || !txts->east_txt
		|| !txts->west_txt || txts->door_txt)
		return (false);
	txts->key_txt = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 5);
	while (++i < 5)
	{
		txts->key_txt[i] = mlx_load_png(txts->key[i]);
		if (!txts->key_txt[i])
			return (false);
	}
	return (true);
}
