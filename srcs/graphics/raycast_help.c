/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:03:35 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/09/25 17:07:07 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

double	get_wall_x(t_data *data, int side)
{
	double	wall_x;

	if (side == 0)
		wall_x = data->player->pos_y + data->player->perp_wall_dist * data->player->ray_dir_y;
	else
		wall_x = data->player->pos_x + data->player->perp_wall_dist * data->player->ray_dir_x;
	wall_x -= floor(wall_x + 1e-6);
	return (wall_x);
}

void	helper(t_data *data)
{
	data->player->ray_dir_x = data->player->dir_x + data->player->plane_x * data->player->camera_x;
	data->player->ray_dir_y = data->player->dir_y + data->player->plane_y * data->player->camera_x;
	data->player->delta_dist_x = fabs(1 / data->player->ray_dir_x);
	data->player->delta_dist_y = fabs(1 / data->player->ray_dir_y);
	data->player->map_x = (int)data->player->pos_x;
	data->player->map_y = (int)data->player->pos_y;
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
}

int	set_side(t_data *data)
{
	int	side;

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
	return (side);
}

void	do_y(t_data *data, int x, int *column_drawn)
{
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (!column_drawn[y])
		{
			if (y < WINDOW_HEIGHT / 2)
				my_mlx_pixel_put(data->image, x, y, data->map->celling);
			else
				my_mlx_pixel_put(data->image, x, y, data->map->floor);
		}
		y++;
	}
}
