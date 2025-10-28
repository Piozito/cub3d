/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:10:47 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/10/28 16:37:19 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int	handle_keypress(int keysym, t_data *data)
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
	if (keysym == XK_Left)
		data->player->key_states[7] = 1;
	if (keysym == XK_Right)
		data->player->key_states[8] = 1;
	if (keysym == XK_e
		&& data->map->map[(int)data->player->pos_y]
		[(int)data->player->pos_x] != '2')
		data->player->key_states[6] = 1;
	return (0);
}

void	go_pos(t_data *data, int open, int mult, double *pos)
{
	double	next_x;
	double	next_y;

	if (data->player->key_states[0] == 1)
	{
		next_x = pos[0] + pos[2] * (WLK_SPEED * mult);
		if ((data->map->map[(int)pos[1]][(int)next_x] != '1'
			&& (data->map->map[(int)pos[1]][(int)next_x] != '2' || open == 10)))
			pos[0] = next_x;
		next_y = pos[1] + pos[3] * (WLK_SPEED * mult);
		if ((data->map->map[(int)next_y][(int)pos[0]] != '1'
			&& (data->map->map[(int)next_y][(int)pos[0]] != '2' || open == 10)))
			pos[1] = next_y;
	}
	if (data->player->key_states[1] == 1)
	{
		next_x = pos[0] - pos[2] * (WLK_SPEED * mult);
		if ((data->map->map[(int)pos[1]][(int)next_x] != '1'
			&& (data->map->map[(int)pos[1]][(int)next_x] != '2' || open == 10)))
			pos[0] = next_x;
		next_y = pos[1] - pos[3] * (WLK_SPEED * mult);
		if ((data->map->map[(int)next_y][(int)pos[0]] != '1'
			&& (data->map->map[(int)next_y][(int)pos[0]] != '2' || open == 10)))
			pos[1] = next_y;
	}
}

void	go_plane(t_data *data, int open, int mult, double *pos)
{
	double	next_x;
	double	next_y;

	if (data->player->key_states[2] == 1)
	{
		next_x = pos[0] + data->player->plane_x * ((WLK_SPEED * mult) + 0.025);
		if (data->map->map[(int)pos[1]][(int)next_x] != '1'
		&& (data->map->map[(int)pos[1]][(int)next_x] != '2' || open == 10))
			pos[0] = next_x;
		next_y = pos[1] + data->player->plane_y * ((WLK_SPEED * mult) + 0.025);
		if (data->map->map[(int)next_y][(int)pos[0]] != '1'
		&& (data->map->map[(int)next_y][(int)pos[0]] != '2' || open == 10))
			pos[1] = next_y;
	}
	if (data->player->key_states[3] == 1)
	{
		next_x = pos[0] - data->player->plane_x * ((WLK_SPEED * mult) + 0.025);
		if (data->map->map[(int)pos[1]][(int)next_x] != '1'
		&& (data->map->map[(int)pos[1]][(int)next_x] != '2' || open == 10))
			pos[0] = next_x;
		next_y = pos[1] - data->player->plane_y * ((WLK_SPEED * mult) + 0.025);
		if (data->map->map[(int)next_y][(int)pos[0]] != '1'
		&& (data->map->map[(int)next_y][(int)pos[0]] != '2' || open == 10))
			pos[1] = next_y;
	}
}

void	movement_handler(t_data *data)
{
	int		mult;
	int		open;
	double	pos[4];
	t_doors	*closest;

	open = 100;
	pos[0] = data->player->pos_x;
	pos[1] = data->player->pos_y;
	pos[2] = data->player->dir_x;
	pos[3] = data->player->dir_y;
	mult = 1;
	closest = open_closest_door(data);
	if (closest)
		open = closest->open;
	if (data->player->key_states[4] == 1)
		mult = 2;
	go_pos(data, open, mult, pos);
	go_plane(data, open, mult, pos);
	data->player->pos_x = pos[0];
	data->player->pos_y = pos[1];
	arrow_handler(data->player);
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
	if (keysym == XK_Left)
		data->player->key_states[7] = 0;
	if (keysym == XK_Right)
		data->player->key_states[8] = 0;
	return (0);
}
