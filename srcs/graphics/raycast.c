/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:33:39 by fragarc2          #+#    #+#             */
/*   Updated: 2025/08/27 12:08:39 by aaleixo-         ###   ########.fr       */
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

	data->map->door->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->door->addr, &data->image->width, &data->image->height);
	data->map->door->addr = mlx_get_data_addr(data->map->door->mlx_img, &data->map->door->bpp, &data->map->door->line_length, &data->map->door->endian);
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

void waller(t_data *data, int x, int y, int side, int tex_y, int tex_x)
{
	int	 color;
	t_im	*texture;

	if (side == 0 && data->player->ray_dir_x > 0)
		texture = data->map->east;
	else if (side == 0 && data->player->ray_dir_x < 0)
		texture = data->map->west;
	else if (side == 1 && data->player->ray_dir_y > 0)
		texture = data->map->south;
	else
		texture = data->map->north;

	char *tex_addr = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bpp / 8));
	color = *(int *)tex_addr;
	if (color == -16777216)
	{
		while (y < data->player->draw_start || y > data->player->draw_end)
		{
			if (y < data->player->draw_start)
				my_mlx_pixel_put(data->image, x, y, data->map->celling);
			else if (y > data->player->draw_end)
				my_mlx_pixel_put(data->image, x, y, data->map->floor);
		}
	}
	else
		my_mlx_pixel_put(data->image, x, y, color);
}

void wallberg(t_data *data, int x, int y, int tex_y, int tex_x)
{
	int	 color;
	t_im	*texture;

	texture = data->map->door;
	char *tex_addr = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bpp / 8));
	color = *(int *)tex_addr;
	if (color == -16777216)
	{
		return;
	}
	else
		my_mlx_pixel_put(data->image, x, y, color);
}

void do_y(t_data *data, int x, int tex_x, int side, int hit, int jump)
{
	double step = (double)TEXTURE_SIZE / data->player->line_height;
	double tex_pos = (data->player->draw_start - WINDOW_HEIGHT / 2 + data->player->line_height / 2 - (jump / data->player->perp_wall_dist)) * step;
	int tex_y;
	int y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < data->player->draw_start)
			my_mlx_pixel_put(data->image, x, y, data->map->celling);
		else if (y > data->player->draw_end)
			my_mlx_pixel_put(data->image, x, y, data->map->floor);
		else if (y >= data->player->draw_start && y <= data->player->draw_end)
		{
			tex_y = (int)tex_pos & (TEXTURE_SIZE - 1);
			if (tex_y < 0) tex_y = 0;
			if (tex_y >= TEXTURE_SIZE) tex_y = TEXTURE_SIZE - 1;
			if(hit != 2)
				waller(data, x, y, side, tex_y, tex_x);
			if (hit == 2)
				wallberg(data, x, y, tex_y, tex_x);
			tex_pos += step;
		}
		y++;
	}
}

void do_door(t_data *data, int x, int map_x, int map_y, int side, int jump)
{
	double door_x;
	int tex_x;
	if (data->map->map[map_y][map_x] == '2')
	{
		if (side == 0 && data->player->ray_dir_x > 0)
			data->player->perp_wall_dist = fabs(((map_x) - data->player->pos_x + (1 - data->player->step_x) / 2) / data->player->ray_dir_x);
		else if(side == 0)
			data->player->perp_wall_dist = fabs(((map_x) - data->player->pos_x + (1 - data->player->step_x) / 2) / data->player->ray_dir_x);
		else if(data->player->ray_dir_y > 0)
			data->player->perp_wall_dist = fabs(((map_y) - data->player->pos_y + (1 - data->player->step_y) / 2) / data->player->ray_dir_y);
		else
			data->player->perp_wall_dist = fabs(((map_y) - data->player->pos_y + (1 - data->player->step_y) / 2) / data->player->ray_dir_y);
		if (side == 0)
			door_x = data->player->pos_y + data->player->perp_wall_dist * data->player->ray_dir_y;
		else
			door_x = data->player->pos_x + data->player->perp_wall_dist * data->player->ray_dir_x;

		door_x -= floor(door_x + 1e-6);
		if (door_x < 0)
			door_x += 1.0;
		else if (door_x >= 1)
			door_x -= 1.0;

		tex_x = (int)(door_x * (double)TEXTURE_SIZE);
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= TEXTURE_SIZE)
			tex_x = TEXTURE_SIZE - 1;

		if ((side == 0 && data->player->ray_dir_x < 0) || (side == 1 && data->player->ray_dir_y > 0))
			tex_x = TEXTURE_SIZE - tex_x - 1;

		data->player->line_height = (int)(WINDOW_HEIGHT / data->player->perp_wall_dist);
		data->player->draw_start = (-data->player->line_height / 2 + WINDOW_HEIGHT / 2) + (jump / data->player->perp_wall_dist);
		data->player->draw_end = (data->player->line_height / 2 + WINDOW_HEIGHT / 2) - 1 + (jump / data->player->perp_wall_dist);

		if (data->player->draw_start < 0)
			data->player->draw_start = 0;
		if (data->player->draw_end >= WINDOW_HEIGHT)
			data->player->draw_end = WINDOW_HEIGHT - 1;

		do_y(data, x, tex_x, side, 2, jump);
	}
}

