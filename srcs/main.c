/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:11:51 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/09/17 14:07:43 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/cub3d.h"

void	flag(int *flags)
{
	ssize_t	i;

	i = 0;
	while (i < 10)
		flags[i++] = 0;
}

int	get_textures(t_data *data, char **argv)
{
	char	*str;
	char	**map;
	ssize_t	i;
	int		flags[10];
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

int	check_attribute(char *str)
{
	char	*attr[11];
	ssize_t	i;

	i = 0;
	attr[0] = "NO ";
	attr[1] = "SO ";
	attr[2] = "WE ";
	attr[3] = "EA ";
	attr[4] = "F ";
	attr[5] = "C ";
	attr[6] = "D ";
	attr[7] = "D1 ";
	attr[8] = "D2 ";
	attr[9] = "D3 ";
	attr[10] = NULL;
	while (attr[i])
	{
		if (ft_strncmp(attr[i], str, ft_strlen(attr[i])) == 0)
			break ;
		i++;
	}
	if (i < 10)
		return (i);
	else
		return (-1);
}

void	set_hooks(t_data *data)
{
	mlx_starter(data);
	//mlx_mouse_hide causes leaks!!!
	mlx_mouse_hide(data->mlx_ptr, data->window_ptr);
	mlx_hook(data->window_ptr, DestroyNotify, NoEventMask, &ft_clear, data);
	mlx_hook(data->window_ptr, MotionNotify, PointerMotionMask, &camera_handler, data->player);
	mlx_hook(data->window_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->window_ptr, KeyRelease, KeyReleaseMask,
		&handle_btnrelease, data);
	mlx_loop_hook(data->mlx_ptr, vectors, data);
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
		}
		ft_debug(data);
		set_hooks(data);
		mlx_loop(data->mlx_ptr);
		ft_clear(data);
		return (0);
	}
	else
		printf("Error\nIncorrect amount of arguments.\n");
	return (1);
}
