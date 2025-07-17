/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:51:47 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/07/17 13:54:05 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

static size_t	ft_prvstrlen(char *str)
{
	size_t	i;
	size_t	last_char;

	i = 0;
	last_char = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			last_char = i + 1;
		i++;
	}
	return (last_char);
}

size_t	get_biggest_line(char **map)
{
	size_t	i;
	size_t	biggest_line;
	size_t	len;

	i = 0;
	biggest_line = 0;
	while (map[i])
	{
		len = ft_prvstrlen(map[i]);
		if (len > biggest_line)
			biggest_line = len;
		i++;
	}
	return (biggest_line);
}

int	line_checker(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (1);
	while (line[i])
	{
		if (line[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	top_and_bottom(char **map)
{
	size_t	i;
	size_t	j;
	size_t	biggest_line;
	char	*first_line;
	char	*last_line;

	i = 0;
	biggest_line = get_biggest_line(map);
	first_line = ft_calloc(biggest_line + 1, sizeof(char));
	last_line = ft_calloc(biggest_line + 1, sizeof(char));
	if (!first_line || !last_line)
	{
		free(first_line);
		free(last_line);
		return (1);
	}
	while (map[i])
	{
		j = 0;
		while (j < biggest_line)
		{
			if (j < ft_strlen(map[i]) && map[i][j])
			{
				if ((!first_line[j] && map[i][j] != ' ' && map[i][j] != '\t')
					|| first_line[j] == ' ' || first_line[j] == '\t')
					first_line[j] = map[i][j];
				if (map[i][j] != ' ' && map[i][j] != '\t')
					last_line[j] = map[i][j];
			}
			j++;
		}
		i++;
	}
	first_line[biggest_line] = '\0';
	last_line[biggest_line] = '\0';
	if (line_checker(first_line) == 1 || line_checker(last_line) == 1)
	{
		free(first_line);
		free(last_line);
		return (1);
	}
	free(first_line);
	free(last_line);
	return (0);
}

int	check_last_char(char *line)
{
	ssize_t	i;

	i = 0;
	while (line[i])
		i++;
	if (i > 0)
		i--;
	while (i >= 0 && (line[i] == ' ' || line[i] == '\t'))
		i--;
	if (i < 0 || line[i] != '1')
		return (1);
	return (0);
}

int	line_check(char **map)
{
	ssize_t	i;
	ssize_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ' || map[i][j] == '\t')
			j++;
		if (map[i][j] != '1' || check_last_char(map[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	floodfill(t_data *data, char **visited, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map.map_height
		|| y >= (int)get_biggest_line(data->map.map)
		|| data->map.map[x][y] == '1' || visited[x][y])
		return ;
	if (data->map.map[x][y] == ' ' || data->map.map[x][y] == '\t')
	{
		visited[x][y] = '2';
		return ;
	}
	visited[x][y] = '1';
	floodfill(data, visited, x + 1, y);
	floodfill(data, visited, x - 1, y);
	floodfill(data, visited, x, y + 1);
	floodfill(data, visited, x, y - 1);
}

int	find_spawn(t_data *data, char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	data->map.spawn[0] = -1;
	data->map.spawn[1] = -1;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (data->map.spawn[0] != -1 || data->map.spawn[1] != -1)
					return (1);
				data->map.spawn[0] = i;
				data->map.spawn[1] = j;
			}
			j++;
		}
		i++;
	}
	data->map.map_height = i;
	if (data->map.spawn[0] == -1 || data->map.spawn[1] == -1)
		return (1);
	return (0);
}

int	flood(t_data *data)
{
	char	**visited;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = get_biggest_line(data->map.map);
	visited = ft_calloc(data->map.map_height + 1, sizeof(char *));
	if (!visited)
		return (1);
	while (i < data->map.map_height)
	{
		visited[i] = (char *)ft_calloc(len + 1, sizeof(char));
		if (!visited[i])
			return (1);
		i++;
	}
	floodfill(data, visited, data->map.spawn[0], data->map.spawn[1]);
	i = 0;
	while (i < data->map.map_height)
	{
		j = 0;
		while (j < len)
		{
			if (visited[i][j] == '2')
			{
				int k = 0;
				while (k < data->map.map_height)
					free(visited[k++]);
				free(visited);
				return (1);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < data->map.map_height)
		free(visited[i++]);
	free(visited);
	return (0);
}

int	parsing(t_data *data)
{
	if (top_and_bottom(data->map.map) == 1)
		return (1);
	if (line_check(data->map.map) == 1)
		return (1);
	if (find_spawn(data, data->map.map) == 1)
		return (1);
	if (flood(data) == 1)
		return (1);
	return (0);
}