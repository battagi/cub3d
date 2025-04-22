/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:22:10 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/22 16:34:43 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/parsing.h"

void	open_all_txts(int *fd, t_txts *textures)
{
	fd[0] = open(textures->north, O_RDONLY);
	fd[1] = open(textures->south, O_RDONLY);
	fd[2] = open(textures->east, O_RDONLY);
	fd[3] = open(textures->west, O_RDONLY);
	fd[4] = open(textures->key[0], O_RDONLY);
	fd[5] = open(textures->key[1], O_RDONLY);
	fd[6] = open(textures->key[2], O_RDONLY);
	fd[7] = open(textures->key[3], O_RDONLY);
	fd[8] = open(textures->key[4], O_RDONLY);
	fd[9] = open(textures->door, O_RDONLY);

}

int	check_chars(t_game *data, char **map, int i, int j)
{
	int	ret;

	ret = 0;
	if (map[j][i] != '0' && map[j][i] != '1' && map[j][i] != ' '
		&& map[j][i] != 'N' && map[j][i] != 'S' && map[j][i] != 'E'
		&& map[j][i] != 'W' && map[j][i] != 'K' && map[j][i] != 'd'
		&& map[j][i] != 'D')
		err_func(data);
	if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E'
		|| map[j][i] == 'W')
	{
		data->pov = map[j][i];
		ret++;
	}
	if (map[j][i] == 'K')
		data->key_count++;
	return (ret);
}

t_sprites	*add_sprite(int i, int j)
{
	t_sprites	*ret;

	ret = (t_sprites *)malloc(sizeof(t_sprites));
	ret->pos_x = j * TILE_SIZE + (TILE_SIZE / 2);
	ret->pos_y = i * TILE_SIZE + (TILE_SIZE / 2);
	ret->dist = -1;
	ret->height = -1;
	ret->is_vsbl = false;
	ret->collected = false;
	return (ret);
}

t_sprites	**parse_sprites(t_game *data, char **map)
{
	t_sprites	**ret;
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	k = 0;
	ret = (t_sprites **)malloc(sizeof(t_sprites *) * (data->key_count + 1));
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'K')
			{
				ret[k] = add_sprite(i, j);
				k++;
			}
			j++;
		}
		i++;
	}
	ret[k] = NULL;
	return (ret);
}
