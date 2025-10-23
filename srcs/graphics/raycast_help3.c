/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_help3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:52:38 by fragarc2          #+#    #+#             */
/*   Updated: 2025/10/23 12:17:59 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int	texer(t_data *data, int tex_x)
{
	tex_x = (int)(get_wall_x(data) * (double)TEXTURE_SIZE);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TEXTURE_SIZE)
		tex_x = TEXTURE_SIZE - 1;
	if ((data->player->side == 0 && data->player->ray_dir_x < 0)
		|| (data->player->side == 1 && data->player->ray_dir_y > 0))
		tex_x = TEXTURE_SIZE - tex_x - 1;
	return (tex_x);
}

int	texturer(t_data *data, int i, int tex_x, int *column_drawn)
{
	while (i < TEXTURE_SIZE)
	{
		data->player->side = set_side(data);
		if (data->map->map[data->player->map_y][data->player->map_x] == '0')
			continue ;
		vector_help(data);
		tex_x = texer(data, tex_x);
		draw_texture(data, column_drawn, tex_x);
		if (data->map->map[data->player->map_y][data->player->map_x] == '1')
			break ;
		i++;
	}
	return (tex_x);
}

t_doors	*find_door(t_doors **array, int map_y, int map_x)
{
	ssize_t	i;
	t_doors	*door;

	i = 0;
	while (array[i])
	{
		if (array[i]->coords[0] == map_y && array[i]->coords[1] == map_x)
		{
			door = array[i];
			return (door);
		}
		i++;
	}
	return (NULL);
}

void	dooring_help(t_data *data, int *column_drawn, int tex_x)
{
	data->tex->color = get_texel_color(data->map->door_bot,
			tex_x, data->tex->tex_y - data->tex->open_px);
	if (data->tex->color != -16777216)
	{
		my_mlx_pixel_put(data->image, data->tex->x,
			data->tex->y, data->tex->color);
		column_drawn[data->tex->y] = 1;
	}
}

void	dooring(t_data *data, int tex_x, int *column_drawn)
{
	data->tex->tex_y = (int)data->tex->tex_pos;
	data->tex->tex_pos += data->tex->step;
	limit(data->tex->tex_y, TEXTURE_SIZE);
	data->tex->drew = 0;
	if (data->tex->tex_y < TEXTURE_SIZE - data->tex->open_px)
	{
		data->tex->color = get_texel_color(data->map->door_top,
				tex_x, data->tex->tex_y + data->tex->open_px);
		if (data->tex->color != -16777216)
		{
			my_mlx_pixel_put(data->image, data->tex->x, data->tex->y,
				data->tex->color);
			column_drawn[data->tex->y] = 1;
			data->tex->drew = 1;
		}
	}
	if (!data->tex->drew && data->tex->tex_y >= data->tex->open_px)
	{
		dooring_help(data, column_drawn, tex_x);
	}
}
