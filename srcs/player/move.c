/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:12:39 by fragarc2          #+#    #+#             */
/*   Updated: 2025/07/16 12:16:23 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	else if (ft_strchr("wasd", keysym))
		move_player(data, keysym);
	return (0);
}

int	check_next_tile(t_data *data, char direction, char tile)
{
	if ((direction == 'd' && data->map.map[data->p_i][data->p_j + 1] == tile)
		|| (direction == 'a' && data->map.map[data->p_i][data->p_j - 1] == tile)
		|| (direction == 's' && data->map.map[data->p_i + 1][data->p_j] == tile)
		|| (direction == 'w' && data->map.map[data->p_i
			- 1][data->p_j] == tile))
		return (0);
	else
		return (1);
}

void	move_player(t_data *data, char direction)
{
	if (check_next_tile(data, direction, '1') == 0 || (data->map.can_exit == 0
			&& check_next_tile(data, direction, 'E') == 0))
		return ;
	if (data->map.collected == data->map.count_c)
		data->map.can_exit = 1;
	data->map.map[data->p_i][data->p_j] = '0';
	if (direction == 'd')
		data->p_j++;
	else if (direction == 'a')
		data->p_j--;
	else if (direction == 's')
		data->p_i++;
	else if (direction == 'w')
		data->p_i--;
	move_msg(data);
	data->map.map[data->p_i][data->p_j] = 'P';
}
