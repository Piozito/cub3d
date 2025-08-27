/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:08:46 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/08/27 13:06:21 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"

# define NORTH "../textures/north"
# define SOUTH "../textures/south"
# define EAST "../textures/east"
# define WEST "../textures/west"
# define NUM_TEXTURES 4
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define TEXTURE_SIZE 64

#define WLK_SPEED 0.075
#define ROT_SPEED 0.00025
#define JUMP_HEIGHT 250

typedef struct s_im
{
	void		*mlx_img;
	int			width;
	int			height;
	char		*addr;
	int			bpp;
	void		*ground;
	int			line_length;
	int			endian;

}				t_im;

typedef struct s_map
{
	int			fd;
	t_im		*north;
	t_im		*south;
	t_im		*east;
	t_im		*west;
	t_im		*door;
	int			celling;
	int			floor;
	int			spawn[2];
	int			map_height;
	int			map_lenght;
	char		**map;
}				t_map;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		angle;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			tex_y;
	double			wall_x;
	int			key_states[6];
}				t_player;

//key_states[0] W
//key_states[1] S
//key_states[2] D
//key_states[3] A
//key_states[4] Shift
//key_states[5] Space


typedef struct s_data
{
	void		*mlx_ptr;
	void		*window_ptr;
	void		*img_ptr;
	int			*texture_buffer[NUM_TEXTURES];
	t_im		*image;
	t_player	*player;
	t_map		*map;
}				t_data;

void		ft_debug(t_data *data);
int			ft_clear(t_data *data);
void		ext_checker(char *path);
void		map_setter(t_data *data, ssize_t j, char **map);
void		floodfill(t_data *data, char **visited, int x, int y);
int			rgb(char *str);
int			vectors(void *param);
void		mlx_starter(t_data *data);
int			check_flag(int *flags);
int			parsing(t_data *data);
int			line_check(char **map);
int			line_checker(char *line);
int			player_check(char **map);
int			check_attribute(char *str);
int			top_and_bottom(char **map);
int			check_last_char(char *line);
int			find_spawn(t_data *data, char **map);
int			check_visited(t_data *data, char **visited);
int			loop_help(t_data *data, char *str, int *flags);
char		*ft_strndup(char *s, int n);
size_t		get_biggest_line(char **map);
ssize_t		get_file_lines(char **argv);
ssize_t		find_char(const char *str, char c, ssize_t len);

void draw_square(void *mlx_ptr, int x, int y, int size, int color);
void draw_circle(void *mlx_ptr, int coords, int radius, int color);
void draw_minimap(t_data *data);

int	handle_keypress(int keysym, t_data *data);
int	handle_btnrelease(int keysym, t_data *data);

int		camera_handler(int x, int y, t_player *player);
int		set_jump(t_data *data);
void	movement_handler(t_data *data);

void my_mlx_pixel_put(t_im *img, int x, int y, int color);

#endif