/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:40:43 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/09/08 12:40:43 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	draw_circle(void *mlx_ptr, int radius, int color)
{
	int	y;
	int	x;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				my_mlx_pixel_put(mlx_ptr, MP_CTR + y, MP_CTR + x, color);
			x++;
		}
		y++;
	}
}

void	draw_help(int *delta, int *step, int *err, int *crds)
{
	err[1] = 2 * err[0];
	if (err[1] >= delta[1])
	{
		err[0] += delta[1];
		crds[0] += step[0];
	}
	if (err[1] <= delta[0])
	{
		err[0] += delta[0];
		crds[1] += step[1];
	}
}

void	draw_line_help(void *mlx_ptr, int *cords)
{
	my_mlx_pixel_put(mlx_ptr, cords[0], cords[1], 0xFF0000);
	my_mlx_pixel_put(mlx_ptr, cords[0] - 1, cords[1] - 1, 0xFF0000);
	my_mlx_pixel_put(mlx_ptr, cords[0] + 1, cords[1] - 1, 0xFF0000);
	my_mlx_pixel_put(mlx_ptr, cords[0] - 1, cords[1] + 1, 0xFF0000);
	my_mlx_pixel_put(mlx_ptr, cords[0] + 1, cords[1] + 1, 0xFF0000);
}

void	draw_line(void *mlx_ptr, int *ends)
{
	int	delta[2];
	int	step[2];
	int	err[2];
	int	cords[2];

	cords[0] = MP_CTR;
	cords[1] = MP_CTR;
	delta[0] = abs(ends[0] - cords[0]);
	if (cords[0] < ends[0])
		step[0] = 1;
	else
		step[0] = -1;
	delta[1] = -abs(ends[1] - cords[1]);
	if (cords[1] < ends[1])
		step[1] = 1;
	else
		step[1] = -1;
	err[0] = delta[0] + delta[1];
	while (1)
	{
		draw_line_help(mlx_ptr, cords);
		if (cords[0] == ends[0] && cords[1] == ends[1])
			break ;
		draw_help(delta, step, err, cords);
	}
}

void	circle_help(void *mlx_ptr, int *crds, int color)
{
	if (MP_CTR + crds[0] >= 0 && MP_CTR + crds[1] >= 0)
		my_mlx_pixel_put(mlx_ptr, MP_CTR + crds[0], MP_CTR + crds[1], color);
	if (MP_CTR + crds[1] >= 0 && MP_CTR + crds[0] >= 0)
		my_mlx_pixel_put(mlx_ptr, MP_CTR + crds[1], MP_CTR + crds[0], color);
	if (MP_CTR - crds[1] >= 0 && MP_CTR + crds[0] >= 0)
		my_mlx_pixel_put(mlx_ptr, MP_CTR - crds[1], MP_CTR + crds[0], color);
	if (MP_CTR - crds[0] >= 0 && MP_CTR + crds[1] >= 0)
		my_mlx_pixel_put(mlx_ptr, MP_CTR - crds[0], MP_CTR + crds[1], color);
	if (MP_CTR - crds[0] >= 0 && MP_CTR - crds[1] >= 0)
		my_mlx_pixel_put(mlx_ptr, MP_CTR - crds[0], MP_CTR - crds[1], color);
	if (MP_CTR - crds[1] >= 0 && MP_CTR - crds[0] >= 0)
		my_mlx_pixel_put(mlx_ptr, MP_CTR - crds[1], MP_CTR - crds[0], color);
	if (MP_CTR + crds[1] >= 0 && MP_CTR - crds[0] >= 0)
		my_mlx_pixel_put(mlx_ptr, MP_CTR + crds[1], MP_CTR - crds[0], color);
	if (MP_CTR + crds[0] >= 0 && MP_CTR - crds[1] >= 0)
		my_mlx_pixel_put(mlx_ptr, MP_CTR + crds[0], MP_CTR - crds[1], color);
}
