/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:10:47 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/08/12 12:48:52 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
	{
        mlx_destroy_window(data->mlx_ptr, data->window_ptr);
        data->window_ptr = NULL;
    }
   /*  else if (ft_strchr("wasd", keysym))
        move_player(data, keysym); */
    else if (keysym == 65361)
        data->player->ray_dir_x -= 0.05;
    else if (keysym == 65363)
        data->player->ray_dir_x += 0.05;
	else if (keysym == 65362)
        data->player->ray_dir_y -= 0.05;
    else if (keysym == 65364)
        data->player->ray_dir_y += 0.05;
    if (data->player->ray_dir_x < 0)
        data->player->ray_dir_x += 2 * 3.14159;
    if (data->player->ray_dir_x > 2 * 3.14159)
		data->player->ray_dir_x -= 2 * 3.14159;
	if (data->player->ray_dir_y < 0)
        data->player->ray_dir_y += 2 * 3.14159;
    if (data->player->ray_dir_y > 2 * 3.14159)
        data->player->ray_dir_y -= 2 * 3.14159;
    return (0);
}

int	handle_btnrelease(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->window_ptr);
	data->window_ptr = NULL;
	return (0);
}
