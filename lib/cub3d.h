/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:08:46 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/07/16 12:47:10 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdlib.h>
#include <unistd.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "./libft/libft.h"
#include "./minilibx-linux/mlx.h"

#define NORTH "../textures/north"
#define SOUTH "../textures/south"
#define EAST "../textures/east"
#define WEST "../textures/west"

typedef struct	s_map
{
	int			fd;
	void		*north;
	void		*south;
	void		*east;
	void		*west;
	void		*celling;
	void		*floor;
	char		**map;
}				t_map;

typedef struct	s_data
{
	void		*mlx;
	t_map		map;
}				t_data;

#endif