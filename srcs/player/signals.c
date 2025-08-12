/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:10:47 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/08/12 16:56:37 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"
#define WLK_SPEED 0.02
#define ROT_SPEED 0.05

int handle_keypress(int keysym, t_data *data)
{
    static int mult = 1;
    if (keysym == XK_Escape)
    {
        mlx_destroy_window(data->mlx_ptr, data->window_ptr);
        data->window_ptr = NULL;
		ft_clear(data);
    }
    else if (keysym == XK_Right)
    {
        double old_dir_x = data->player->dir_x;
        data->player->dir_x = data->player->dir_x * cos(-ROT_SPEED) - data->player->dir_y * sin(-ROT_SPEED);
        data->player->dir_y = old_dir_x * sin(-ROT_SPEED) + data->player->dir_y * cos(-ROT_SPEED);

        double old_plane_x = data->player->plane_x;
        data->player->plane_x = data->player->plane_x * cos(-ROT_SPEED) - data->player->plane_y * sin(-ROT_SPEED);
        data->player->plane_y = old_plane_x * sin(-ROT_SPEED) + data->player->plane_y * cos(-ROT_SPEED);
    }
    else if (keysym == XK_Left)
    {
        double old_dir_x = data->player->dir_x;
        data->player->dir_x = data->player->dir_x * cos(ROT_SPEED) - data->player->dir_y * sin(ROT_SPEED);
        data->player->dir_y = old_dir_x * sin(ROT_SPEED) + data->player->dir_y * cos(ROT_SPEED);

        double old_plane_x = data->player->plane_x;
        data->player->plane_x = data->player->plane_x * cos(ROT_SPEED) - data->player->plane_y * sin(ROT_SPEED);
        data->player->plane_y = old_plane_x * sin(ROT_SPEED) + data->player->plane_y * cos(ROT_SPEED);
    }
	else if (keysym == XK_w)
    {
        if (data->map->map[(int)(data->player->pos_y)][(int)(data->player->pos_x + data->player->dir_x * (WLK_SPEED * mult))] != '1')
            data->player->pos_x += data->player->dir_x * (WLK_SPEED * mult);
        if (data->map->map[(int)(data->player->pos_y + data->player->dir_y * (WLK_SPEED * mult))][(int)(data->player->pos_x)] != '1')
            data->player->pos_y += data->player->dir_y * (WLK_SPEED * mult);
    }
    else if (keysym == XK_s)
    {
        if (data->map->map[(int)(data->player->pos_y)][(int)(data->player->pos_x - data->player->dir_x * (WLK_SPEED * mult))] != '1')
            data->player->pos_x -= data->player->dir_x * (WLK_SPEED * mult);
        if (data->map->map[(int)(data->player->pos_y - data->player->dir_y * (WLK_SPEED * mult))][(int)(data->player->pos_x)] != '1')
            data->player->pos_y -= data->player->dir_y * (WLK_SPEED * mult);
    }
    else if (keysym == XK_d)
    {
        if (data->map->map[(int)(data->player->pos_y)][(int)(data->player->pos_x + data->player->plane_x * (WLK_SPEED * mult))] != '1')
            data->player->pos_x += data->player->plane_x * (WLK_SPEED * mult);
        if (data->map->map[(int)(data->player->pos_y + data->player->plane_y * (WLK_SPEED * mult))][(int)(data->player->pos_x)] != '1')
            data->player->pos_y += data->player->plane_y * (WLK_SPEED * mult);
    }
    else if (keysym == XK_a)
    {
        if (data->map->map[(int)(data->player->pos_y)][(int)(data->player->pos_x - data->player->plane_x * (WLK_SPEED * mult))] != '1')
            data->player->pos_x -= data->player->plane_x * (WLK_SPEED * mult);
        if (data->map->map[(int)(data->player->pos_y - data->player->plane_y * (WLK_SPEED * mult))][(int)(data->player->pos_x)] != '1')
            data->player->pos_y -= data->player->plane_y * (WLK_SPEED * mult);
	}
    else if (keysym == XK_Up)
    {
        printf("BOOST\n");
        if(mult < 5)
            mult++;
    }
    else if (keysym == XK_Down)
    {
        printf("RELAX\n");
        if(mult > 1)
            mult--;
    }
    return (0);
}

int	handle_btnrelease(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->window_ptr);
	data->window_ptr = NULL;
	return (0);
}
