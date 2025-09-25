/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:59:14 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/09/25 13:53:07 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	init_file(t_data *data, char *file)
{
	data->image = prep_img();
	data->map->north = prep_img();
	data->map->south = prep_img();
	data->map->east = prep_img();
	data->map->west = prep_img();
	data->map->door_top = prep_img();
	data->map->door_bot = prep_img();
	data->map->fd = open(file, O_RDONLY);
	if (data->map->fd <= 0)
	{
		printf("Error\nInvalid map.\n");
		ft_clear(data);
	}
}

void	init_data_structs(t_data *data, char *file)
{
	int	i;

	i = 0;
	data->mlx_ptr = NULL;
	data->window_ptr = NULL;
	data->player = malloc(sizeof(t_player));
	data->player->dir_x = 0.0;
	data->player->dir_y = 0.0;
	data->player->plane_x = 0.0;
	data->player->plane_y = 0.0;
	data->player->tex_x = 0;
	data->player->tex_y = 0;
	while (i < 7)
		data->player->key_states[i++] = 0;
	data->map = malloc(sizeof(t_map));
	data->map->celling = 0;
	data->map->floor = 0;
	data->map->spawn[0] = -1;
	data->map->spawn[1] = -1;
	data->map->door_num = 0;
	data->map->map_height = 0;
	data->map->map_lenght = 0;
	init_file(data, file);
}

void	free_img(void *mlx, t_im *im)
{
	if (im)
	{
		if (im->file)
			free(im->file);
		if (im->mlx_img)
			mlx_destroy_image(mlx, im->mlx_img);
		free(im);
	}
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

int	ft_clear(t_data *data)
{
	free_img(data->mlx_ptr, data->map->north);
	free_img(data->mlx_ptr, data->map->south);
	free_img(data->mlx_ptr, data->map->east);
	free_img(data->mlx_ptr, data->map->west);
	free_img(data->mlx_ptr, data->map->door_top);
	free_img(data->mlx_ptr, data->map->door_bot);
	free_img(data->mlx_ptr, data->image);
	free_doors(data);
	if (data->player)
		free(data->player);
	if (data->window_ptr)
		mlx_destroy_window(data->mlx_ptr, data->window_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (data)
		free(data);
	exit(0);
	return (0);
}
