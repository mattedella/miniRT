/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:55:45 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/06 10:11:16 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

static t_ray	get_ray(double x, double y, t_camera *camera)
{
	double	ratio;
	double	scale;
	t_ray	ray;
	t_coord	right;
	t_coord	up;

	ratio = (double)(WIN_WIDTH / WIN_HEIGHT);
	scale = tan(camera->fov) / 2;
	ray.origin.x = camera->position.x;
	ray.origin.y = camera->position.y;
	ray.origin.z = camera->position.z;	
	ray.direction.x = (2 * ((x + 0.5) / (double)WIN_WIDTH) -1) * ratio * scale;
    ray.direction.y = (1 - 2 * (y + 0.5) / (double)WIN_HEIGHT) * scale;
	ray.direction.z = camera->vector_norm.z - camera->position.z;
	right = vector_norm(vector_cross((t_coord){0, 1, 0},
		vector_norm(camera->vector_norm)));
	up = vector_cross(vector_norm(camera->vector_norm), right);
	ray.direction = vector_add(vector_add(vector_scale(right, ray.direction.x),
		vector_scale(up, ray.direction.y)),
		vector_scale(vector_norm(camera->vector_norm), camera->vector_norm.z));
	ray.direction = vector_norm(ray.direction);
	return (ray);
}

void	ray_trace(t_minirt *data, t_wdata *win_data)
{
	int		i;
	t_coord	pixel;

	i = 0;
	while (i < data->nbr_object)
	{
		pixel.y = 0;
		while(pixel.y < WIN_HEIGHT)
		{
			pixel.x = 0;
			while(pixel.x < WIN_WIDTH)
			{
				render(data, win_data, pixel, i);
				pixel.x++;
			}
			pixel.y++;
		}
		i++;
		mlx_put_image_to_window(win_data->mlx,
		win_data->win, win_data->img, 0, 0);
	}
	// render_light(ray, data->alight, data->light);
}

void	render(t_minirt *data, t_wdata *win_data, t_coord pixel, int i)
{
	t_ray	ray;

	ray = get_ray(pixel.x, pixel.y, data->camera);
	if (i < data->nbr_plane && data->plane[i].flag != 0)
		render_plane(ray, data->plane[i], win_data, pixel);
	if (i < data->nbr_sphere && data->sphere[i].flag != 0)
		render_sphere(ray, data->sphere[i], win_data, pixel);
	if (i < data->nbr_cylinder && data->cylinder[i].flag != 0)
		render_cylinder(ray, data->cylinder[i], win_data, pixel);
}
