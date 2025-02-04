/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:20:18 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/01/28 09:56:51 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"

void	fill_txts(t_txts *textures, char **paths)
{
	int	i;

	i = 0;
	while (i < 6)
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
	}
	free_txts(paths);
}

int	*extract_color(char *rgb)
{
	int	*ret;

	ret = NULL;
	if (rgb && rgb_str_validity(rgb) && valid_color(rgb))
		ret = assign_color(rgb);
	else
	{
		printf("Error\n");
		exit(1);
	}
	return (ret);
}

int	*assign_color(char *rgb)
{
	int	i;
	int	*crgb;
	int	com_pos;

	i = 0;
	crgb = (int *)malloc(sizeof(int) * 3);
	rgb = rgb + 2;
	if (!crgb)
	{
		printf("Error\n");
		return (NULL);
	}
	while (i < 3)
	{
		com_pos = 0;
		while (rgb[com_pos] && rgb[com_pos] != ',')
			com_pos++;
		if (rgb[com_pos] == ',')
			rgb[com_pos] = '\0';
		crgb[i] = ft_atoi(rgb);
		com_pos++;
		rgb = rgb + com_pos;
		i++;
	}
	return (crgb);
}

bool	check_names(char *buff)
{
	if (!ft_strncmp("NO ", buff, 3) || !ft_strncmp("SO ", buff, 3)
		|| !ft_strncmp("WE ", buff, 3) || !ft_strncmp("EA ", buff, 3))
		return (true);
	if (!ft_strncmp("F ", buff, 2) || !ft_strncmp("C ", buff, 2) || !buff[0])
		return (true);
	return (false);
}

int	check_line(char *buff)
{
	int	i;

	i = 0;
	if (!buff)
	{
		printf("Error: Buffer is NULL\n");
		return (0);
	}
	while (buff[i])
	{
		if (buff[i] == '1')
			return (1);
		else if (buff[i] != ' ' && buff[i] != '\n' && buff[i] != '\t')
		{
			printf("Error33: Invalid character '%c'\n", buff[i]);
			exit(1);
		}
		i++;
	}
	return (0);
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

void	handle_txts(t_game *data, int fd)
{
	char	*txts[6];
	char	*buff;
	int		i;
	int		j;

	j = 0;
	buff = get_next_line(fd);
	while (buff && j < 6)
	{
		buff = ft_strtrim(buff, " \n");
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
