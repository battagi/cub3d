/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:56:36 by abattagi          #+#    #+#             */
/*   Updated: 2025/03/26 12:08:15 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

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
