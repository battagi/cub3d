/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:14:46 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/22 17:18:41 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/parsing.h"

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
		err_func(data);
	data->player = (t_player *)malloc(sizeof(t_player));
	if (!data->player)
		err_func(data);
	data->rays = (t_rays *)malloc(sizeof(t_rays) * WIN_WIDTH);
	data->key_count = 0;
	if (!data->rays)
		err_func(data);
	assign_mbrs(data);
	return (data);
}

void	handle_txts(t_game *data, int fd)
{
	char	*txts[11];
	char	*buff;
	int		i;
	int		j;

	j = 0;
	buff = get_next_line(fd);
	while (buff && j < 12)
	{
		buff = ft_strtrim(buff, " \n", 0);
		if (!check_names(buff))
		{
			printf("Error\n");
			exit(1);
		}
		if (buff[0] && buff[0] != '\n')
		{
			txts[j] = ft_strdup(buff);
			j++;
		}
		free(buff);
		buff = get_next_line(fd);
	}
	check_next_buffs_valid(buff, fd);
	fill_txts(data->textures, txts);
}

void	verify_txts(t_game *data)
{
	int		i;
	int		fd[10];
	t_txts	*textures;

	textures = data->textures;
	if (!textures->ceiling || !textures->floor || !textures->north
		|| !textures->south || !textures->east || !textures->west
		|| !textures->key || !textures->door)
		err_func(data);
	open_all_txts(fd, textures);
	i = -1;
	while (++i < 10)
	{
		if (fd[i] < 0)
			err_func(data);
	}
	close_all(fd, 10);
	if (!load_pngs(data, textures))
		err_func(data);
}

void	handle_map(t_game *data, int fd, char *path)
{
	char	*buff;
	int		c;

	c = count_map_lines(fd);
	fd = open(path, O_RDONLY);
	buff = get_next_line(fd);
	while (buff && skip_eline(buff))
	{
		free(buff);
		buff = get_next_line(fd);
	}
	data->map = malloc(sizeof(char *) * (c + 1));
	if (!data->map)
		return ;
	copy_map(fd, buff, data, c);
	close(fd);
	check_map(data, c);
	check_door(data);
}

t_game	*parse_data(char *path)
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
	verify_txts(data);
	handle_map(data, fd, path);
	get_map_size(data);
	player_position(data);
	return (data);
}
