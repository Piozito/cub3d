/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:38:33 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/09/25 13:38:33 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

int	camera_handler(int x, int y, t_player *player)
{
	static double	last_x = -1;
	double			rot_speed;
	double			old_dir_x;
	double			old_plane_x;
	int				delta_x;

	(void)y;
	if (last_x == -1)
		last_x = x;
	delta_x = x - last_x;
	if (delta_x == 0)
		return (0);
	rot_speed = (ROT_SPEED * delta_x);
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed)
		- player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed)
		+ player->dir_y * cos(rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed)
		- player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed)
		+ player->plane_y * cos(rot_speed);
	return (0);
}

void	arrow_handler(t_player *player)
{
	int		rot;
	double	old_dir_x;
	double	old_plane_x;

	if ((player->key_states[7] && player->key_states[8])
		|| (!player->key_states[7] && !player->key_states[8]))
		return ;
	rot = 1;
	if (player->key_states[7])
		rot = -1;
	old_dir_x = player->dir_x;
	player->dir_x = old_dir_x * cos((ROT_SPEED * 100) * rot)
		- player->dir_y * sin((ROT_SPEED * 100) * rot);
	player->dir_y = old_dir_x * sin((ROT_SPEED * 100) * rot)
		+ player->dir_y * cos((ROT_SPEED * 100) * rot);
	old_plane_x = player->plane_x;
	player->plane_x = old_plane_x * cos((ROT_SPEED * 100) * rot)
		- player->plane_y * sin((ROT_SPEED * 100) * rot);
	player->plane_y = old_plane_x * sin((ROT_SPEED * 100) * rot)
		+ player->plane_y * cos((ROT_SPEED * 100) * rot);
}
