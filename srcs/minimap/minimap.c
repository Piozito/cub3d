/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:00:02 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/08/19 13:05:12 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void draw_square(void *mlx_ptr, void *win_ptr, int x, int y, int size, int color)
{
    for (int dy = 0; dy < size; dy++)
        for (int dx = 0; dx < size; dx++)
            mlx_pixel_put(mlx_ptr, win_ptr, y + dy, x + dx, color);
}

void draw_circle(void *mlx_ptr, void *win_ptr, int cx, int cy, int radius)
{
    for (int y = -radius; y <= radius; y++)
        for (int x = -radius; x <= radius; x++)
            if (x * x + y * y <= radius * radius)
                mlx_pixel_put(mlx_ptr, win_ptr, cy + y, cx + x, 0xFF0000);
}

void draw_minimap(t_data *data)
{
    int cell_size = 8;
    for (int x = 0; data->map->map[x]; x++)
    {
        for (int y = 0; data->map->map[x][y]; y++)
        {
            int color;
            if (data->map->map[x][y] == '1')
                color = 0xCCCCCC;
            else if (data->map->map[x][y] == '0'
                || data->map->map[x][y] == 'N'
                || data->map->map[x][y] == 'S'
                || data->map->map[x][y] == 'W'
                || data->map->map[x][y] == 'E')
                color = 0x333333;
            else if(data->map->map[x][y] == '2')
                color = 0x00c622;
            else
                continue;
            draw_square(data->mlx_ptr, data->window_ptr, 10 + x * cell_size, 10 + y * cell_size, cell_size, color);
        }
    }
    draw_circle(
        data->mlx_ptr,
        data->window_ptr,
        10 + (data->player->pos_y - 0.5) * cell_size + cell_size / 2,
        10 + (data->player->pos_x - 0.5) * cell_size + cell_size / 2,
        cell_size / 3
    );
}