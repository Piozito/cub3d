/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:00:02 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/08/26 16:52:09 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void draw_square(void *mlx_ptr, int x, int y, int size, int color)
{
    for (int dy = 0; dy < size; dy++)
        for (int dx = 0; dx < size; dx++)
            my_mlx_pixel_put(mlx_ptr, y + dy, x + dx, color);
}

void draw_circle(void *mlx_ptr, int coords, int radius, int color)
{
    for (int y = -radius; y <= radius; y++)
        for (int x = -radius; x <= radius; x++)
            if (x * x + y * y <= radius * radius)
                my_mlx_pixel_put(mlx_ptr, coords + y, coords + x, color);
}

void draw_line(void *mlx_ptr, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1)
    {
        my_mlx_pixel_put(mlx_ptr, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_circle_outline(void *mlx_ptr, int coords, int radius, int color)
{
    int x = radius;
    int y = 0;
    int err = 1 - x;

    while (x >= y)
    {
        if (coords + x >= 0 && coords + y >= 0)
            my_mlx_pixel_put(mlx_ptr, coords + x, coords + y, color);
        if (coords + y >= 0 && coords + x >= 0)
            my_mlx_pixel_put(mlx_ptr, coords + y, coords + x, color);
        if (coords - y >= 0 && coords + x >= 0)
            my_mlx_pixel_put(mlx_ptr, coords - y, coords + x, color);
        if (coords - x >= 0 && coords + y >= 0)
            my_mlx_pixel_put(mlx_ptr, coords - x, coords + y, color);
        if (coords - x >= 0 && coords - y >= 0)
            my_mlx_pixel_put(mlx_ptr, coords - x, coords - y, color);
        if (coords - y >= 0 && coords - x >= 0)
            my_mlx_pixel_put(mlx_ptr, coords - y, coords - x, color);
        if (coords + y >= 0 && coords - x >= 0)
            my_mlx_pixel_put(mlx_ptr, coords + y, coords - x, color);
        if (coords + x >= 0 && coords - y >= 0)
            my_mlx_pixel_put(mlx_ptr, coords + x, coords - y, color);
        y++;
        if (err < 0)
            err += 2 * y + 1;
        else
        {
            x--;
            err += 2 * (y - x) + 1;
        }
    }
}

void	draw_cone(t_data *data, int minimap_radius, int coords)
{
	float	cone_angle;
	float	cone_length;
	float	angle;
	int		ends[2];
	int		i;

	i = 0;
	cone_angle = 3.1416 / 3.0;
	cone_length = minimap_radius / 2;
	while (i <= 60)
	{
		angle = (atan2(data->player->dir_y, data->player->dir_x)) - cone_angle / 2.0 + cone_angle * i / 60;
		ends[0] = coords + (int)(cone_length * cos(angle));
		ends[1] = coords + (int)(cone_length * sin(angle));
		draw_line(data->image, coords, coords, ends[0], ends[1], 0xFF0000);
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	int minimap_radius = 75;
	int coords = 120;
	float zoom = 15.0;
	int dx = -minimap_radius;
	int dy;
	int i = 0;
	int color = 0x222222;

	draw_circle(data->image, coords, 85, 0xFF0000);
	while (dx <= minimap_radius)
	{
		dy = -minimap_radius;
		while (dy <= minimap_radius)
		{
			if (dx*dx + dy*dy > minimap_radius * minimap_radius)
			{
			    dy++;
			    continue;
			}
			int map_iy = (int)(data->player->pos_y + dy / zoom);
			int map_ix = (int)(data->player->pos_x + dx / zoom);
			i = 0;
			while (data->map->map[i])
				i++;
			if (map_iy < 0 || map_iy >= i)
			{
				dy++;	
				continue;
			}
			i = 0;
			while (data->map->map[map_iy][i])
				i++;
			if (map_ix < 0 || map_ix >= i)
			{
				dy++;	
				continue;
			}
			if (data->map->map[map_iy][map_ix] == '1')
				color = 0xCCCCCC;
			else if (data->map->map[map_iy][map_ix] == '2')
				color = 0x00c622;
			else if (data->map->map[map_iy][map_ix] == '0'
				|| data->map->map[map_iy][map_ix] == 'N'
				|| data->map->map[map_iy][map_ix] == 'S'
				|| data->map->map[map_iy][map_ix] == 'W'
				|| data->map->map[map_iy][map_ix] == 'E')
				color = data->map->floor;
			if (coords + dx >= 0 && coords + dy >= 0)
				my_mlx_pixel_put(data->image, coords + dx, coords + dy, color);
			dy++;
		}
		dx++;
	}
	draw_cone(data, minimap_radius, coords);
	draw_circle(data->image, coords, 8, 0xFF0000);
}
