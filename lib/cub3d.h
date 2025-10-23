/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:08:46 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/10/23 13:05:57 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <limits.h>
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

# define W_W 1440
# define W_H 810
# define TEXTURE_SIZE 256

# define WLK_SPEED 0.075
# define ROT_SPEED 0.00025

# define MP_ZOOM 15.0
# define MP_RDS 75
# define MP_CTR 120

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
	char		*file;
}				t_im;

typedef struct s_doors
{
	int			coords[2];
	int			open;
}				t_doors;

typedef struct s_map
{
	int			fd;
	t_im		*north;
	t_im		*south;
	t_im		*east;
	t_im		*west;
	t_im		*door_top;
	t_im		*door_bot;
	int			door_num;
	int			celling;
	int			floor;
	int			spawn[2];
	int			map_height;
	int			map_lenght;
	int			key;
	int			flag;
	char		**map;
	t_doors		**doors;
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
	int			side;
	int			key_states[7];
}				t_player;

typedef struct s_tex
{
	int			color;
	int			tex_y;
	double		wall_height;
	double		step;
	double		tex_pos;
	int			open_px;
	int			drew;
	int			y;
	int			x;
}				t_tex;

//key_states[0] W
//key_states[1] S
//key_states[2] D
//key_states[3] A
//key_states[4] Shift
//key_states[5] Space UNUSED
//key_states[6] E

typedef struct s_data
{
	void		*mlx_ptr;
	void		*window_ptr;
	void		*img_ptr;
	t_im		*image;
	t_player	*player;
	t_map		*map;
	t_tex		*tex;
}				t_data;

int		rgb(char *str);
int		vectors(void *param);
int		parsing(t_data *data);
int		check_flag(int *flags);
int		line_check(char **map);
int		ft_clear(t_data *data);
int		set_side(t_data *data);
int		limit(int i, int limit);
int		player_check(char **map);
int		check_spaces(char **map);
int		line_checker(char *line);
int		top_and_bottom(char **map);
int		check_attribute(char *str);
int		check_last_char(char *line);
int		texer(t_data *data, int tex_x);
int		find_spawn(t_data *data, char **map);
int		handle_keypress(int keysym, t_data *data);
int		handle_btnrelease(int keysym, t_data *data);
int		check_next(char **map, int x, int y);
int		check_visited(t_data *data, char **visited);
int		check_door(t_data *data, char **map, int flag);
int		camera_handler(int x, int y, t_player *player);
int		loop_help(t_data *data, char *str, int *flags);
int		get_texel_color(t_im *texture, int tex_x, int tex_y);
int		texturer(t_data *data, int i, int tex_x, int *column_drawn);

void	free_map(t_map *map);
void	helper(t_data *data);
//void	ft_debug(t_data *data);
void	ext_checker(char *path);
void	draw_cone(t_data *data);
void	free_doors(t_data *data);
void	vector_help(t_data *data);
void	draw_limits(t_data *data);
void	mlx_starter(t_data *data);
void	draw_minimap(t_data *data);
void	tex_initialiser(t_data *data);
void	movement_handler(t_data *data);
void	draw_line(void *mlx_ptr, int *ends);
void	init_file(t_data *data, char *file);
void	do_y(t_data *data, int *column_drawn);
void	init_data_structs(t_data *data, char *file);
void	map_setter(t_data *data, ssize_t j, char **map);
void	circle_help(void *mlx_ptr, int *crds, int color);
void	draw_circle(void *mlx_ptr, int radius, int color);
void	dooring(t_data *data, int tex_x, int *column_drawn);
void	my_mlx_pixel_put(t_im *img, int x, int y, int color);
void	draw_help(int *delta, int *step, int *err, int *crds);
void	floodfill(t_data *data, char **visited, int x, int y);
void	draw_texture(t_data *data, int *column_drawn, int tex_x);
void	draw_circle_outline(void *mlx_ptr, int radius, int color);
void	draw_minimap_pixel(t_data *data, int count[2], int map[2], int *color);

char	*ft_strndup(char *s, int n);

size_t	get_biggest_line(char **map);

ssize_t	get_file_lines(char **argv);
ssize_t	find_char(const char *str, char c, ssize_t len);

double	get_wall_x(t_data *data);

t_im	*prep_img(void);
t_im	*get_wall_texture(t_data *data);
t_doors	*open_closest_door(t_data *data);
t_doors	*find_door(t_doors **array, int map_y, int map_x);

#endif
