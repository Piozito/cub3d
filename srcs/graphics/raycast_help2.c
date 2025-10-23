/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_help2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:52:42 by fragarc2          #+#    #+#             */
/*   Updated: 2025/10/23 11:51:42 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	mlx_starter(t_data *data)
{
	char	*t;

	t = "cub3D - Made by fragarc2 and aaleixo-";
	data->mlx_ptr = mlx_init();
	data->window_ptr = mlx_new_window(data->mlx_ptr, W_W, W_H, t);
	data->image->mlx_img = mlx_new_image(data->mlx_ptr, W_W, W_H);
	data->image->addr = mlx_get_data_addr(data->image->mlx_img,
			&data->image->bpp,
			&data->image->line_length, &data->image->endian);
	tex_initialiser(data);
}

int	get_texel_color(t_im *texture, int tex_x, int tex_y)
{
	char	*tex_addr;

	tex_addr = texture->addr + (tex_y * texture->line_length
			+ tex_x * (texture->bpp / 8));
	return (*(int *)tex_addr);
}

t_im	*get_wall_texture(t_data *data)
{
	if (data->player->side == 0 && data->player->ray_dir_x > 0)
		return (data->map->east);
	else if (data->player->side == 0 && data->player->ray_dir_x < 0)
		return (data->map->west);
	else if (data->player->side == 1 && data->player->ray_dir_y > 0)
		return (data->map->south);
	else
		return (data->map->north);
}

int	limit(int i, int limit)
{
	if (i < 0)
		i = 0;
	if (i > limit)
		i = limit;
	return (i);
}

void	draw_limits(t_data *data)
{
	if (data->player->draw_start < 0)
		data->player->draw_start = 0;
	if (data->player->draw_end > W_H)
		data->player->draw_end = W_H;
	data->tex->wall_height = fabs((double)W_H / data->player->perp_wall_dist);
	data->tex->step = (double)TEXTURE_SIZE / data->tex->wall_height;
	data->tex->tex_pos = (data->player->draw_start
			- W_H / 2.0 + data->tex->wall_height / 2.0) * data->tex->step;
}
