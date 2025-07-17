/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:08:46 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/07/17 13:21:40 by aaleixo-         ###   ########.fr       */
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

typedef struct	s_map
{
	int			fd;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*celling;
	char		*floor;
	int			spawn[2];
	int		map_height;
	int		map_lenght;
	char		**map;
}				t_map;

typedef struct	s_data
{
	void		*mlx;
	t_map		map;
}				t_data;

ssize_t get_file_lines(char **argv);
ssize_t find_char(const char *str, char c, ssize_t len);
char *ft_strndup(char *s, int n);
void map_setter(t_data *data, ssize_t j, char **map);
void ft_debug(t_data *data);
void ft_clear(t_data *data);
int parsing(t_data *data);

#endif