/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:33:39 by fragarc2          #+#    #+#             */
/*   Updated: 2025/07/17 13:43:10 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/cub3d.h"

void vectors(t_player *player)
{
	int hit = 0;
	int side = 0;
	int x = 0;
	while (x < WINDOW_WIDTH)
	{
		hit = 0;
		player->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		player->ray_dir_x = player->dir_x + player->plane_x * player->camera_x;
		player->ray_dir_y = player->dir_y + player->plane_y * player->camera_x;

		player->map_x = (int)player->pos_x;
		player->map_y = (int)player->pos_y;

		player->delta_dist_x = fabs(1 / player->ray_dir_x);
		player->delta_dist_y = fabs(1 / player->ray_dir_y);

		if (player->ray_dir_x < 0)
		{
			player->step_x = -1;
			player->side_dist_x = (player->pos_x - player->map_x) * player->delta_dist_x;
		}
		else
		{
			player->step_x = 1;
			player->side_dist_x = (player->map_x + 1.0 - player->pos_x) * player->delta_dist_x;
		}

		if (player->ray_dir_y < 0)
		{
			player->step_y = -1;
			player->side_dist_y = (player->pos_y - player->map_y) * player->delta_dist_y;
		}
		else
		{
			player->step_y = 1;
			player->side_dist_y = (player->map_y + 1.0 - player->pos_y) * player->delta_dist_y;
		}
		while (hit == 0)
		{
			if (player->side_dist_x < player->side_dist_y)
			{
				player->side_dist_x += player->delta_dist_x;
				player->map_x += player->step_x;
				side = 0;
			}
			else
			{
				player->side_dist_y += player->delta_dist_y;
				player->map_y += player->step_y;
				side = 1;
			}
			if (player->map.map[player->map_x][player->map_y] == '1')
				hit = 1;
		}
		if (side == 0)
			player->perp_wall_dist = (player->map_x - player->pos_x + (1 - player->step_x) / 2) / player->ray_dir_x;
		else
			player->perp_wall_dist = (player->map_y - player->pos_y + (1 - player->step_y) / 2) / player->ray_dir_y;
		player->line_height = (int)(WINDOW_HEIGHT / player->perp_wall_dist);
		player->draw_start = -player->line_height / 2 + WINDOW_HEIGHT / 2;
		player->draw_end = player->line_height / 2 + WINDOW_HEIGHT / 2;
		x++;
	}
}

void mlx_starter(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->window_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	data->img_ptr = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
}
