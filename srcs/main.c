/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:11:51 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/08/12 12:23:44 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/cub3d.h"

void	flag(int *flags)
{
	ssize_t	i;

	i = 0;
	while (i < 6)
		flags[i++] = 0;
}

int	get_textures(t_data *data, char **argv)
{
	char	*str;
	char	**map;
	ssize_t	i;
	int		flags[6];
	int		help;

	i = 0;
	help = 0;
	str = "";
	map = malloc(sizeof(char *) * get_file_lines(argv));
	flag(flags);
	while (str)
	{
		str = get_next_line(data->map->fd);
		help = loop_help(data, str, flags);
		if (help == 1)
			break ;
		else if (help == 2)
			continue ;
		map[i++] = ft_strndup(str, 0);
		free(str);
	}
	map[i] = NULL;
	map_setter(data, i, map);
	return (check_flag(flags));
}


void init_data_structs(t_data *data, char *file)
{
	data->mlx_ptr = NULL;
	data->window_ptr = NULL;
	data->img_ptr = NULL;

	data->image = malloc(sizeof(t_im));
	data->image->mlx_img = NULL;
	data->image->addr = NULL;
	data->image->bpp = 0;
	data->image->line_length = 0;
	data->image->endian = 0;

	data->player = malloc(sizeof(t_player));
	data->player->pos_x = 0.0;
	data->player->pos_y = 0.0;
	data->player->dir_x = 0.0;
	data->player->dir_y = 0.0;
	data->player->plane_x = 0.0;
	data->player->plane_y = 0.0;
	data->player->ray_dir_x = 0.0;
	data->player->ray_dir_y = 0.0;
	data->player->camera_x = 0.0;
	data->player->angle = 0.0;

	data->player->map_x = 0;
	data->player->map_y = 0;
	data->player->delta_dist_x = 0.0;
	data->player->delta_dist_y = 0.0;
	data->player->step_x = 0;
	data->player->step_y = 0;
	data->player->side_dist_x = 0.0;
	data->player->side_dist_y = 0.0;

	data->player->perp_wall_dist = 0.0;
	data->player->wall_x = 0.0;
	data->player->line_height = 0;
	data->player->draw_start = 0;
	data->player->draw_end = 0;
	data->player->tex_x = 0;
	data->player->tex_y = 0;

	data->map = malloc(sizeof(t_map));
	data->map->map = NULL;

	data->map->north = malloc(sizeof(t_im));
	data->map->north->mlx_img = NULL;
	data->map->north->addr = NULL;
	data->map->north->bpp = 0;
	data->map->north->line_length = 0;
	data->map->north->endian = 0;

	data->map->south = malloc(sizeof(t_im));
	data->map->south->mlx_img = NULL;
	data->map->south->addr = NULL;
	data->map->south->bpp = 0;
	data->map->south->line_length = 0;
	data->map->south->endian = 0;

	data->map->east = malloc(sizeof(t_im));
	data->map->east->mlx_img = NULL;
	data->map->east->addr = NULL;
	data->map->east->bpp = 0;
	data->map->east->line_length = 0;
	data->map->east->endian = 0;

	data->map->west = malloc(sizeof(t_im));
	data->map->west->mlx_img = NULL;
	data->map->west->addr = NULL;
	data->map->west->bpp = 0;
	data->map->west->line_length = 0;
	data->map->west->endian = 0;

	data->map->celling = 0;
	data->map->floor = 0;
	data->map->spawn[0] = -1;
	data->map->spawn[1] = -1;
	data->map->map_height = 0;
	data->map->map_lenght = 0;
	data->map->fd = open(file, O_RDONLY);
	if (data->map->fd <= 0)
	{
		printf("Error\nInvalid map.\n");
		free(data);
		exit(1);
	}

}


int	check_attribute(char *str)
{
	char	*attr[7];
	ssize_t	i;

	i = 0;
	attr[0] = "NO ";
	attr[1] = "SO ";
	attr[2] = "WE ";
	attr[3] = "EA ";
	attr[4] = "F ";
	attr[5] = "C ";
	attr[6] = NULL;
	while (attr[i])
	{
		if (ft_strncmp(attr[i], str, ft_strlen(attr[i])) == 0)
			break ;
		i++;
	}
	if (i < 6)
		return (i);
	else
		return (-1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 2)
	{
		ext_checker(argv[1]);
		data = malloc(sizeof(t_data));
		init_data_structs(data, argv[1]);
		if (get_textures(data, argv) == 1 || parsing(data) == 1)
		{
			printf("Error\nInvalid map.\n");
			ft_debug(data);
			ft_clear(data);
			exit(1);
		}
		data->player->pos_x = data->map->spawn[1];
		data->player->pos_y = data->map->spawn[0] - 1;
		ft_debug(data);
		mlx_starter(data);
		mlx_hook(data->window_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
		mlx_hook(data->window_ptr, ClientMessage, LeaveWindowMask,
			&handle_btnrelease, &data);
		mlx_loop_hook(data->mlx_ptr, vectors, data);
		mlx_loop(data->mlx_ptr);
		ft_clear(data);
	}
	else
	{
		printf("Error\nIncorrect amount of arguments.\n");
		return (1);
	}
	return (0);
}

