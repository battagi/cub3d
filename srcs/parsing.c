/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:16:38 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/02/04 11:01:31 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"

bool	check_ext(char *path)
{
	int	i;

	i = ft_strlen(path) - 4;
	if (!ft_strncmp(path + i, ".cub", 4))
		return (true);
	return (false);
}

t_game	*init_data(void)
{
	t_game	*data;

	data = (t_game *)malloc(sizeof(t_game));
	if (!data)
	{
		printf("Error: Memory allocation for game data failed\n");
		return (NULL);
	}
	data->textures = (t_txts *)malloc(sizeof(t_txts));
	if (!data->textures)
	{
		printf("Error: Memory allocation for textures failed\n");
		free(data);
		return (NULL);
	}
	data->textures->north = NULL;
	data->textures->south = NULL;
	data->textures->west = NULL;
	data->textures->east = NULL;
	data->textures->image = NULL;
	data->textures->floor = NULL;
	data->textures->ceiling = NULL;
	data->map = NULL;
	data->map_height = 0;
	data->map_width = 0;
	data->player = (t_player *)malloc(sizeof(t_player));
	if (!data->player)
	{
		printf("Error: Memory allocation for player failed\n");
		free(data->textures);
		free(data);
		return (NULL);
	}
	data->player->dir = 0;
	data->player->move_up = false;
	data->player->move_down = false;
	data->player->move_left = false;
	data->player->move_right = false;
	
	return (data);
}

void	verify_txts(t_txts *textures)
{
	int	i;
	int	fd[4];

	if (!textures->ceiling || !textures->floor || !textures->north
		|| !textures->south || !textures->east || !textures->west)
	{
		printf("Error\n");
		// free_func;
		exit(1);
	}
	i = -1;
	fd[0] = open(textures->north, O_RDONLY);
	fd[1] = open(textures->south, O_RDONLY);
	fd[2] = open(textures->east, O_RDONLY);
	fd[3] = open(textures->west, O_RDONLY);
	while (++i < 4)
	{
		if (fd[i] < 0)
		{
			printf("Error\n");
			// free func to do
			exit(1);
		}
	}
	// close_all func to do
}

t_game	*parse_textures(char *path)
{
	int		fd;
	char	*buff;
	t_game	*data;

	if (!check_ext(path))
	{
		printf("Error\n");
		return (NULL);
	}
	data = init_data();
	fd = open(path, O_RDONLY);
	handle_txts(data, fd);
	verify_txts(data->textures);
	handle_map(data, fd, path);
	close(fd);
	return (data);
}
