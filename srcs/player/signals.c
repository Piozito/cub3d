/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:10:47 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/08/12 13:39:25 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

#include <math.h>
#define ROT_SPEED 0.05

#include <math.h>
#define ROT_SPEED 0.05

int handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
    {
        mlx_destroy_window(data->mlx_ptr, data->window_ptr);
        data->window_ptr = NULL;
    }
    else if (keysym == 65363)
    {
        double old_dir_x = data->player->dir_x;
        data->player->dir_x = data->player->dir_x * cos(-ROT_SPEED) - data->player->dir_y * sin(-ROT_SPEED);
        data->player->dir_y = old_dir_x * sin(-ROT_SPEED) + data->player->dir_y * cos(-ROT_SPEED);

        double old_plane_x = data->player->plane_x;
        data->player->plane_x = data->player->plane_x * cos(-ROT_SPEED) - data->player->plane_y * sin(-ROT_SPEED);
        data->player->plane_y = old_plane_x * sin(-ROT_SPEED) + data->player->plane_y * cos(-ROT_SPEED);
    }
    else if (keysym == 65361)
    {
        double old_dir_x = data->player->dir_x;
        data->player->dir_x = data->player->dir_x * cos(ROT_SPEED) - data->player->dir_y * sin(ROT_SPEED);
        data->player->dir_y = old_dir_x * sin(ROT_SPEED) + data->player->dir_y * cos(ROT_SPEED);

        double old_plane_x = data->player->plane_x;
        data->player->plane_x = data->player->plane_x * cos(ROT_SPEED) - data->player->plane_y * sin(ROT_SPEED);
        data->player->plane_y = old_plane_x * sin(ROT_SPEED) + data->player->plane_y * cos(ROT_SPEED);
    }
	
	printf("Key: %d\n", keysym);
    return (0);
}

int	handle_btnrelease(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->window_ptr);
	data->window_ptr = NULL;
	return (0);
}
