/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:52:40 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/07/17 15:12:45 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	ext_checker(char *path)
{
	if (!ft_strnstr(&path[ft_strlen(path) - 4], ".cub\0", 4))
	{
		printf("Error\nNo \".cub\" file detected.\n");
		exit(1);
	}
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
