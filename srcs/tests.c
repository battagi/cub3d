#include "../includes/cub3d.h"
#include<stdio.h>
void	print_textures(t_txts *textures)
{
	if (textures->north)
		printf("North Texture: %s\n", textures->north);
	if (textures->south)
		printf("South Texture: %s\n", textures->south);
	if (textures->west)
		printf("West Texture: %s\n", textures->west);
	if (textures->east)
		printf("East Texture: %s\n", textures->east);
	printf("Floor Color: %d, %d, %d\n", textures->floor[0], textures->floor[1],
		textures->floor[2]);
	printf("Ceiling Color: %d, %d, %d\n", textures->ceiling[0],
		textures->ceiling[1], textures->ceiling[2]);
}
void print_map(t_game *data)
{
    int i = 0;
    while (data->map[i])
    {
        printf("%s\n", data->map[i]);
        i++;
    }
}