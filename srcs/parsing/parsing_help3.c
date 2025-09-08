/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:09:50 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/09/08 11:09:50 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	floodfill(t_data *data, char **visited, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map->map_height
		|| y >= (int)get_biggest_line(data->map->map)
		|| data->map->map[x][y] == '1' || visited[x][y])
		return ;
	if (data->map->map[x][y] == ' ' || data->map->map[x][y] == '\t')
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

int	parse_door(char **map, int i, int j)
{
	if (map[i][j - 1] && map[i][j + 1]
	&& map[i][j - 1] == '1' && map[i][j + 1] == '1')
		return (0);
	else if (map[i - 1][j] && map[i + 1][j]
	&& map[i - 1][j] == '1' && map[i + 1][j] == '1')
		return (0);
	else
		return (1);
}

int	check_door(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				if (parse_door(map, i, j) == 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
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
