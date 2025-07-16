/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:25:23 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/07/16 13:43:05 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

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