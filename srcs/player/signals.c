/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:10:47 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/09/01 16:27:02 by fragarc2         ###   ########.fr       */
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
	if (keysym == XK_space)
		data->player->key_states[5] = 1;
	if (keysym == XK_e)
		data->player->key_states[6] = 1;
	return (0);
}

int set_jump(t_data *data)
{
	static unsigned int jump = 0;
	static int increase;

	if (jump >= JUMP_HEIGHT)
		increase = 0;
	if (increase == 1)
	{
		jump += JUMP_HEIGHT / 12;
		return jump;
	}
	if (jump > 0)
	{
		jump -= JUMP_HEIGHT / 12;
		return jump;
	}
	if (data->player->key_states[5] == 1)
		increase = 1;
	return jump;
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

void    movement_handler(t_data *data)
{
    static int mult = 1;
    double  next_x;
    double  next_y;

    mult = 1;
    if (data->player->key_states[4] == 1)
        mult = 2;
    if (data->player->key_states[0] == 1)
    {
        next_x = data->player->pos_x + data->player->dir_x * (WLK_SPEED * mult);
        if (data->map->map[(int)data->player->pos_y][(int)next_x] != '1')
            data->player->pos_x = next_x;
        next_y = data->player->pos_y + data->player->dir_y * (WLK_SPEED * mult);
        if (data->map->map[(int)next_y][(int)data->player->pos_x] != '1')
            data->player->pos_y = next_y;
    }
    if (data->player->key_states[1] == 1)
    {
        next_x = data->player->pos_x - data->player->dir_x * (WLK_SPEED * mult);
        if (data->map->map[(int)data->player->pos_y][(int)next_x] != '1')
            data->player->pos_x = next_x;
        next_y = data->player->pos_y - data->player->dir_y * (WLK_SPEED * mult);
        if (data->map->map[(int)next_y][(int)data->player->pos_x] != '1')
            data->player->pos_y = next_y;
    }
    if (data->player->key_states[2] == 1)
    {
        next_x = data->player->pos_x + data->player->plane_x * ((WLK_SPEED * mult) + 0.025);
        if (data->map->map[(int)data->player->pos_y][(int)next_x] != '1')
            data->player->pos_x = next_x;
        next_y = data->player->pos_y + data->player->plane_y * ((WLK_SPEED * mult) + 0.025);
        if (data->map->map[(int)next_y][(int)data->player->pos_x] != '1')
            data->player->pos_y = next_y;
    }
    if (data->player->key_states[3] == 1)
    {
        next_x = data->player->pos_x - data->player->plane_x * ((WLK_SPEED * mult) + 0.025);
        if (data->map->map[(int)data->player->pos_y][(int)next_x] != '1')
            data->player->pos_x = next_x;
        next_y = data->player->pos_y - data->player->plane_y * ((WLK_SPEED * mult) + 0.025);
        if (data->map->map[(int)next_y][(int)data->player->pos_x] != '1')
            data->player->pos_y = next_y;
    }
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
	if (keysym == XK_space)
		data->player->key_states[5] = 0;
	if (keysym == XK_e)
		data->player->key_states[6] = 0;
	return (0);
}
