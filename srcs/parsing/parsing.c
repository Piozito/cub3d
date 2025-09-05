/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:51:47 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/09/05 13:38:34 by aaleixo-         ###   ########.fr       */
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

int	flood(t_data *data)
{
	char	**visited;
	int		i;

	i = 0;
	data->map->map_lenght = get_biggest_line(data->map->map);
	visited = ft_calloc(data->map->map_height + 1, sizeof(char *));
	if (!visited)
		return (1);
	while (i < data->map->map_height)
	{
		visited[i] = (char *)ft_calloc(data->map->map_lenght + 1, sizeof(char));
		if (!visited[i])
			return (1);
		i++;
	}
	floodfill(data, visited, data->map->spawn[0], data->map->spawn[1]);
	if (check_visited(data, visited) == 1)
		return (1);
	i = 0;
	while (i < data->map->map_height)
		free(visited[i++]);
	free(visited);
	return (0);
}

int	check_next(char **map, int x, int y)
{
	if (map[x + 1][y] && map[x + 1][y] != '0' && map[x + 1][y] != '1' && map[x + 1][y] != '2')
		return (1);
	if (map[x - 1][y] && map[x - 1][y] != '0' && map[x - 1][y] != '1' && map[x - 1][y] != '2')
		return (1);
	if (map[x][y + 1] && map[x][y + 1] != '0' && map[x][y + 1] != '1' && map[x][y + 1] != '2')
		return (1);
	if (map[x][y - 1] && map[x][y - 1] != '0' && map[x][y - 1] != '1' && map[x][y - 1] != '2')
		return (1);
	return (0);
}

int	check_spaces(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '0' || map[x][y] == '2')
				if (check_next(map, x, y) == 1)
					return (1);
			y++;
		}
		x++;
	}
	return (0);
}

int check_door(char **map)
{
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == '2')
			{
				if(map[i][j - 1] && map[i][j + 1]
				&& map[i][j - 1] == '1' && map[i][j + 1] == '1')
				{

				}
				else if(map[i - 1][j] && map[i + 1][j]
				&& map[i - 1][j] == '1' && map[i + 1][j] == '1')
				{
					
				}
				else	
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	parsing(t_data *data)
{
	if (top_and_bottom(data->map->map) == 1)
		return (1);
	if (line_check(data->map->map) == 1)
		return (1);
	if (player_check(data->map->map) == 1)
		return (1);
	if (find_spawn(data, data->map->map) == 1)
		return (1);
	if (check_spaces(data->map->map) == 1)
		return (1);
	if (flood(data) == 1)
		return (1);
	if (check_door(data->map->map) == 1)
		return (1);
	return (0);
}
