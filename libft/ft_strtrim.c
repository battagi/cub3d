/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:35:46 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/01/11 01:55:28 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_check(char const *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	char	*trimmed;
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	if (start == end)
		return (ft_strdup (""));
	while (ft_check(set, s1[start]))
		start++;
	while (ft_check(set, s1[end - 1]))
		end--;
	trimmed = ft_substr(s1, start, end - start);
	free(s1);
	return (trimmed);
}
