/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_calcul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:28:40 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/15 20:20:58 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
#include "../../../includes/parsing.h"

float	calcul_dist(float x1, float y1, float x2, float y2)
{
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

t_vars	assign_hvars(t_rays	*ray, t_game *data, float ang)
{
	t_vars	vars;

	vars.yintercept = (int)data->player->pos_y / TILE_SIZE;
	vars.yintercept *= TILE_SIZE;
	if (ang_down(ang))
		vars.yintercept += TILE_SIZE;
	vars.xintercept = (int)data->player->pos_x + 
		(vars.yintercept - (int)data->player->pos_y) / tan(ang);
	vars.ystep = TILE_SIZE;
	if (vars.ystep > 0 && ang_up(ang))
		vars.ystep *= -1;
	vars.xstep = vars.ystep / tan(ang);
	if (vars.xstep > 0 && ang_to_left(ang))
		vars.xstep *= -1;
	if (vars.xstep < 0 && ang_to_right(ang))
		vars.xstep *= -1;
	if (ang_up(ang))
		vars.yintercept--;
	ray->hwallhitx = vars.xintercept / TILE_SIZE;
	ray->hwallhity = vars.yintercept / TILE_SIZE;
	return (vars);
}

t_vars	assign_vvars(t_rays *ray, t_game *data, float ang)
{
	t_vars	vars;

	vars.xintercept = (int)data->player->pos_x / TILE_SIZE;
	vars.xintercept *= TILE_SIZE;
	if (ang_to_right(ang))
		vars.xintercept += TILE_SIZE;
	vars.yintercept = (int)data->player->pos_y + 
		(vars.xintercept - (int)data->player->pos_x) * tan(ang);
	vars.xstep = TILE_SIZE;
	if (ang_to_left(ang) && vars.xstep > 0)
		vars.xstep *= -1;
	vars.ystep = vars.xstep * tan(ang);
	if (vars.ystep > 0 && ang_up(ang))
		vars.ystep *= -1;
	if (vars.ystep < 0 && ang_down(ang))
		vars.ystep *= -1;
	if (ang_to_left(ang))
		vars.xintercept--;
	ray->vwallhitx = vars.xintercept / TILE_SIZE;
	ray->vwallhity = vars.yintercept / TILE_SIZE;
	return (vars);
}

void	calculate_hdist(t_game *data, t_rays *ray)
{
	ray->horz_v = assign_hvars(ray, data, ray->ang);
	while (ray->hwallhitx >= 0 && ray->hwallhity >= 0
		&& ray->hwallhitx < data->map_width 
		&& ray->hwallhity < data->map_height)
	{
		if (ray->hwallhitx >= 0 && ray->hwallhity >= 0
			&& ray->hwallhitx < data->map_width 
			&& ray->hwallhity < data->map_height
			&& data->map[(int)ray->hwallhity]
			[(int)ray->hwallhitx] == '1')
		{
			if (ang_up(ray->ang))
				ray->horz_v.yintercept++;
			ray->hdist = calcul_dist(data->player->pos_x, data->player->pos_y,
					ray->horz_v.xintercept, ray->horz_v.yintercept)
				* cos(ray->ang - data->player->dir);
			break ;
		}
		ray->horz_v.xintercept += ray->horz_v.xstep;
		ray->horz_v.yintercept += ray->horz_v.ystep;
		ray->hwallhitx = ray->horz_v.xintercept / TILE_SIZE;
		ray->hwallhity = ray->horz_v.yintercept / TILE_SIZE;
	}
}

void	calculate_vdist(t_game *data, t_rays *ray)
{
	ray->vert_v = assign_vvars(ray, data, ray->ang);
	while (ray->vwallhitx >= 0 && ray->vwallhity >= 0
		&& ray->vwallhitx < data->map_width 
		&& ray->vwallhity < data->map_height)
	{
		if (ray->vwallhitx >= 0 && ray->vwallhity >= 0
			&& ray->vwallhitx < data->map_width 
			&& ray->vwallhity < data->map_height
			&& data->map[(int)ray->vwallhity]
			[(int)ray->vwallhitx] == '1')
		{
			if (ang_to_left(ray->ang))
				ray->vert_v.xintercept++;
			ray->vdist = calcul_dist(data->player->pos_x, data->player->pos_y,
					ray->vert_v.xintercept, ray->vert_v.yintercept)
				* cos(ray->ang - data->player->dir);
			break ;
		}
		ray->vert_v.xintercept += ray->vert_v.xstep;
		ray->vert_v.yintercept += ray->vert_v.ystep;
		ray->vwallhitx = ray->vert_v.xintercept / TILE_SIZE;
		ray->vwallhity = ray->vert_v.yintercept / TILE_SIZE;
	}
}
