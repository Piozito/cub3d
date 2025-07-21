/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:57:09 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/07/21 15:47:49 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

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

void	update_first_last(char *line, char *first, char *last, size_t len)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		if (j < ft_strlen(line) && line[j])
		{
			if ((!first[j] && line[j] != ' ' && line[j] != '\t')
				|| first[j] == ' ' || first[j] == '\t')
				first[j] = line[j];
			if (line[j] != ' ' && line[j] != '\t')
				last[j] = line[j];
		}
		j++;
	}
}

int	top_and_bottom(char **map)
{
	size_t	i;
	size_t	biggest_line;
	char	*first_line;
	char	*last_line;
	int		ret;

	biggest_line = get_biggest_line(map);
	first_line = ft_calloc(biggest_line + 1, sizeof(char));
	last_line = ft_calloc(biggest_line + 1, sizeof(char));
	i = 0;
	while (map[i])
		update_first_last(map[i++], first_line, last_line, biggest_line);
	first_line[biggest_line] = '\0';
	last_line[biggest_line] = '\0';
	ret = 0;
	if (line_checker(first_line) == 1)
		ret = 1;
	if (line_checker(last_line) == 1)
		ret = 1;
	return (ret);
}

int	find_spawn(t_data *data, char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
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

int	check_visited(t_data *data, char **visited)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = get_biggest_line(data->map.map);
	while (i < data->map.map_height)
	{
		j = 0;
		while (j < len)
		{
			if (visited[i][j] == '2')
			{
				i = 0;
				while (i < data->map.map_height)
					free(visited[i++]);
				free(visited);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
