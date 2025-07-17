/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:25:23 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/07/17 13:23:26 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void ft_debug(t_data *data)
{
	ssize_t i = 0;
	if(data->map.north)
		printf("North: %s\n", data->map.north);
	if(data->map.south)
		printf("South: %s\n", data->map.south);
	if(data->map.west)
		printf("West: %s\n", data->map.west);
	if(data->map.east)
		printf("East: %s\n", data->map.east);
	if(data->map.floor)
		printf("Floor: %s\n", data->map.floor);
	if(data->map.celling)
		printf("Celling: %s\n", data->map.celling);
	printf("Map:\n");
	while(data->map.map[i])
		printf("%s\n", data->map.map[i++]);
}

void ft_clear(t_data *data)
{
	ssize_t i = 0;
	if(data->map.north)
		free(data->map.north);
	if(data->map.south)
		free(data->map.south);
	if(data->map.west)
		free(data->map.west);
	if(data->map.east)
		free(data->map.east);
	if(data->map.floor)
		free(data->map.floor);
	if(data->map.celling)
		free(data->map.celling);
	if (data->map.map)
	{
		while (data->map.map[i])
			free(data->map.map[i++]);
		free(data->map.map);
	}
	free(data);
}

ssize_t find_char(const char *str, char c, ssize_t len)
{
	ssize_t i = 0;
	ssize_t found = 0;
	while(i < len)
	{
		if(str[i] == c)
			found++;
		i++;
	}
	return found;
}

ssize_t get_file_lines(char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	char *str = malloc(BUFFER_SIZE + 1);
	ssize_t bytes_read;
	ssize_t lines = 0;
	while(str)
	{
		bytes_read = read(fd, str, BUFFER_SIZE);
		if(bytes_read <= 0)
			break;
		str[bytes_read] = '\0';
		lines += find_char(str, '\n', bytes_read);
	}
	lines++;
	free(str);
	close(fd);
	return lines + 1;
}

char *ft_strndup(char *s, int n)
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	while (s[i] != '\0')
		i++;
	if(i - n < 0)
		return (NULL);
	ptr = (char *)malloc((i - n + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i + n] != '\0' && s[i + n] != '\n')
	{
		ptr[i] = s[i + n];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}