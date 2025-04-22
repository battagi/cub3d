/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:33:18 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/22 16:56:28 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/parsing.h"

void	copy_map(int fd, char *buff, t_game *data, int len)
{
	int	j;
	int	l;

	j = 0;
	l = 0;
	while (j < len)
	{
		data->map[j] = malloc(sizeof(char) * (ft_strlen(buff) + 1));
		if (!data->map[j])
			return (free(buff));
		ft_strcpy(data->map[j], buff);
		data->map[j] = ft_strtrim(data->map[j], "\n", 2);
		data->map[j] = ft_strtrim(data->map[j], " \t", 2);
		if (l < ft_strlen(data->map[j]))
			l = ft_strlen(data->map[j]);
		free(buff);
		buff = get_next_line(fd);
		j++;
	}
	data->map[j] = NULL;
	append_spaces(data->map, l);
}

void	err_func(t_game *data)
{
	if (data)
	{
		if (data->textures)
		{
			if (data->textures->north)
				free(data->textures->north);
			if (data->textures->south)
				free(data->textures->south);
			if (data->textures->west)
				free(data->textures->west);
			if (data->textures->east)
				free(data->textures->east);
			if (data->textures->floor)
				free(data->textures->floor);
			if (data->textures->ceiling)
				free(data->textures->ceiling);
			if (data->textures->door)
				free(data->textures->door);
			free(data->textures);
		}
		if (data->map)
			data->map = freemem(data->map);
		free(data);
	}
	printf("Error\n");
	exit(1);
}

void	enclosed_hmap(t_game *data, int len)
{
	int		j;
	char	*buff;

	j = -1;
	buff = ft_strdup(data->map[0]);
	buff = ft_strtrim(buff, " \t", 0);
	while (buff[++j])
	{
		if (buff[j] != ' ' && buff[j] != '1' && buff[j] != 'd'
			&& buff[j] != 'D')
			err_func(data);
	}
	free(buff);
	j = -1;
	buff = ft_strdup(data->map[len - 1]);
	buff = ft_strtrim(buff, " \t", 0);
	while (buff[++j])
	{
		if (buff[j] != ' ' && buff[j] != '1' && buff[j] != '1' && buff[j] != 'd'
			&& buff[j] != 'D')
			err_func(data);
	}
	free(buff);
}

void	enclosed_vmap(t_game *data, int len)
{
	int		j;
	char	*buff;

	j = -1;
	while (++j < len)
	{
		buff = ft_strdup(data->map[j]);
		buff = ft_strtrim(buff, " ", 0);
		if (buff[0] != '1' || buff[ft_strlen(buff) - 1] != '1')
			err_func(data);
		free(buff);
	}
}

void	valid_chars(t_game *data, char **map)
{
	int	i;
	int	j;
	int	c;

	j = -1;
	c = 0;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
			c += check_chars(data, map, i, j);
	}
	if (c != 1)
		err_func(data);
}
