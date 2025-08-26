/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:54:13 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/08/19 14:04:01 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	map_setter(t_data *data, ssize_t j, char **map)
{
	ssize_t	i;

	i = 0;
	data->map->map = malloc(sizeof(char *) * (j + 1));
	while (map[i])
	{
		data->map->map[i] = ft_strdup(map[i]);
		free(map[i]);
		i++;
	}
	free(map);
	data->map->map[i] = NULL;
}

int	texture_help(t_data *data, char *str)
{
	if (ft_strncmp(str, "NO ", 3) == 0)
		data->map->north->addr = ft_strndup(str, 3);
	else if (ft_strncmp(str, "SO ", 3) == 0)
		data->map->south->addr = ft_strndup(str, 3);
	else if (ft_strncmp(str, "WE ", 3) == 0)
		data->map->west->addr = ft_strndup(str, 3);
	else if (ft_strncmp(str, "EA ", 3) == 0)
		data->map->east->addr = ft_strndup(str, 3);
	else if (ft_strncmp(str, "D ", 2) == 0)
		data->map->door->addr = ft_strndup(str, 2);
	else if (ft_strncmp(str, "F ", 2) == 0)
		data->map->floor = rgb(str + 2);
	else if (ft_strncmp(str, "C ", 2) == 0)
		data->map->celling = rgb(str + 2);
	else
		return (1);
	if(data->map->floor == -1 || data->map->celling == -1)
		return (-1);
	free(str);
	return (0);
}

int	attr_check(t_data *data, char *str, int *flags)
{
	int	attr;

	attr = check_attribute(str);
	if (attr >= 0)
	{
		if (flags[attr] == 1)
			return (1);
		flags[attr] = 1;
		if (texture_help(data, str) == -1)
			return (1);
		return (2);
	}
	return (0);
}

int	check_flag(int *flags)
{
	ssize_t	i;

	i = 0;
	while (i < 7)
	{
		if (flags[i] != 1)
			return (1);
		i++;
	}
	return (0);
}

int	loop_help(t_data *data, char *str, int *flags)
{
	int	res;

	res = 0;
	if (!str)
		return (1);
	if (str[0] == '\n')
	{
		free(str);
		return (2);
	}
	res = attr_check(data, str, flags);
	if (res == 1)
	{
		free(str);
		return (1);
	}
	else if (res == 2)
		return (2);
	else
		return (0);
}
