/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:07:54 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/04 15:20:01 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "Minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# define PI 3.141592653
# define WIN_WIDTH 900
# define WIN_HEIGHT 900
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define L_KEY 108
# define C_KEY 99
# define P_KEY 112
# define Y_KEY 121
# define UP_ARROW 65362
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364
# define ESC_KEY 65307

typedef struct	s_index
{
	int			i;
	int			j;
	int			k;
	int			t;
}				t_index;


typedef struct	s_coord
{
	double		x;
	double		y;
	double		z;
}				t_coord;

typedef t_coord	t_rgb;

typedef struct s_ray
{
	t_coord		origin;
	t_coord		direction;
	double		half_fov;
}				t_ray;

typedef struct s_hit_record
{
	t_coord		p;
	t_coord		normal;
	double		t;
	int			front_face;
}				t_hit_record;

typedef struct	s_alight
{
	double		ratio;
	t_rgb		color;
}				t_alight;

typedef struct	s_light
{
	t_coord		position;
	double		brightness;
	t_rgb		color;
}				t_light;

typedef struct	s_camera
{
	t_coord		position;
	t_coord		vector_norm;
	double		fov;
}				t_camera;

typedef struct	s_sphere
{
	t_coord		position;
	double		diameter;
	t_rgb		color;
	int			flag;	
}				t_sphere;

typedef struct	s_plane
{
	t_coord		position;
	t_coord		vector_norm;
	t_rgb		color;	
	int			flag;
}				t_plane;

typedef struct	s_cylinder
{
	int			flag;
	t_coord		position;
	t_coord		vector_norm;
	double		diameter;
	double		height;
	t_rgb		color;
}				t_cylinder;

typedef struct	s_window_data
{
	void		*mlx;
	void		*win;
	void		*img;
	int			endian;
	int			bits_per_pixel;
	int			line_length;
	char		*addr;
}				t_wdata;

typedef struct	s_minirt
{
	t_alight	*alight;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_wdata		*win_data;
	int			nbr_object;
	int			nbr_plane;
	int			nbr_sphere;
	int			nbr_cylinder;
}				t_minirt;

//get_next_line
size_t	f_strlen(char *str);
char	*get_next_line(int fd);

// window utils
int		press_x(t_wdata *data);
int	key_hook(int keycode, t_wdata *data);

// init param object
void	get_light(char **mat, t_minirt *data);
void	get_camera(char **mat, t_minirt *data);
void	get_ambient_light(char **mat, t_minirt *data);

// init object
void	get_plane(char **mat, t_minirt *data, int i);
void	get_sphere(char **mat, t_minirt *data, int i);
void	get_cylinder(char **mat, t_minirt *data, int i);
void	init_plane(t_minirt *data, int n_cmd);
void	init_sphere(t_minirt *data, int n_cmd);
void	init_cylinder(t_minirt *data, int n_cmd);
void	check_object(t_minirt *data, char **file);

// check_param
void	check_fov(int fov);
void	check_color_range(t_rgb color);
void	check_ratio_light(double light);
void	check_vector_range(t_coord pos);

// utils
int		ft_exit(int id);
double	ft_atod(char *argv);
int		mat_len(char **mat);
void	free_mat(char **mat);
size_t	mat_get_len(char *argv);

// init data
t_list	**garbage_collector(void);
void	*my_calloc(size_t size);
void	garbage_collector_free();
void	init_window(t_wdata *win_data);
void	init_data(t_minirt *data, t_wdata *win_data);

// rendering
void	render(t_minirt *data, t_wdata *win_data);
void	ray_trace(t_minirt *data, t_wdata *win_data);
void	render_plane(t_ray ray, t_plane plane,
		t_wdata *win_data, t_coord pixel);
void	render_sphere(t_ray ray, t_sphere sphere,
		t_wdata *win_data, t_coord pixel);
void	render_cylinder(t_ray ray, t_cylinder cylinder,
		t_wdata *win_data, t_coord pixel);
void	render_light(t_ray ray, t_alight *alight, t_light *light);
void	put_pixel(t_wdata *data, int x, int y, t_rgb color);

// vector
unsigned int	create_rgb(int r, int g, int b);
t_coord			vector_norm(t_coord v);
t_coord			vector_scale(t_coord v, double t);
t_coord			vector_add(t_coord v1, t_coord v2);
t_coord 		vector_cross(t_coord v1, t_coord v2);
t_coord			vector_subtract(t_coord v1, t_coord v2);
double			vector_dot(t_coord v1, t_coord v2);
double			vector_dot(t_coord v1, t_coord v2);

#endif