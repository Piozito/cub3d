/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:33:39 by fragarc2          #+#    #+#             */
/*   Updated: 2025/09/25 17:26:15 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

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

int vectors(void *param)
{
	t_data *data = (t_data *)param;
	int x = 0;
	int side;

	movement_handler(data);
	//mlx_mouse_move(data->mlx_ptr, data->window_ptr, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
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
			data->player->draw_start = -data->player->line_height / 2 + WINDOW_HEIGHT / 2;
			data->player->draw_end = data->player->line_height / 2 + WINDOW_HEIGHT / 2;
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

t_doors *find_door(t_doors **array, int map_y, int map_x)
{
	ssize_t i;
	t_doors *door;

	i = 0;
	while(array[i])
	{
		if(array[i]->coords[0] == map_y && array[i]->coords[1] == map_x)
		{
			door = array[i];
			return door;
		}
		i++;
	}
	return NULL;
}

void draw_texture(t_data *data, int side, int *column_drawn, int tex_x, int x)
{
    int draw_start = data->player->draw_start;
    int draw_end = data->player->draw_end;

    if (draw_start < 0) draw_start = 0;
    if (draw_end > WINDOW_HEIGHT) draw_end = WINDOW_HEIGHT;

    double wall_height = fabs((double)WINDOW_HEIGHT / data->player->perp_wall_dist);
    double step = (double)TEXTURE_SIZE / wall_height;
    double tex_pos = (draw_start - WINDOW_HEIGHT / 2.0 + wall_height / 2.0) * step;

    if (data->map->map[data->player->map_y][data->player->map_x] == '2')
    {
		t_doors *door = find_door(data->map->doors, data->player->map_y, data->player->map_x);
        int percent = (100 - door->open);
		int open_px = 0;
        if(percent > 80)
            percent = 80;
		if(data->player->map_y == door->coords[0] && data->player->map_x == door->coords[1])
			open_px = percent;

        int top_limit = TEXTURE_SIZE - open_px;
        int bot_limit = open_px;

        for (int y = draw_start; y < draw_end; y++)
        {
            if (y < 0 || y >= WINDOW_HEIGHT) continue;
            if (column_drawn[y]) { tex_pos += step; continue; }

            int tex_y = (int)tex_pos;
            tex_pos += step;

            if (tex_y < 0) tex_y = 0;
            if (tex_y >= TEXTURE_SIZE) tex_y = TEXTURE_SIZE - 1;

            int drew = 0;
            if (tex_y < top_limit)
            {
                int color = get_texel_color(data->map->door_top, tex_x, tex_y + open_px);
                if (color != -16777216)
				{
                    my_mlx_pixel_put(data->image, x, y, color);
                    column_drawn[y] = 1;
                    drew = 1;
                }
            }
            if (!drew && tex_y >= bot_limit)
            {
                int color = get_texel_color(data->map->door_bot, tex_x, tex_y - bot_limit);
                if (color != -16777216)
				{
                    my_mlx_pixel_put(data->image, x, y, color);
                    column_drawn[y] = 1;
                }
            }
        }
        return;
    }

    t_im *texture = get_wall_texture(data, side);
    for (int y = draw_start; y < draw_end; y++)
    {
        if (y < 0 || y >= WINDOW_HEIGHT) continue;
        if (column_drawn[y])
		{
            tex_pos += step;
            continue;
        }
        int tex_y = (int)tex_pos;
        if (tex_y < 0) tex_y = 0;
        if (tex_y >= TEXTURE_SIZE) tex_y = TEXTURE_SIZE - 1;
        int color = get_texel_color(texture, tex_x, tex_y);
        if(color != -16777216)
            my_mlx_pixel_put(data->image, x, y, color);
        column_drawn[y] = 1;
        tex_pos += step;
    }
}
