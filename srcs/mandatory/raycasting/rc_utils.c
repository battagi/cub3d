/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:27:27 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/03/26 12:09:04 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/parsing.h"

bool	ang_to_right(float ang)
{
	return (ang < M_PI_2 || ang > 3 * M_PI_2);
}

bool	ang_to_left(float ang)
{
	return (ang >= M_PI_2 && ang <= 3 * M_PI_2);
}

bool	ang_up(float ang)
{
	return (ang > M_PI);
}

bool	ang_down(float ang)
{
	return (!ang_up(ang));
}

float	normalize_angle(float ang)
{
	float	ret;

	ret = fmod(ang, 2 * M_PI);
	if (ret < 0)
		ret += 2 * M_PI;
	return (ret);
}
