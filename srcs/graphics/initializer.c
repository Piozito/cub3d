/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:47:32 by pio               #+#    #+#             */
/*   Updated: 2025/09/25 17:04:49 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	my_mlx_pixel_put(t_im *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(int *)dst = color;
}

void	*my_mlx_xpm_image(t_data *data, char *file)
{
	int	width;
	int	height;

	width = data->image->width;
	height = data->image->height;
	return (mlx_xpm_file_to_image(data->mlx_ptr, file, &width, &height));
}

void	*my_addr(t_im *dir)
{
	return (mlx_get_data_addr(dir->mlx_img, &dir->bpp,
			&dir->line_length, &dir->endian));
}

void	door_initialiser(t_data *data)
{
	data->map->door_top->mlx_img = my_mlx_xpm_image(data,
			data->map->door_top->file);
	data->map->door_top->addr = my_addr(data->map->door_top);
	data->map->door_bot->mlx_img = my_mlx_xpm_image(data,
			data->map->door_bot->file);
	data->map->door_bot->addr = my_addr(data->map->door_bot);
}

void	tex_initialiser(t_data *data)
{
	data->map->east->mlx_img = my_mlx_xpm_image(data, data->map->east->file);
	data->map->east->addr = my_addr(data->map->east);
	data->map->north->mlx_img = my_mlx_xpm_image(data, data->map->north->file);
	data->map->north->addr = my_addr(data->map->north);
	data->map->south->mlx_img = my_mlx_xpm_image(data, data->map->south->file);
	data->map->south->addr = my_addr(data->map->south);
	data->map->west->mlx_img = my_mlx_xpm_image(data, data->map->west->file);
	data->map->west->addr = my_addr(data->map->west);
	door_initialiser(data);
}
