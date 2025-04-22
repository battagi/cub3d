/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 23:36:50 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/02/07 18:29:06 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lsize;

	i = 0;
	lsize = ft_strlen(src);
	if (size == 0)
		return (lsize);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (lsize);
}
