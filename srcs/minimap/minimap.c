/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:00:02 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/08/12 12:30:54 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void draw_square(void *mlx_ptr, void *win_ptr, int x, int y, int size, int color)
{
    for (int dy = 0; dy < size; dy++)
        for (int dx = 0; dx < size; dx++)
            mlx_pixel_put(mlx_ptr, win_ptr, x + dx, y + dy, color);
}

void draw_circle(void *mlx_ptr, void *win_ptr, int cx, int cy, int radius, int color)
{
    for (int y = -radius; y <= radius; y++)
        for (int x = -radius; x <= radius; x++)
            if (x * x + y * y <= radius * radius)
                mlx_pixel_put(mlx_ptr, win_ptr, cx + x, cy + y, color);
}

void draw_minimap(t_data *data)
{
    int cell_size = 8;
    for (int y = 0; data->map->map[y]; y++)
    {
        for (int x = 0; data->map->map[y][x]; x++)
        {
            int color;
            if (data->map->map[y][x] == '1')
                color = 0xCCCCCC;
            else if (data->map->map[y][x] == '0'
                || data->map->map[y][x] == 'N'
                || data->map->map[y][x] == 'S'
                || data->map->map[y][x] == 'W'
                || data->map->map[y][x] == 'E')
                color = 0x333333;
            else
                continue;
            draw_square(data->mlx_ptr, data->window_ptr, 10 + x * cell_size, 10 + y * cell_size, cell_size, color);
        }
    }
    draw_circle(
        data->mlx_ptr,
        data->window_ptr,
        10 + data->player->map_x * cell_size + cell_size / 2,
        10 + data->player->map_y * cell_size + cell_size / 2,
        cell_size / 3,
        0xFF0000
    );
}