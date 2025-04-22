/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:20:18 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/03/26 12:11:33 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/parsing.h"

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

int	*assign_color(char *rgb)
{
	int	i;
	int	*crgb;
	int	com_pos;

	i = 0;
	crgb = (int *)malloc(sizeof(int) * 4);
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
	return (crgb[i] = 255, crgb);
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

void	free_txts(char **txts)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (txts[i])
			free(txts[i]);
	}
}

void	close_all(int *fds, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		close(fds[i]);
}
