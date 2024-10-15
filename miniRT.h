/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:07:54 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/15 15:41:51 by mdella-r         ###   ########.fr       */
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

# define DBL_MAX 1.7976931348623157E+308
# define PI 3.141593
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define L_KEY 108
# define C_KEY 99
# define P_KEY 112
# define Y_KEY 121
# define R_KEY 114
# define O_KEY 111
# define X_KEY 120
# define Z_KEY 122
# define PLUS_KEY 65451
# define MINUS_KEY 65453
# define UP_ARROW 65362
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364
# define ESC_KEY 65307

typedef struct s_index
{
	int			i;
	int			j;
	int			k;
	int			t;
}				t_index;

typedef struct s_double
{
	double		a;
	double		b;
	double		c;
	double		disc;
}				t_double;

typedef struct s_coord
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

typedef struct s_alight
{
	double		ratio;
	t_rgb		color;
}				t_alight;

typedef struct s_light
{
	t_coord		position;
	double		brightness;
	t_rgb		color;
}				t_light;

typedef struct s_camera
{
	t_coord		position;
	t_coord		vector_norm;
	double		fov;
}				t_camera;

typedef struct s_sphere
{
	t_coord		position;
	double		diameter;
	t_rgb		color;
	int			flag;	
}				t_sphere;

typedef struct s_plane
{
	t_coord		position;
	t_coord		vector_norm;
	t_rgb		color;	
	int			flag;
}				t_plane;

typedef struct s_cylinder
{
	int			flag;
	t_coord		position;
	t_coord		vector_norm;
	double		diameter;
	double		height;
	t_rgb		color;
}				t_cylinder;

typedef struct s_window_data
{
	void		*mlx;
	void		*win;
	void		*img;
	int			endian;
	int			bits_per_pixel;
	int			line_length;
	char		*addr;
}				t_wdata;

typedef struct s_minirt
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
size_t			f_strlen(char *str);
char			*get_next_line(int fd);

// window utils
int				press_x(t_wdata *data);
int				key_hook(int keycode, t_minirt *data);
int				quit(char id, t_wdata *data, char **mat, char **file);

// init param object
void			get_light(char **mat, char **file, t_minirt *data);
void			get_camera(char **mat, char **file, t_minirt *data);
void			get_ambient_light(char **mat, char **file, t_minirt *data);

// init object
int				control_object(char **tmp);
void			get_nbr_object(t_minirt *data, int i, int j, int k);
void			check_object(t_minirt *data, char **file);
void			check_option(t_minirt *data, char **file);
void			get_plane(char **mat, char **file, t_minirt *data, int i);
void			get_sphere(char **mat, char **file, t_minirt *data, int i);
void			get_cylinder(char **mat, char **file, t_minirt *data, int i);
void			init_plane(t_minirt *data, int n_cmd);
void			init_sphere(t_minirt *data, int n_cmd);
void			init_cylinder(t_minirt *data, int n_cmd);
void			check_object(t_minirt *data, char **file);

// check_param
void			check_fov(double fov, t_wdata *data, char **mat, char **file);
void			check_color_range(t_rgb color, t_wdata *data,
					char **mat, char **file);
void			check_ratio_light(double light, t_wdata *data,
					char **mat, char **file);
void			check_vector_range(t_coord pos, t_wdata *data,
					char **mat, char **file);

// utils
int				ft_exit(int id);
double			ft_atod(char *argv);
int				mat_len(char **mat);
void			free_mat(char **mat);
size_t			mat_get_len(char *argv);

// render order
double			*closest_dist(void);
double			*plane_dist(void);
double			*sphere_dist(void);
double			*cylinder_dist(void);

// init data
void			*my_calloc(size_t size, int n_cmd);
void			garbage_collector_free(void);
void			init_window(t_wdata *win_data);
void			init_data(t_minirt *data, t_wdata *win_data);

// rendering
void			render(t_minirt *data, t_wdata *win_data, t_coord pixel);
void			ray_trace(t_minirt *data, t_wdata *win_data);
void			render_plane(t_ray ray, t_plane plane,
					t_wdata *win_data, t_coord pixel);
void			render_sphere(t_ray ray, t_sphere sphere,
					t_wdata *win_data, t_coord pixel);
void			render_cylinder(t_ray ray, t_cylinder cylinder,
					t_wdata *win_data, t_coord pixel);
void			render_light(t_ray ray, t_alight *alight, t_light *light);
void			put_pixel(t_wdata *data, int x, int y, t_rgb color);

// vector
unsigned int	create_rgb(int r, int g, int b);
t_coord			norm(t_coord v);
t_coord			scale(t_coord v, double t);
t_coord			add(t_coord v1, t_coord v2);
t_coord			cross(t_coord v1, t_coord v2);
t_coord			subtract(t_coord v1, t_coord v2);
double			dot(t_coord v1, t_coord v2);
double			length(t_coord v);

#endif