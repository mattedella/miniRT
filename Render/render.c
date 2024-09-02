/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:55:45 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/02 17:45:24 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

static t_ray	get_ray(double x, double y, t_camera *camera)
{
	double	ratio;
	double	scale;
	t_ray	ray;

	ratio = (double)(WIN_WIDTH / WIN_HEIGHT);
	scale = tan((camera->fov * 0.5) * PI / 180.0);
	ray.origin.x = camera->position.x;
	ray.origin.y = camera->position.y;
	ray.origin.z = camera->position.z;	
	ray.direction.x = (2 * (x + 0.5) / (double)WIN_WIDTH - 1) * ratio * scale;
    ray.direction.y = (1 - 2 * (y + 0.5) / (double)WIN_HEIGHT) * scale;
	ray.direction.z = camera->vector_norm.z;
	ray.direction = vector_normalize(ray.direction);
	return (ray);
}

void	ray_trace(t_minirt *data)
{
	t_ray	ray;
	int		i;
	t_coord	pixel;

	i = 0;
	pixel.x = 0;
	pixel.y = 0;
	while (i < data->nbr_object)
	{
		while(pixel.y < WIN_HEIGHT)
		{
			while(pixel.x < WIN_WIDTH)
			{
				ray = get_ray(pixel.x, pixel.y, data->camera);
				if (data->sphere[i].flag != 0)
					render_sphere(ray, data->sphere[i], data->win_data);
				if (data->cylinder[i].flag != 0)
					render_cylinder(ray, data->cylinder[i]);
				if (data->plane[i].flag != 0)
					render_plane(ray, data->plane[i]);
				pixel.x++;
			}
			pixel.y++;
		}
		i++;
	}
	render_light(ray, data->alight, data->light);
}

void	render(t_minirt *data)
{
	ray_trace(data);
	// mlx_put_image_to_window(data->win_data->mlx, data->win_data->win, data->win_data->img, 0, 0);
}
