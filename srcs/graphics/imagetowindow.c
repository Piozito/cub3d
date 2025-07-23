/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imagetowindow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:01:15 by fragarc2          #+#    #+#             */
/*   Updated: 2025/07/23 18:01:43 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	chars(t_data *data, int width, int i, int j)
{
	if (data->map->map[i][j] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->image->wall, width, i
			* IMG_SIZE);
	else if (data->map->map[i][j] == '0')
		mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->image->ground, width, i
			* IMG_SIZE);
	else if (data->map->map[i][j] == 'N')
		mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->image->wall_n, width, i
			* IMG_SIZE);
	else if (data->map->map[i][j] == 'S')
		mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->image->wall_s, width, i
			* IMG_SIZE);
	else if (data->map->map[i][j] == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->image->wall_e, width, i
			* IMG_SIZE);
	else if (data->map->map[i][j] == 'W')
	{
		mlx_put_image_to_window(data->mlx_ptr, data->window_ptr, data->image->wall_w, width, i
			* IMG_SIZE);
	}
}

int	render(t_data *data)
{
	int		i;
	size_t	j;
	int		width;

	if (data->win == NULL)
		return (1);
	i = 0;
	j = 0;
	width = 0;
	while (data->map->map[i])
	{
		while (data->map->map[i][j] && data->map->map[i][j] != '\n')
		{
			chars(data, width, i, j);
			width += IMG_SIZE;
			j++;
		}
		j = 0;
		width = 0;
		i++;
	}
	return (0);
}
