/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:07:30 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/09/08 13:07:30 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

t_im	*prep_img(void)
{
	t_im	*im;

	im = malloc(sizeof(t_im));
	im->mlx_img = NULL;
	im->addr = NULL;
	im->bpp = 0;
	im->line_length = 0;
	im->endian = 0;
	im->file = NULL;
	return (im);
}

void	free_doors(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		if (data->map->doors && data->map->door_num > 0)
		{
			while (i < data->map->door_num && data->map->doors)
			{
				if (data->map->doors[i])
					free(data->map->doors[i]);
				i++;
			}
			if (data->map->doors)
				free(data->map->doors);
		}
		free_map(data->map);
	}
}
