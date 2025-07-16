/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:11:51 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/07/16 13:47:11 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/cub3d.h"

void get_textures(t_data *data)
{
	char *str;
	while(1)
	{
		str = get_next_line(data->map.fd);
		if(!str)
			break;
		else if(strncmp(str, "NO ", 3) == 0)
			data->map.north = ft_strndup(str, 3);
		else if(strncmp(str, "SO ", 3) == 0)
			data->map.south = ft_strndup(str, 3);
		else if(strncmp(str, "WE ", 3) == 0)
			data->map.west = ft_strndup(str, 3);
		else if(strncmp(str, "EA ", 3) == 0)
			data->map.east = ft_strndup(str, 3);
		free(str);
	}
}

void ft_debug(t_data *data)
{
	if(data->map.north)
		printf("North: %s\n", data->map.north);
	if(data->map.south)
		printf("South: %s\n", data->map.south);
	if(data->map.west)
		printf("West: %s\n", data->map.west);
	if(data->map.east)
		printf("East: %s\n", data->map.east);
}

void ft_clear(t_data *data)
{
	if(data->map.north)
		free(data->map.north);
	if(data->map.south)
		free(data->map.south);
	if(data->map.west)
		free(data->map.west);
	if(data->map.east)
		free(data->map.east);
	free(data);
}

int main(int argc, char **argv)
{
	if(argc == 2)
	{
		t_data *data;

		(void)argv;
		data = malloc(sizeof(t_data));
		data->map.fd = open(argv[1], O_RDONLY);
		get_textures(data);
		ft_debug(data);
		ft_clear(data);
	}
	else
	{
		printf("Incorrect amount of arguments\n");
		return 1;
	}
	return 0;
}
