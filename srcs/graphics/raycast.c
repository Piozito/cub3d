/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:33:39 by fragarc2          #+#    #+#             */
/*   Updated: 2025/07/23 19:02:30 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void my_mlx_pixel_put(t_im *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(int *)dst = color;
}

void tex_initialiser(t_data *data)
{
	data->map->east->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->east->addr, &data->image->width, &data->image->height);
	data->map->east->addr = mlx_get_data_addr(data->map->east->mlx_img, &data->map->east->bpp, &data->map->east->line_length, &data->map->east->endian);

	data->map->north->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->north->addr, &data->image->width, &data->image->height);
	data->map->north->addr = mlx_get_data_addr(data->map->north->mlx_img, &data->map->north->bpp, &data->map->north->line_length, &data->map->north->endian);

	data->map->south->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->south->addr, &data->image->width, &data->image->height);
	data->map->south->addr = mlx_get_data_addr(data->map->south->mlx_img, &data->map->south->bpp, &data->map->south->line_length, &data->map->south->endian);

	data->map->west->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->west->addr, &data->image->width, &data->image->height);
	data->map->west->addr = mlx_get_data_addr(data->map->west->mlx_img, &data->map->west->bpp, &data->map->west->line_length, &data->map->west->endian);
}

void mlx_starter(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->window_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	data->img_ptr = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->image->mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->image->addr = mlx_get_data_addr(data->image->mlx_img, &data->image->bpp, &data->image->line_length, &data->image->endian);
	tex_initialiser(data);
}


void waller(t_data *data, int x, int y, int side)
{
	double step;
	double tex_pos;
	int color;
	t_im *texture;

	if (side == 0 && data->player->ray_dir_x > 0)
		texture = data->map->east;
	else if (side == 0 && data->player->ray_dir_x < 0)
		texture = data->map->west;
	else if (side == 1 && data->player->ray_dir_y > 0)
		texture = data->map->south;
	else
		texture = data->map->north;


	data->player->tex_x = (int)(data->player->wall_x * (double)TEXTURE_SIZE);
	step = 1.0 * TEXTURE_SIZE / data->player->line_height;
	tex_pos = (y - data->player->draw_start) * step;
	data->player->tex_y = (int)tex_pos & (TEXTURE_SIZE - 1);
	char *tex_addr = texture->addr + (data->player->tex_y * texture->line_length + data->player->tex_x * (texture->bpp / 8));
	color = *(int *)tex_addr;
	my_mlx_pixel_put(data->image, x, y, color);
}
int vectors(void *param)
{
	t_data *data = (t_data *)param;
	int hit = 0;
	int side = 0;
	int x = 0;
	int y = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		hit = 0;
		data->player->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		data->player->ray_dir_x = data->player->dir_x + data->player->plane_x * data->player->camera_x;
		data->player->ray_dir_y = data->player->dir_y + data->player->plane_y * data->player->camera_x;

		data->player->map_x = (int)data->player->pos_x;
		data->player->map_y = (int)data->player->pos_y;

		data->player->delta_dist_x = fabs(1 / data->player->ray_dir_x);
		data->player->delta_dist_y = fabs(1 / data->player->ray_dir_y);

		if (data->player->ray_dir_x < 0)
		{
			data->player->step_x = -1;
			data->player->side_dist_x = (data->player->pos_x - data->player->map_x) * data->player->delta_dist_x;
		}
		else
		{
			data->player->step_x = 1;
			data->player->side_dist_x = (data->player->map_x + 1.0 - data->player->pos_x) * data->player->delta_dist_x;
		}

		if (data->player->ray_dir_y < 0)
		{
			data->player->step_y = -1;
			data->player->side_dist_y = (data->player->pos_y - data->player->map_y) * data->player->delta_dist_y;
		}
		else
		{
			data->player->step_y = 1;
			data->player->side_dist_y = (data->player->map_y + 1.0 - data->player->pos_y) * data->player->delta_dist_y;
		}
		while (hit == 0)
		{
			if (data->player->side_dist_x < data->player->side_dist_y)
			{
				data->player->side_dist_x += data->player->delta_dist_x;
				data->player->map_x += data->player->step_x;
				side = 0;
			}
			else
			{
				data->player->side_dist_y += data->player->delta_dist_y;
				data->player->map_y += data->player->step_y;
				side = 1;
			}
			if (data->player->map_x < 0 || data->player->map_y < 0
				|| data->player->map_x >= data->map->map_lenght
				|| data->player->map_y >= data->map->map_height)
			{
				break;
			}
			if (data->map->map[data->player->map_x][data->player->map_y] == '1')
				hit = 1;
		}
		if (side == 0)
			data->player->perp_wall_dist = (data->player->map_x - data->player->pos_x + (1 - data->player->step_x) / 2) / data->player->ray_dir_x;
		else
			data->player->perp_wall_dist = (data->player->map_y - data->player->pos_y + (1 - data->player->step_y) / 2) / data->player->ray_dir_y;
		if (side == 0)
			data->player->wall_x = data->player->pos_y + data->player->perp_wall_dist * data->player->ray_dir_y;
		else
			data->player->wall_x = data->player->pos_x + data->player->perp_wall_dist * data->player->ray_dir_x;
		data->player->wall_x -= floor(data->player->wall_x);
		data->player->line_height = (int)(WINDOW_HEIGHT / data->player->perp_wall_dist);
		data->player->draw_start = -data->player->line_height / 2 + WINDOW_HEIGHT / 2;
		data->player->draw_end = data->player->line_height / 2 + WINDOW_HEIGHT / 2;
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			if (y < data->player->draw_start)
				my_mlx_pixel_put(data->image, x, y, data->map->celling);
			else if (y >= data->player->draw_start && y <= data->player->draw_end)
				waller(data, x, y, side);
			else
				my_mlx_pixel_put(data->image, x, y, data->map->floor);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->image->mlx_img, 0, 0);
	return(0);
}



