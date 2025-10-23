/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:16:35 by pio               #+#    #+#             */
/*   Updated: 2025/10/21 12:21:24 by fragarc2         ###   ########.fr       */
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

double	*helper_door(t_data *data, double *d, t_doors **a_d, t_doors **door)
{
	*door = data->map->doors[(int)d[4]];
	d[0] = (*door)->coords[1] + 0.5 - data->player->pos_x;
	d[1] = (*door)->coords[0] + 0.5 - data->player->pos_y;
	d[2] = d[0] * d[0] + d[1] * d[1];
	if (d[2] < d[3])
	{
		d[3] = d[2];
		*a_d = *door;
	}
	return (d);
}

/*d[0] = dx, d[1] = dy, d[2] = dist, d[3] = dist, d[4] = i*/

t_doors	*open_closest_door(t_data *data)
{
	static t_doors	*active_door;
	t_doors			*door;
	double			d[5];

	d[4] = 0;
	d[3] = 1e9;
	door = NULL;
	if (!active_door || active_door->open == 100 || active_door->open == 10)
	{
		data->map->key = 0;
		while (d[4] < data->map->door_num)
		{
			helper_door(data, d, &active_door, &door);
			d[4]++;
		}
		if (d[3] < 5 && data->player->key_states[6] == 1)
			data->map->key = 1;
	}
	if (active_door && active_door->open == 100)
		data->map->flag = 1;
	else if (active_door && active_door->open == 10)
		data->map->flag = 2;
	active_door = open_door_helper
		(active_door, &data->map->flag, &data->map->key);
	return (active_door);
}
