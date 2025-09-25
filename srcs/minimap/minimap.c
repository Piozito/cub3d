/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:00:02 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/09/25 12:14:48 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	draw_cone(t_data *data)
{
	float	cone[2];
	float	angle;
	int		ends[2];
	int		i;

	i = 0;
	cone[0] = 3.16149 / 3.0;
	cone[1] = MP_RDS / 2.8;
	while (i <= 60)
	{
		angle = atan2(data->player->dir_y, data->player->dir_x) + 45;
		angle -= cone[0] / 2.0 + cone[0] * i / 60;
		ends[0] = MP_CTR + (int)(cone[1] * cos(angle));
		ends[1] = MP_CTR + (int)(cone[1] * sin(angle));
		draw_line(data->image, ends);
		i++;
	}
}

void	draw_minimap_pixel(t_data *data, int count[2], int map[2], int *color)
{
	int	i;

	if (count[0] * count[0] + count[1] * count[1] > MP_RDS * MP_RDS)
		return ;
	map[0] = (int)(data->player->pos_y + count[1] / MP_ZOOM);
	map[1] = (int)(data->player->pos_x + count[0] / MP_ZOOM);
	i = 0;
	while (data->map->map[i])
		i++;
	if (map[0] < 0 || map[0] >= i)
		return ;
	i = 0;
	while (data->map->map[map[0]][i])
		i++;
	if (map[1] < 0 || map[1] >= i)
		return ;
	if (data->map->map[map[0]][map[1]] == '1')
		*color = 0xCCCCCC;
	else if (data->map->map[map[0]][map[1]] == '2')
		*color = 0x00c622;
	else if (data->map->map[map[0]][map[1]] == '0')
		*color = data->map->floor;
	if (MP_CTR + count[0] >= 0 && MP_CTR + count[1] >= 0)
		my_mlx_pixel_put(data->image,
			MP_CTR + count[0], MP_CTR + count[1], *color);
}

void	draw_minimap(t_data *data)
{
	int	count[2];
	int	map[2];
	int	color;

	count[0] = -MP_RDS;
	color = 0x222222;
	draw_circle(data->image, 85, 0x000000);
	while (count[0] <= MP_RDS)
	{
		count[1] = -MP_RDS;
		while (count[1] <= MP_RDS)
		{
			draw_minimap_pixel(data, count, map, &color);
			count[1]++;
		}
		count[0]++;
	}
	draw_cone(data);
	draw_circle(data->image, 8, 0xFF0000);
}
