/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:59:14 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/08/27 11:13:44 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	free_img(void *mlx, t_im *im)
{
	if (im->mlx_img)
		mlx_destroy_image(mlx, im->mlx_img);
	free(im);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->fd)
		close(map->fd);
	if (map->map)
	{
		while (map->map[i])
			free(map->map[i++]);
		free(map->map);
	}
	if (map)
		free(map);
}

void	ft_clear(t_data *data)
{
	ssize_t	i;

	i = 0;
	free_img(data->mlx_ptr, data->map->north);
	free_img(data->mlx_ptr, data->map->south);
	free_img(data->mlx_ptr, data->map->east);
	free_img(data->mlx_ptr, data->map->west);
	free_img(data->mlx_ptr, data->map->door);
	free_img(data->mlx_ptr, data->image);
	free_map(data->map);
	if(data->player)
		free(data->player);
	if(data->window_ptr)
    	mlx_destroy_window(data->mlx_ptr, data->window_ptr);
	if(data->mlx_ptr)
		free(data->mlx_ptr);
	free(data);
	exit(0);
}
