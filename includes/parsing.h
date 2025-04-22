/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:53:42 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/04/19 21:29:01 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int			check_line(char *buff);
int			*assign_color(char *rgb);
int			*extract_color(char *rgb);
void		free_txts(char **txts);
void		close_all(int *fds, int count);

void		check_dupped_textures(char **txts);
bool		rgb_str_validity(char *rgb);
bool		count_commas(char *rgb);
bool		rgb_check(int *crgb, char *rgb);
bool		valid_color(char *rgb);

bool		check_ext(char *path);
void		assign_mbrs(t_game *data);
bool		check_names(char *buff);
void		check_next_buffs_valid(char *buff, int fd);
void		fill_txts(t_txts *textures, char **paths);

void		open_all_txts(int *fd, t_txts *textures);
int			check_chars(t_game *data, char **map, int i, int j);
t_sprites	*add_sprite(int i, int j);
t_sprites	**parse_sprites(t_game *data, char **map);

int			check_buff(char *buff);
bool		skip_eline(char *buff);
int			count_map_lines(int fd);
char		*spaces_str(int len, int max);
void		append_spaces(char **map, int max_len);

void		copy_map(int fd, char *buff, t_game *data, int len);
void		err_func(t_game *data);
void		enclosed_hmap(t_game *data, int len);
void		enclosed_vmap(t_game *data, int len);
void		valid_chars(t_game *data, char **map);

bool		surrounded_zero(t_game *data, int j, int i, int len);
bool		surrounded_player(t_game *data, int j, int i, int len);
void		check_zeros(t_game *data, int len);
void		check_map(t_game *data, int len);

void		get_map_size(t_game *data);
void		player_position(t_game *data);

#endif