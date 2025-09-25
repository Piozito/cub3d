/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:25:23 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/09/25 17:07:52 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	ft_debug(t_data *data)
{
	ssize_t	i;

	i = 0;
	if (data->map->north->file)
		printf("North: %s\n", data->map->north->file);
	if (data->map->south->file)
		printf("South: %s\n", data->map->south->file);
	if (data->map->west->file)
		printf("West: %s\n", data->map->west->file);
	if (data->map->east->file)
		printf("East: %s\n", data->map->east->file);
	if (data->map->door_top->file)
		printf("Door top: %s\n", data->map->door_top->file);
	if (data->map->door_bot->file)
		printf("Door bot: %s\n", data->map->door_bot->file);
	if (data->map->floor)
		printf("Floor: %d\n", data->map->floor);
	if (data->map->celling)
		printf("Celling: %d\n", data->map->celling);
	if (data->map->spawn[0] && data->map->spawn[1])
	{
		printf("Spawn X: %d\n", data->map->spawn[0]);
		printf("Spawn Y: %d\n", data->map->spawn[1]);
	}
	printf("Map:\n");
	while (data->map->map[i])
		printf("%s\n", data->map->map[i++]);
	i = 0;
	printf("Amount of doors: %d\n", data->map->door_num);
	while (i < data->map->door_num)
	{
		printf("--------------------\n");
		printf("x: %d\n", data->map->doors[i]->coords[0]);
		printf("y: %d\n", data->map->doors[i]->coords[1]);
		printf("open: %d\n", data->map->doors[i]->open);
		i++;
	}
}

ssize_t	find_char(const char *str, char c, ssize_t len)
{
	ssize_t	i;
	ssize_t	found;

	i = 0;
	found = 0;
	while (i < len)
	{
		if (str[i] == c)
			found++;
		i++;
	}
	return (found);
}

ssize_t	get_file_lines(char **argv)
{
	int		fd;
	char	*str;
	ssize_t	bytes_read;
	ssize_t	lines;

	fd = open(argv[1], O_RDONLY);
	str = malloc(BUFFER_SIZE + 1);
	lines = 0;
	while (str)
	{
		bytes_read = read(fd, str, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		str[bytes_read] = '\0';
		lines += find_char(str, '\n', bytes_read);
	}
	lines++;
	free(str);
	close(fd);
	return (lines + 1);
}

char	*ft_strndup(char *s, int n)
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	while (s[i] != '\0')
		i++;
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

int	line_checker(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (1);
	}
	while (line[i])
	{
		if (line[i] != '1')
		{
			free(line);
			return (1);
		}
		i++;
	}
	free(line);
	return (0);
}
