/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_txts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:16:38 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/22 17:14:05 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/parsing.h"

bool	check_ext(char *path)
{
	int	i;

	i = ft_strlen(path) - 4;
	if (!ft_strncmp(path + i, ".cub", 4))
		return (true);
	return (false);
}

void	assign_mbrs(t_game *data)
{
	data->map = NULL;
	data->map_height = 0;
	data->map_width = 0;
	data->sprite_flag = 0;
	data->sprite_counter = 0;
	data->key_collected = 0;
	data->textures->north = NULL;
	data->textures->south = NULL;
	data->textures->west = NULL;
	data->textures->east = NULL;
	data->textures->image = NULL;
	data->textures->floor = NULL;
	data->textures->ceiling = NULL;
	data->player->dir = 0;
	data->player->move_up = false;
	data->player->move_down = false;
	data->player->move_left = false;
	data->player->move_right = false;
	data->door_key = false;
	data->rays->is_door = false;
}

bool	check_names(char *buff)
{
	if (!ft_strncmp("NO ", buff, 3) || !ft_strncmp("SO ", buff, 3)
		|| !ft_strncmp("WE ", buff, 3) || !ft_strncmp("EA ", buff, 3))
		return (true);
	if (!ft_strncmp("F ", buff, 2) || !ft_strncmp("C ", buff, 2)
		|| !ft_strncmp("K ", buff, 2) || !ft_strncmp("D ", buff, 2) || !buff[0])
		return (true);
	return (false);
}

void	check_next_buffs_valid(char *buff, int fd)
{
	if (!buff)
	{
		printf("Error: Initial buffer is NULL\n");
		free(buff);
		exit(1);
	}
	while (buff)
	{
		if (check_line(buff) == 1)
		{
			free(buff);
			return ;
		}
		free(buff);
		buff = get_next_line(fd);
	}
	if (!buff)
	{
		printf("Error: there is no map\n");
		free(buff);
		exit(1);
	}
}

void	fill_txts(t_txts *textures, char **paths)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	textures->key = (char **)malloc(6 * sizeof(char *));
	while (i < 12)
	{
		if (paths[i] && !ft_strncmp(paths[i], "NO", 2))
			textures->north = ft_strdup(paths[i++] + 3);
		else if (paths[i] && !ft_strncmp(paths[i], "SO", 2))
			textures->south = ft_strdup(paths[i++] + 3);
		else if (paths[i] && !ft_strncmp(paths[i], "WE", 2))
			textures->west = ft_strdup(paths[i++] + 3);
		else if (paths[i] && !ft_strncmp(paths[i], "EA", 2))
			textures->east = ft_strdup(paths[i++] + 3);
		else if (!ft_strncmp(paths[i], "F", 1))
			textures->floor = extract_color(paths[i++]);
		else if (!ft_strncmp(paths[i], "C", 1))
			textures->ceiling = extract_color(paths[i++]);
		else if (!ft_strncmp(paths[i], "K", 1))
			textures->key[j++] = ft_strdup(paths[i++] + 2);
		else if (!ft_strncmp(paths[i], "D", 1))
			textures->door = ft_strdup(paths[i++] + 2);
	}
	textures->key[j] = NULL;
	free_txts(paths);
}
