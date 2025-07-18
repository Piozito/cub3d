/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:11:51 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/07/17 15:30:35 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/cub3d.h"

void	map_setter(t_data *data, ssize_t j, char **map)
{
	ssize_t	i;

	i = 0;
	data->map.map = malloc(sizeof(char *) * (j + 1));
	while (map[i])
	{
		data->map.map[i] = ft_strdup(map[i]);
		free(map[i]);
		i++;
	}
	free(map);
	data->map.map[i] = NULL;
}

int	texture_help(t_data *data, char *str)
{
	if (!strncmp(str, "NO ", 3))
		data->map.north = ft_strndup(str, 3);
	else if (!strncmp(str, "SO ", 3))
		data->map.south = ft_strndup(str, 3);
	else if (!strncmp(str, "WE ", 3))
		data->map.west = ft_strndup(str, 3);
	else if (!strncmp(str, "EA ", 3))
		data->map.east = ft_strndup(str, 3);
	else if (!strncmp(str, "F ", 2))
		data->map.floor = ft_strndup(str, 2);
	else if (!strncmp(str, "C ", 2))
		data->map.celling = ft_strndup(str, 2);
	else
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

void	get_textures(t_data *data, char **argv)
{
	char	*str;
	char	**map;
	ssize_t	i;

	i = 0;
	map = malloc(sizeof(char *) * get_file_lines(argv));
	str = "";
	while (str)
	{
		str = get_next_line(data->map.fd);
		if (str && str[0] == '\n')
		{
			free(str);
			continue ;
		}
		if (!str)
			break ;
		else if (texture_help(data, str) == 0)
			continue ;
		else
			map[i++] = ft_strndup(str, 0);
		free(str);
	}
	map[i] = NULL;
	map_setter(data, i, map);
}

void	init(t_data *data)
{
	data->map.spawn[0] = -1;
	data->map.spawn[1] = -1;
	data->map.map_height = 0;
	data->map.map_lenght = 0;
	if (data->map.fd <= 0)
	{
		printf("Error\nInvalid map.\n");
		free(data);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 2)
	{
		ext_checker(argv[1]);
		data = malloc(sizeof(t_data));
		data->map.fd = open(argv[1], O_RDONLY);
		init(data);
		get_textures(data, argv);
		if (parsing(data) == 1)
		{
			printf("Error\nInvalid map.\n");
			exit(1);
		}
		ft_debug(data);
		ft_clear(data);
	}
	else
	{
		printf("Error\nIncorrect amount of arguments.\n");
		return (1);
	}
	return (0);
}
