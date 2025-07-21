/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:33:39 by fragarc2          #+#    #+#             */
/*   Updated: 2025/07/21 15:09:05 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void mlx_starter(t_data *data)
{
	t_im	img;
	data->mlx_ptr = mlx_init();
	data->window_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	data->img_ptr = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_length, &img.endian);
}

void my_mlx_pixel_put(t_im *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}
void waller(t_data *data, int x, int y, int side)
{
	double step;
	double tex_pos;
	int color;
	char *texture;

	if (side == 0 && data->player.ray_dir_x > 0)
		texture = data->map.east;
	else if (side == 0 && data->player.ray_dir_x < 0)
		texture = data->map.west;
	else if (side == 1 && data->player.ray_dir_y > 0)
		texture = data->map.south;
	else
		texture = data->map.north;

	data->player.tex_x = (int)(data->player.wall_x * (double)TEXTURE_SIZE);
	step = 1.0 * TEXTURE_SIZE / data->player.line_height;
	tex_pos = (y - data->player.draw_start) * step;
	data->player.tex_y = (int)tex_pos & (TEXTURE_SIZE - 1);
	color = texture[TEXTURE_SIZE * data->player.tex_y + data->player.tex_x];
	my_mlx_pixel_put(&data->image, x, y, color);
}
void vectors(t_data *data)
{
	int hit = 0;
	int side = 0;
	int x = 0;
	int y = 0;
	while (x < WINDOW_WIDTH)
	{
		hit = 0;
		data->player.camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		data->player.ray_dir_x = data->player.dir_x + data->player.plane_x * data->player.camera_x;
		data->player.ray_dir_y = data->player.dir_y + data->player.plane_y * data->player.camera_x;

		data->player.map_x = (int)data->player.pos_x;
		data->player.map_y = (int)data->player.pos_y;

		data->player.delta_dist_x = fabs(1 / data->player.ray_dir_x);
		data->player.delta_dist_y = fabs(1 / data->player.ray_dir_y);

		if (data->player.ray_dir_x < 0)
		{
			data->player.step_x = -1;
			data->player.side_dist_x = (data->player.pos_x - data->player.map_x) * data->player.delta_dist_x;
		}
		else
		{
			data->player.step_x = 1;
			data->player.side_dist_x = (data->player.map_x + 1.0 - data->player.pos_x) * data->player.delta_dist_x;
		}

		if (data->player.ray_dir_y < 0)
		{
			data->player.step_y = -1;
			data->player.side_dist_y = (data->player.pos_y - data->player.map_y) * data->player.delta_dist_y;
		}
		else
		{
			data->player.step_y = 1;
			data->player.side_dist_y = (data->player.map_y + 1.0 - data->player.pos_y) * data->player.delta_dist_y;
		}
		while (hit == 0)
		{
			if (data->player.side_dist_x < data->player.side_dist_y)
			{
				data->player.side_dist_x += data->player.delta_dist_x;
				data->player.map_x += data->player.step_x;
				side = 0;
			}
			else
			{
				data->player.side_dist_y += data->player.delta_dist_y;
				data->player.map_y += data->player.step_y;
				side = 1;
			}
			if (data->player.map.map[data->player.map_x][data->player.map_y] == '1')
				hit = 1;
		}
		if (side == 0)
			data->player.perp_wall_dist = (data->player.map_x - data->player.pos_x + (1 - data->player.step_x) / 2) / data->player.ray_dir_x;
		else
			data->player.perp_wall_dist = (data->player.map_y - data->player.pos_y + (1 - data->player.step_y) / 2) / data->player.ray_dir_y;
		if (side == 0)
			data->player.wall_x = data->player.pos_y + data->player.perp_wall_dist * data->player.ray_dir_y;
		else
			data->player.wall_x = data->player.pos_x + data->player.perp_wall_dist * data->player.ray_dir_x;
		data->player.wall_x -= floor(data->player.wall_x);
		data->player.line_height = (int)(WINDOW_HEIGHT / data->player.perp_wall_dist);
		data->player.draw_start = -data->player.line_height / 2 + WINDOW_HEIGHT / 2;
		data->player.draw_end = data->player.line_height / 2 + WINDOW_HEIGHT / 2;
		while (y < WINDOW_HEIGHT)
		{
			if (y < data->player.draw_start)
				my_mlx_pixel_put(&data->image, x, y, data->player.map.celling);
			else if (y >= data->player.draw_start && y <= data->player.draw_end)
				waller(data, x, y, side);
			else
				my_mlx_pixel_put(&data->image, x, y, data->player.map.floor);
		}
		x++;
	}
}



