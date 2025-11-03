/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:33:39 by fragarc2          #+#    #+#             */
/*   Updated: 2025/11/03 10:35:41 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	vector_help(t_data *data)
{
	if (data->player->side == 0)
		data->player->perp_wall_dist = fabs((data->player->map_x
					- data->player->pos_x + (1 - data->player->step_x) / 2)
				/ data->player->ray_dir_x);
	else
		data->player->perp_wall_dist = fabs((data->player->map_y
					- data->player->pos_y + (1 - data->player->step_y)
					/ 2) / data->player->ray_dir_y);
	if (data->player->perp_wall_dist < 0.01)
		data->player->perp_wall_dist = 0.01;
	data->player->line_height = (int)(W_H / data->player->perp_wall_dist);
	data->player->draw_start = -data->player->line_height / 2 + W_H / 2;
	data->player->draw_end = data->player->line_height / 2 + W_H / 2;
	if (data->player->draw_start < 0)
		data->player->draw_start = 0;
	if (data->player->draw_end > W_H)
		data->player->draw_end = W_H;
}

int	vectors(void *param)
{
	t_data	*data;
	int		column_drawn[W_H];
	int		i;
	int		tex_x;

	data = (t_data *)param;
	movement_handler(data);
	if (data->player->key_states[5] == 0)
		mlx_mouse_move(data->mlx_ptr, data->window_ptr, W_W / 2, W_H / 2);
	while (data->tex->x < W_W)
	{
		i = 0;
		while (i < W_H)
			column_drawn[i++] = 0;
		i = 0;
		data->player->camera_x = 2 * data->tex->x / (double)W_W - 1;
		helper(data);
		tex_x = texturer(data, i, tex_x, column_drawn);
		do_y(data, column_drawn);
		data->tex->x++;
	}
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->window_ptr,
		data->image->mlx_img, 0, 0);
	return (0);
}

void	pixil(t_data *data, int *column_drawn, int tex_x, t_im *texture)
{
	while (data->tex->y < data->player->draw_end)
	{
		if (data->tex->y < 0 || data->tex->y >= W_H)
		{
			data->tex->y++;
			continue ;
		}
		if (column_drawn[data->tex->y])
		{
			data->tex->tex_pos += data->tex->step;
			data->tex->y++;
			continue ;
		}
		data->tex->tex_y = (int)data->tex->tex_pos;
		limit(data->tex->tex_y, TEXTURE_SIZE);
		data->tex->color = get_texel_color(texture, tex_x, data->tex->tex_y);
		if (data->tex->color != -16777216)
			my_mlx_pixel_put(data->image, data->tex->x,
				data->tex->y, data->tex->color);
		column_drawn[data->tex->y] = 1;
		data->tex->tex_pos += data->tex->step;
		data->tex->y++;
	}
}

void	pixil_door(t_data *data, int *column_drawn, int tex_x)
{
	while (data->tex->y < data->player->draw_end)
	{
		if (data->tex->y < 0 || data->tex->y >= W_H)
		{
			data->tex->y++;
			continue ;
		}
		if (column_drawn[data->tex->y])
		{
			data->tex->tex_pos += data->tex->step;
			data->tex->y++;
			continue ;
		}
		dooring(data, tex_x, column_drawn);
		data->tex->y++;
	}
}

void	draw_texture(t_data *data, int *column_drawn, int tex_x)
{
	int		percent;
	t_im	*texture;
	t_doors	*door;

	draw_limits(data);
	if (data->map->map[data->player->map_y][data->player->map_x] == '2')
	{
		door = find_door(data->map->doors,
				data->player->map_y, data->player->map_x);
		percent = (100 - door->open);
		data->tex->open_px = 0;
		if (percent > 80)
			percent = 80;
		if (data->player->map_y == door->coords[0]
			&& data->player->map_x == door->coords[1])
			data->tex->open_px = percent;
		data->tex->y = data->player->draw_start;
		pixil_door(data, column_drawn, tex_x);
		return ;
	}
	data->tex->y = data->player->draw_start;
	texture = get_wall_texture(data);
	pixil(data, column_drawn, tex_x, texture);
}
