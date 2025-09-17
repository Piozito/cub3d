/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:10:47 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/09/17 14:08:54 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"


int handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_clear(data);
	if (keysym == XK_w)
		data->player->key_states[0] = 1;
	if (keysym == XK_s)
		data->player->key_states[1] = 1;
	if (keysym == XK_d)
		data->player->key_states[2] = 1;
	if (keysym == XK_a)
		data->player->key_states[3] = 1;
	if (keysym == XK_Shift_L)
		data->player->key_states[4] = 1;
	if (keysym == XK_e)
		data->player->key_states[6] = 1;
	return (0);
}

int    camera_handler(int x, int y, t_player *player)
{
    static double   last_x = -1;
    double          rot_speed;
    double          old_dir_x;
    double          old_plane_x;
    int             delta_x;

    (void)y;
    if (last_x == -1)
        last_x = x;
    delta_x = x - last_x;
    if (delta_x == 0)
        return (0);
    rot_speed = (ROT_SPEED * delta_x) * -1;
    old_dir_x = player->dir_x;
    player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y * sin(-rot_speed);
    player->dir_y = old_dir_x * sin(-rot_speed) + player->dir_y * cos(-rot_speed);
    old_plane_x = player->plane_x;
    player->plane_x = player->plane_x * cos(-rot_speed) - player->plane_y * sin(-rot_speed);
    player->plane_y = old_plane_x * sin(-rot_speed) + player->plane_y * cos(-rot_speed);
    return (0);
}

int check_movement(t_data *data, double next_x, double next_y)
{
    int next[2];
    int i[2];
    double offsets[2];

    offsets[0] = -PLR_HITBOX;
    offsets[1] = PLR_HITBOX;

    i[0] = 0;
    while (i[0] < 2)
    {
        i[1] = 0;
        while (i[1] < 2)
        {
            next[0] = (int)(next_x + offsets[i[0]]);
            next[1] = (int)(next_y + offsets[i[1]]);
            if (data->map->map[next[1]][next[0]] == '1')
                return 1;
            if (data->player->flag == 1 && data->map->map[next[1]][next[0]] == '2')
                return 1;
            i[1]++;
        }
        i[0]++;
    }
    return 0;
}

void movement_handler(t_data *data)
{
    double move_x = 0, move_y = 0;
    int speed_mult = (data->player->key_states[4] == 1) ? 2 : 1;
    double move_speed = WLK_SPEED * speed_mult;

    if (data->player->key_states[0] == 1)
    {
        move_x += data->player->dir_x * move_speed;
        move_y += data->player->dir_y * move_speed;
    }
    if (data->player->key_states[1] == 1)
    {
        move_x -= data->player->dir_x * move_speed;
        move_y -= data->player->dir_y * move_speed;
    }
    if (data->player->key_states[2] == 1)
    {
        move_x += data->player->plane_x * (move_speed + 0.025);
        move_y += data->player->plane_y * (move_speed + 0.025);
    }
    if (data->player->key_states[3] == 1)
    {
        move_x -= data->player->plane_x * (move_speed + 0.025);
        move_y -= data->player->plane_y * (move_speed + 0.025);
    }

    double next_x = data->player->pos_x + move_x;
    double next_y = data->player->pos_y + move_y;

    if (!check_movement(data, next_x, data->player->pos_y))
        data->player->pos_x = next_x;
    if (!check_movement(data, data->player->pos_x, next_y))
        data->player->pos_y = next_y;
}

int	handle_btnrelease(int keysym, t_data *data)
{
	if (keysym == XK_w)
		data->player->key_states[0] = 0;
	else if (keysym == XK_s)
		data->player->key_states[1] = 0;
	else if (keysym == XK_d)
		data->player->key_states[2] = 0;
	else if (keysym == XK_a)
		data->player->key_states[3] = 0;
	if (keysym == XK_Shift_L)
		data->player->key_states[4] = 0;
	if (keysym == XK_e)
		data->player->key_states[6] = 0;
	return (0);
}
