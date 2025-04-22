/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 07:59:54 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/19 21:05:34 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include "cub3d.h"

typedef struct s_wall_rs
{
	float	wall_top;
	float	wall_bot;
	float	min_top;
	float	max_bot;
	float	tex_x;
	float	tex_y;
}		t_wall_rs;

t_wall_rs		assign_wall_rs(float wall_height, t_rays *ray,
					mlx_texture_t *txt);
uint32_t		grab_color(mlx_texture_t *txt, t_wall_rs wall);
void			render_walls(t_game *data);
float			normalize_sprite_ang(float sprite_ang);
void			find_vsbl_sprites(t_game *data);
void			sort_sprites(t_game *data);
t_sprite_vars	assign_sprite_vars(t_game *data, int pos);
uint32_t		grab_spc(t_game *data, t_sprite_vars vars);
void			handle_sprites(t_game *data);
void			render_fl_cl(t_game *data);
uint32_t		get_color(int *rgb);

#endif