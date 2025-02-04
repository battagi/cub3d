/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abattagi <abattagi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:56:36 by abattagi          #+#    #+#             */
/*   Updated: 2025/01/28 11:50:33 by abattagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		dst[j] = src[i];
		if (src[i] == '\t')
		{
			k = j;
			while (k < j + 4)
			{
				dst[k] = ' ';
				k++;
			}
			j = k - 1;
		}
		i++;
		j++;
	}
	dst[j] = '\0';
}

// made some changes here!
int	check_buff(char *buff)
{
	int	i;
	int	f;

	i = 0;
	f = 1;
	while (buff[i] == ' ' || buff[i] == '\t')
		i++;
	while (buff[i])
	{
		if (buff[i] != '1' || buff[i] != ' ')
			f = 0;
	}
	return (f);
}

bool	skip_eline(char *buff)
{
	int		i;
	bool	ret;

	i = 0;
	ret = false;
	while (buff[i] == ' ' || buff[i] == '\t')
		i++;
	if (buff[i] == '\n')
		return (true);
	while (buff[i])
	{
		if (buff[i] != '1' && buff[i] != '\n' && buff[i] != ' '
			&& buff[i] != '0' && buff[i] != 'N' && buff[i] != 'W'
			&& buff[i] != 'S' && buff[i] != 'E')
			ret = true;
		i++;
	}
	return (ret);
}

int	count_map_lines(int fd)
{
	int		c;
	int		f;
	int		i;
	char	*buff;

	buff = get_next_line(fd);
	c = 1;
	while (buff && skip_eline(buff))
	{
		free(buff);
		buff = get_next_line(fd);
	}
	while (buff)
	{
		if (buff[0] == '\0')
			break ;
		c++;
		free(buff);
		buff = get_next_line(fd);
	}
	close(fd);
	return (c);
}

char	*spaces_str(int len, int max)
{
	int		i;
	int		diff;
	char	*ret;

	i = -1;
	diff = max - len;
	ret = (char *)malloc(diff + 1);
	if (!ret)
		return (NULL);
	while (++i < diff)
		ret[i] = ' ';
	ret[diff] = '\0';
	return (ret);
}

void	append_spaces(char **map, int max_len)
{
	int		i;
	char	*buff;
	char	*buff2;

	i = 0;
	while (map[i])
	{
		buff = NULL;
		if (ft_strlen(map[i]) < max_len)
		{
			buff2 = spaces_str(ft_strlen(map[i]), max_len);
			buff = ft_strjoin(map[i], buff2);
		}
		if (buff)
		{
			free(buff2);
			free(map[i]);
			map[i] = buff;
		}
		i++;
	}
}

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
		data->map[j] = ft_strtrim(data->map[j], "\n");
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
	buff = ft_strtrim(buff, " \t");
	while (buff[++j])
	{
		if (buff[j] != ' ' && buff[j] != '1')
			err_func(data);
	}
	free(buff);
	j = -1;
	buff = ft_strdup(data->map[len - 1]);
	buff = ft_strtrim(buff, " \t");
	while (buff[++j])
	{
		if (buff[j] != ' ' && buff[j] != '1')
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
		buff = ft_strtrim(buff, " ");
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
		{
			if (map[j][i] != '0' && map[j][i] != '1' && map[j][i] != ' '
				&& map[j][i] != 'N' && map[j][i] != 'S' && map[j][i] != 'E'
				&& map[j][i] != 'W')
				err_func(data);
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E'
				|| map[j][i] == 'W')
			{
				data->pov = map[j][i];
				c++;
			}
		}
	}
	if (c != 1)
		err_func(data);
}

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
					if(!surrounded_player(data, j, i, len))
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
}
