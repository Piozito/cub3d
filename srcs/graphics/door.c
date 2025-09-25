/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:16:35 by pio               #+#    #+#             */
/*   Updated: 2025/09/25 17:10:37 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

t_doors	*open_door_helper_2(t_doors *active_door, int *flag, int *key)
{
	if (*flag == 2 && active_door->open < 100)
	{
		active_door->open += 2;
		if (active_door->open >= 100)
		{
			active_door->open = 100;
			*key = 0;
		}
	}
	else if (*flag == 1 && active_door->open > 10)
	{
		active_door->open -= 2;
		if (active_door->open <= 10)
		{
			active_door->open = 10;
			*key = 0;
		}
	}
	return (active_door);
}

t_doors	*open_door_helper(t_doors *active_door, int *flag, int *key)
{
	if (active_door && active_door->open == 100)
		*flag = 1;
	else if (active_door && active_door->open == 10)
		*flag = 2;
	if (active_door && *key == 1)
		open_door_helper_2(active_door, flag, key);
	return (active_door);
}

t_doors	*open_closest_door(t_data *data)
{
	static int		key = 0;
	static int		flag = 0;
	static t_doors	*active_door = NULL;
	double			min_dist;
	t_doors			*door;
	double			dx;
	double			dy;
	double			dist;
	int				i;

	i = 0;
	min_dist = 1e9;
	if (!active_door || active_door->open == 100 || active_door->open == 10)
	{
		key = 0;
		while (i < data->map->door_num)
		{
			door = data->map->doors[i];
			dx = door->coords[1] + 0.5 - data->player->pos_x;
			dy = door->coords[0] + 0.5 - data->player->pos_y;
			dist = dx * dx + dy * dy;
			if (dist < min_dist)
			{
				min_dist = dist;
				active_door = door;
			}
			i++;
		}
		if (min_dist < 5 && data->player->key_states[6] == 1)
			key = 1;
	}
	if (active_door && active_door->open == 100)
		flag = 1;
	else if (active_door && active_door->open == 10)
		flag = 2;
	active_door = open_door_helper(active_door, &flag, &key);
	return (active_door);
}