int vectors(void *param)
{
	t_data *data = (t_data *)param;
	int hit = 0;
	int side = 0;
	int x = 0;
	int map_x;
	int map_y;
	int flag = 0;
	int door[5];
	int jump = set_jump(data);

	movement_handler(data);
	mlx_mouse_move(data->mlx_ptr, data->window_ptr, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	while (x < WINDOW_WIDTH)
	{
		hit = 0;
		data->player->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		data->player->ray_dir_x = data->player->dir_x + data->player->plane_x * data->player->camera_x;
		data->player->ray_dir_y = data->player->dir_y + data->player->plane_y * data->player->camera_x;

		map_x = (int)data->player->pos_x;
		map_y = (int)data->player->pos_y;

		data->player->delta_dist_x = fabs(1 / data->player->ray_dir_x);
		data->player->delta_dist_y = fabs(1 / data->player->ray_dir_y);

		if (data->player->ray_dir_x < 0)
		{
			data->player->step_x = -1;
			data->player->side_dist_x = (data->player->pos_x - map_x) * data->player->delta_dist_x;
		}
		else
		{
			data->player->step_x = 1;
			data->player->side_dist_x = (map_x + 1.0 - data->player->pos_x) * data->player->delta_dist_x;
		}
		if (data->player->ray_dir_y < 0)
		{
			data->player->step_y = -1;
			data->player->side_dist_y = (data->player->pos_y - map_y) * data->player->delta_dist_y;
		}
		else
		{
			data->player->step_y = 1;
			data->player->side_dist_y = (map_y + 1.0 - data->player->pos_y) * data->player->delta_dist_y;
		}

		while (hit == 0)
		{
			if (data->player->side_dist_x < data->player->side_dist_y)
			{
				data->player->side_dist_x += data->player->delta_dist_x;
				map_x += data->player->step_x;
				side = 0;
			}
			else
			{
				data->player->side_dist_y += data->player->delta_dist_y;
				map_y += data->player->step_y;
				side = 1;
			}
			if (data->map->map[map_y][map_x] == '2')
			{
				door[0] = x;
				door[1] = map_x;
				door[2] = map_y;
				door[3] = side;
				flag = 1;
			}
			if (data->map->map[map_y][map_x] == '1')
				hit = 1;
		}

		if (side == 0)
			data->player->perp_wall_dist = fabs((map_x - data->player->pos_x + (1 - data->player->step_x) / 2) / data->player->ray_dir_x);
		else
			data->player->perp_wall_dist = fabs((map_y - data->player->pos_y + (1 - data->player->step_y) / 2) / data->player->ray_dir_y);

		if (side == 0)
			data->player->wall_x = data->player->pos_y + data->player->perp_wall_dist * data->player->ray_dir_y;
		else
			data->player->wall_x = data->player->pos_x + data->player->perp_wall_dist * data->player->ray_dir_x;

		data->player->wall_x -= floor(data->player->wall_x + 1e-6);
		if (data->player->wall_x < 0)
			data->player->wall_x += 1.0;
		else if (data->player->wall_x >= 1)
			data->player->wall_x -= 1.0;

		int tex_x = (int)(data->player->wall_x * (double)TEXTURE_SIZE);
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= TEXTURE_SIZE)
			tex_x = TEXTURE_SIZE - 1;

		if ((side == 0 && data->player->ray_dir_x < 0) || (side == 1 && data->player->ray_dir_y > 0))
			tex_x = TEXTURE_SIZE - tex_x - 1;

		data->player->line_height = (int)(WINDOW_HEIGHT / data->player->perp_wall_dist);
		data->player->draw_start = (-data->player->line_height / 2 + WINDOW_HEIGHT / 2) + (jump / data->player->perp_wall_dist);
		data->player->draw_end = (data->player->line_height / 2 + WINDOW_HEIGHT / 2) + (jump / data->player->perp_wall_dist);

		if (data->player->draw_start < 0)
			data->player->draw_start = 0;
		if (data->player->draw_end >= WINDOW_HEIGHT)
			data->player->draw_end = WINDOW_HEIGHT - 1;

		do_y(data, x, tex_x, side, hit, jump);
		if (flag == 1)
			do_door(data, door[0], door[1], door[2], door[3], jump);
		x++;
	}
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->image->mlx_img, 0, 0);
	return 0;
}