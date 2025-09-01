/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:33:39 by fragarc2          #+#    #+#             */
/*   Updated: 2025/09/01 14:56:02 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void my_mlx_pixel_put(t_im *img, int x, int y, int color)
{
	char *dst;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(int *)dst = color;
}

void tex_initialiser(t_data *data)
{
	data->map->east->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->east->file, &data->image->width, &data->image->height);
	data->map->east->addr = mlx_get_data_addr(data->map->east->mlx_img, &data->map->east->bpp, &data->map->east->line_length, &data->map->east->endian);
	data->map->north->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->north->file, &data->image->width, &data->image->height);
	data->map->north->addr = mlx_get_data_addr(data->map->north->mlx_img, &data->map->north->bpp, &data->map->north->line_length, &data->map->north->endian);
	data->map->south->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->south->file, &data->image->width, &data->image->height);
	data->map->south->addr = mlx_get_data_addr(data->map->south->mlx_img, &data->map->south->bpp, &data->map->south->line_length, &data->map->south->endian);
	data->map->west->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->west->file, &data->image->width, &data->image->height);
	data->map->west->addr = mlx_get_data_addr(data->map->west->mlx_img, &data->map->west->bpp, &data->map->west->line_length, &data->map->west->endian);
	data->map->door->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->door->file, &data->image->width, &data->image->height);
	data->map->door->addr = mlx_get_data_addr(data->map->door->mlx_img, &data->map->door->bpp, &data->map->door->line_length, &data->map->door->endian);
	data->map->door_1->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->door_1->file, &data->image->width, &data->image->height);
	data->map->door_1->addr = mlx_get_data_addr(data->map->door_1->mlx_img, &data->map->door_1->bpp, &data->map->door_1->line_length, &data->map->door_1->endian);
	data->map->door_2->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->door_2->file, &data->image->width, &data->image->height);
	data->map->door_2->addr = mlx_get_data_addr(data->map->door_2->mlx_img, &data->map->door_2->bpp, &data->map->door_2->line_length, &data->map->door_2->endian);
	data->map->door_3->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->map->door_3->file, &data->image->width, &data->image->height);
	data->map->door_3->addr = mlx_get_data_addr(data->map->door_3->mlx_img, &data->map->door_3->bpp, &data->map->door_3->line_length, &data->map->door_3->endian);
}

void mlx_starter(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->window_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D - Made by fragarc2 and aaleixo-");
	data->image->mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->image->addr = mlx_get_data_addr(data->image->mlx_img, &data->image->bpp, &data->image->line_length, &data->image->endian);
	tex_initialiser(data);
}

int get_texel_color(t_im *texture, int tex_x, int tex_y)
{
	char *tex_addr = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bpp / 8));
	return *(int *)tex_addr;
}

t_im *get_wall_texture(t_data *data, int side)
{
	if (side == 0 && data->player->ray_dir_x > 0)
		return data->map->east;
	else if (side == 0 && data->player->ray_dir_x < 0)
		return data->map->west;
	else if (side == 1 && data->player->ray_dir_y > 0)
		return data->map->south;
	else
		return data->map->north;
}

int vectors(void *param)
{
	t_data *data = (t_data *)param;
	int x = 0;
	int jump = set_jump(data);
	int side;
	
	movement_handler(data);
	mlx_mouse_move(data->mlx_ptr, data->window_ptr, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	while (x < WINDOW_WIDTH)
	{
		int column_drawn[WINDOW_HEIGHT] = {0};
		int i = 0;

		data->player->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		helper(data);
		while (i < TEXTURE_SIZE)
		{
			side = set_side(data);

			if (data->map->map[data->player->map_y][data->player->map_x] != '1' && data->map->map[data->player->map_y][data->player->map_x] != '2')
				continue;

			if (side == 0)
				data->player->perp_wall_dist = fabs((data->player->map_x - data->player->pos_x + (1 - data->player->step_x) / 2) / data->player->ray_dir_x);
			else
				data->player->perp_wall_dist = fabs((data->player->map_y - data->player->pos_y + (1 - data->player->step_y) / 2) / data->player->ray_dir_y);
			if (data->player->perp_wall_dist < 0.01)
				data->player->perp_wall_dist = 0.01;
			data->player->line_height = (int)(WINDOW_HEIGHT / data->player->perp_wall_dist);
			data->player->draw_start = -data->player->line_height / 2 + WINDOW_HEIGHT / 2 + (jump / data->player->perp_wall_dist);
			data->player->draw_end = data->player->line_height / 2 + WINDOW_HEIGHT / 2 + (jump / data->player->perp_wall_dist);
			if (data->player->draw_start < 0) data->player->draw_start = 0;
			if (data->player->draw_end > WINDOW_HEIGHT) data->player->draw_end = WINDOW_HEIGHT -1;

			
			int tex_x = (int)(get_wall_x(data, side) * (double)TEXTURE_SIZE);
			if (tex_x < 0)
				tex_x = 0;
			if (tex_x >= TEXTURE_SIZE)
				tex_x = TEXTURE_SIZE - 1;
			if ((side == 0 && data->player->ray_dir_x < 0) || (side == 1 && data->player->ray_dir_y > 0))
				tex_x = TEXTURE_SIZE - tex_x - 1;
			draw_texture(data, side, column_drawn, tex_x, x);
			if (data->map->map[data->player->map_y][data->player->map_x] == '1')
				break;
			i++;
		}
		do_y(data, x, column_drawn);
		x++;
	}
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->image->mlx_img, 0, 0);
	return 0;
}

void draw_texture(t_data *data, int side, int *column_drawn, int tex_x, int x)
{
	double step = 1.0 * TEXTURE_SIZE / data->player->line_height;
	double tex_pos = (data->player->draw_start - WINDOW_HEIGHT / 2 + data->player->line_height / 2) * step;
	t_im *texture = NULL;
	if (data->map->map[data->player->map_y][data->player->map_x] == '1')
		texture = get_wall_texture(data, side);
	else
		texture = data->map->door;
	for (int y = data->player->draw_start; y < data->player->draw_end; y++)
	{
	    if (y < 0 || y >= WINDOW_HEIGHT)
	    {
	        tex_pos += step;
	        continue;
	    }
	    if (column_drawn[y])
	    {
	        tex_pos += step;
	        continue;
	    }
	    int tex_y = (int)tex_pos;
	    if (tex_y < 0) tex_y = 0;
	    if (tex_y >= TEXTURE_SIZE) tex_y = TEXTURE_SIZE - 1;
	    int color = get_texel_color(texture, tex_x, tex_y);
	    if (data->map->map[data->player->map_y][data->player->map_x] == '2' && color == -16777216)
	    {
	        tex_pos += step;
	        continue;
	    }
	    my_mlx_pixel_put(data->image, x, y, color);
	    column_drawn[y] = 1;
	    tex_pos += step;
	}
}
