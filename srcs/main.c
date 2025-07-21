/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:11:51 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/07/21 16:06:25 by fragarc2         ###   ########.fr       */
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
		str = get_next_line(data->map.fd);
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
		data->map.fd = open(argv[1], O_RDONLY);
		init(data);
		if (get_textures(data, argv) == 1 || parsing(data) == 1)
		{
			printf("Error\nInvalid map.\n");
			ft_clear(data);
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
	mlx_starter(data);
	vectors(data);
	return (0);
}
