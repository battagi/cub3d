/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:53:42 by ouel-bou          #+#    #+#             */
/*   Updated: 2025/01/21 23:20:56 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int		*assign_color(char *rgb);
int		*extract_color(char *rgb);
void	check_dupped_textures(char **txts);
bool	valid_color(char *rgb);
bool	rgb_str_validity(char *rgb);
void	handle_txts(t_game *data, int fd);
void	handle_map(t_game *data, int fd, char *path);
void	free_txts(char **txts);

#endif