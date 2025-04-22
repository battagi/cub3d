/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:18:30 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/15 18:52:13 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	check_dupped_textures(char **txts)
{
	int	i;
	int	j;

	i = 0;
	while (i < 6)
	{
		j = i + 1;
		while (j < 6)
		{
			if (txts[i] && txts[j] && !ft_strncmp(txts[i], txts[j], 2))
			{
				printf("Error\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

bool	rgb_str_validity(char *rgb)
{
	char	*tmp;
	int		i;

	tmp = rgb + 2;
	i = 0;
	while (tmp[i])
	{
		while (tmp[i] == ' ')
			i++;
		if (!ft_isdigit(tmp[i]) && tmp[i] != ',')
			return (false);
		i++;
	}
	return (true);
}

bool	count_commas(char *rgb)
{
	int		i;
	int		com_count;
	bool	ret;

	i = 0;
	com_count = 0;
	ret = false;
	while (rgb[i])
	{
		if (rgb[i] == ',')
			com_count++;
		i++;
	}
	if (com_count == 2)
		ret = true;
	return (ret);
}

bool	rgb_check(int *crgb, char *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (crgb[i] > 255 || crgb[i] < 0)
			return (false);
		i++;
	}
	return (count_commas(rgb));
}

bool	valid_color(char *rgb)
{
	int		i;
	int		crgb[3];
	int		com_count;
	int		com_pos;
	char	*tmp;

	i = 0;
	com_count = 0;
	tmp = ft_strdup(rgb + 2);
	while (i < 3)
	{
		com_pos = 0;
		while (tmp[com_pos] && tmp[com_pos] != ',')
			com_pos++;
		if (tmp[com_pos] == ',')
		{
			com_count++;
			tmp[com_pos] = '\0';
		}
		crgb[i] = ft_atoi(tmp);
		com_pos++;
		tmp = tmp + com_pos;
		i++;
	}
	return (rgb_check(crgb, rgb));
}
