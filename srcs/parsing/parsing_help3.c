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

t_doors	*prep_door(int x, int y)
{
	static t_doors	*old_ptr;
	t_doors			*door;
	static int		i;

	i = 0;
	door = malloc(sizeof(t_doors));
	door->id = i;
	door->coords[0] = x;
	door->coords[1] = y;
	door->open = 100;
	door->next = old_ptr;
	old_ptr = door;
	i++;
	return (door);
}

int	parse_door(t_data *data, char **map, int x, int y)
{
	data->map->door_num++;
	if (map[x][y - 1] && map[x][y + 1]
	&& map[x][y - 1] == '1' && map[x][y + 1] == '1')
		return (0);
	else if (map[x - 1][y] && map[x + 1][y]
	&& map[x - 1][y] == '1' && map[x + 1][y] == '1')
		return (0);
	else
		return (1);
}

int	check_door(t_data *data, char **map, int flag)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	d = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				if (flag == 0 && parse_door(data, map, i, j) == 1)
					return (1);
				if (flag == 1)
					data->map->doors[d++] = prep_door(i, j);
			}
			j++;
		}
		i++;
	}
	return (0);
}
