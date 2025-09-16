/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pio <pio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:33:39 by fragarc2          #+#    #+#             */
/*   Updated: 2025/09/16 15:29:41 by pio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	my_mlx_pixel_put(t_im *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(int *)dst = color;
}

void	*my_mlx_xpm_image(t_data *data, char *file)
{
	int	width;
	int	height;

	width = data->image->width;
	height = data->image->height;
	return (mlx_xpm_file_to_image(data->mlx_ptr, file, &width, &height));
}

void	*my_addr(t_im *dir)
{
	return (mlx_get_data_addr(dir->mlx_img, &dir->bpp,
			&dir->line_length, &dir->endian));
}

void	door_initialiser(t_data *data)
{
	data->map->door->mlx_img = my_mlx_xpm_image(data,
			data->map->door->file);
	data->map->door->addr = my_addr(data->map->door);
	data->map->door_1->mlx_img = my_mlx_xpm_image(data,
			data->map->door_1->file);
	data->map->door_1->addr = my_addr(data->map->door_1);
	data->map->door_2->mlx_img = my_mlx_xpm_image(data,
			data->map->door_2->file);
	data->map->door_2->addr = my_addr(data->map->door_2);
	data->map->door_3->mlx_img = my_mlx_xpm_image(data,
			data->map->door_3->file);
	data->map->door_3->addr = my_addr(data->map->door_3);
}

void	tex_initialiser(t_data *data)
{
	data->map->east->mlx_img = my_mlx_xpm_image(data, data->map->east->file);
	data->map->east->addr = my_addr(data->map->east);
	data->map->north->mlx_img = my_mlx_xpm_image(data, data->map->north->file);
	data->map->north->addr = my_addr(data->map->north);
	data->map->south->mlx_img = my_mlx_xpm_image(data, data->map->south->file);
	data->map->south->addr = my_addr(data->map->south);
	data->map->west->mlx_img = my_mlx_xpm_image(data, data->map->west->file);
	data->map->west->addr = my_addr(data->map->west);
	door_initialiser(data);
}

void mlx_starter(t_data *data)
{
	char *t;

	t = "cub3D - Made by fragarc2 and aaleixo-";
	data->mlx_ptr = mlx_init();
	data->window_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, t);
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

int open_closest_door(t_data *data)
{
	t_doors *closest = NULL;
	static int key = 0;
	double min_dist = 1e9;
	int px = (int)data->player->pos_x;
	int py = (int)data->player->pos_y;
	for (int i = 0; i < data->map->door_num; i++)
	{
		t_doors *door = data->map->doors[i];
		double dx = door->coords[0] + 0.5 - px;
		double dy = door->coords[1] + 0.5 - py;
		double dist = dx * dx + dy * dy;
		if (dist < min_dist)
		{
			min_dist = dist;
			closest = door;
		}
	}
	if (closest >= 0)
	{
		if(data->player->key_states[6] == 1)
			key = 1;
		if(data->player->flag == 0 && key == 1)
		{
			if(closest->open < 100)
				closest->open+= 2;
			if(closest->open == 100)
			{
				key = 0;
				data->player->flag = 1;
			}
		}
		if(data->player->flag == 1 && key == 1)
		{
			if(closest->open > 10)
				closest->open-= 2;
			if(closest->open == 10)
			{
				key = 0;
				data->player->flag = 0;
			}
		}
		return closest->open;
    }
    return 100;
}

int vectors(void *param)
{
	t_data *data = (t_data *)param;
	int x = 0;
	int jump = set_jump(data);
	int side;
	int z = 0;

	movement_handler(data);
	mlx_mouse_move(data->mlx_ptr, data->window_ptr, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	z = open_closest_door(data);

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
			draw_texture(data, side, column_drawn, tex_x, x, z);
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

void draw_texture(t_data *data, int side, int *column_drawn, int tex_x, int x, int z)
{
	double step = 1.0 * TEXTURE_SIZE / data->player->line_height;
	double tex_pos = (data->player->draw_start - WINDOW_HEIGHT / 2 + data->player->line_height / 2) * step;
	t_im *texture = NULL;
	int open_val = doors->open;
	if (data->map->map[data->player->map_y][data->player->map_x] == '1')
		texture = get_wall_texture(data, side);
	else if (open_val > 75)
		texture = data->map->door;
	else if (open_val > 50)
		texture = data->map->door_1;
	else if (open_val > 25)
		texture = data->map->door_2;
	else if (open_val > 0)
		texture = data->map->door_3;
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
