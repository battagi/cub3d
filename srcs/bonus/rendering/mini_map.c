#include "../../../includes/render.h"
#include "../../../includes/cub3d.h"
void	d_s_border(mlx_image_t *image, int x, int y, t_game *data)
{
	uint32_t	border_color;
	int			square_width;
	int			square_height;
	int			i;
	int			j;

	i = 0;
	border_color = 0xFF000000;
	square_width = MINIMAP_SCALE;
	square_height = MINIMAP_SCALE;
	while (i < square_height)
	{
		j = 0;
		while (j < square_width)
		{
			if (i == 0 || i == square_height - 1 || j == 0 || j == square_width
				- 1)
				mlx_put_pixel(image, x + j, y + i, border_color);
			j++;
		}
		i++;
	}
}

void	d_square(mlx_image_t *image, int x, int y, t_game *data,
		uint32_t color)
{
	int	square_width;
	int	square_height;
	int	i;
	int	j;

	i = 0;
	square_width = MINIMAP_SCALE;
	square_height = MINIMAP_SCALE;
	while (i < square_height)
	{
		j = 0;
		while (j < square_width)
		{
			mlx_put_pixel(image, x + j, y + i, color);
			j++;
		}
		i++;
	}
	d_s_border(image, x, y, data);
}
t_increment	ft_steps(int x0, int y0, int x1, int y1)
{
	t_increment	increment;
	float		dx;
	float		dy;
	int			steps;

	dx = x1 - x0;
	dy = y1 - y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	increment.steps = steps;
	increment.x = dx / steps;
	increment.y = dy / steps;
	return (increment);
}

int ft_max(int a , int b)
{
	if (a > b)
		return a;
	else 
		return b;
}
int ft_min(int a , int b)
{
	if (a < b)
		return a;
	else 
		return b;
}
void draw_player_indicator(mlx_image_t *img, int cx, int cy, int r, uint32_t col, t_game *d)
{
    float a = d->player->dir;
    float tip_x = cx + cosf(a) * r, tip_y = cy + sinf(a) * r;
    float lx = cx + cosf(a + 2.0944f) * r/2, ly = cy + sinf(a + 2.0944f) * r/2;
    float rx = cx + cosf(a - 2.0944f) * r/2, ry = cy + sinf(a - 2.0944f) * r/2;

    int min_x = ft_max((int)fminf(fminf(tip_x, lx), rx), 0);
    int max_x = ft_min((int)fmaxf(fmaxf(tip_x, lx), rx), img->width - 1);
    int min_y = ft_max((int)fminf(fminf(tip_y, ly), ry), 0);
    int max_y = ft_min((int)fmaxf(fmaxf(tip_y, ly), ry), img->height - 1);

    float v0x = rx - tip_x, v0y = ry - tip_y;
    float v1x = lx - tip_x, v1y = ly - tip_y;
    float d00 = v0x*v0x + v0y*v0y, d01 = v0x*v1x + v0y*v1y, d11 = v1x*v1x + v1y*v1y;
    float inv = 1.0f / (d00*d11 - d01*d01);

    for (int y = min_y; y <= max_y; y++) {
        float v2y = y - tip_y;
        for (int x = min_x; x <= max_x; x++) {
            float v2x = x - tip_x;
            float d02 = v0x*v2x + v0y*v2y, d12 = v1x*v2x + v1y*v2y;
            float u = (d11*d02 - d01*d12) * inv;
            if (u >= 0 && (d00*d12 - d01*d02) * inv >= 0 && u + (d00*d12 - d01*d02) * inv <= 1)
                mlx_put_pixel(img, x, y, col);
        }
    }
}
void	mini_map(t_game *data)
{
	uint32_t color;
	int offset_x, offset_y;
	int mini_map_x, mini_map_y;
	int player_mini_map_x, player_mini_map_y;
	int x, y;

	y = -1;
	while (++y < MINIMAP_HEIGHT + 30)
	{
		x = -1;
		while (++x < MINIMAP_WIDTH + 30)
			mlx_put_pixel(data->textures->image, x, y, 0xFF101010);
	}
	int player_grid_x = (int)round(data->player->pos_x / 64.0f);
	int player_grid_y = (int)round(data->player->pos_y / 64.0f);
	offset_x = (player_grid_x * MINIMAP_SCALE) - (MINIMAP_WIDTH / 2);
	offset_y = (player_grid_y * MINIMAP_SCALE) - (MINIMAP_HEIGHT / 2);

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			mini_map_x = (x * MINIMAP_SCALE) - offset_x;
			mini_map_y = (y * MINIMAP_SCALE) - offset_y;

			if (mini_map_x >= 0 && mini_map_x < MINIMAP_WIDTH && mini_map_y >= 0
				&& mini_map_y < MINIMAP_HEIGHT)
			{
				if (x < (int)ft_strlen(data->map[y]) && data->map[y][x] == '1')
					color = COLOR_WALL;
				else
					color = COLOR_FLOOR;

				d_square(data->textures->image, mini_map_x, mini_map_y, data,
					color);
			}
			x++;
		}
		y++;
	}
	player_mini_map_x = MINIMAP_WIDTH / 2;
	player_mini_map_y = MINIMAP_HEIGHT / 2;
	draw_player_indicator(data->textures->image, player_mini_map_x,
		player_mini_map_y, 20, COLOR_PLAYER, data);
}