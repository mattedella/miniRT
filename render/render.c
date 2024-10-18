/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:55:45 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 15:59:09 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_ray	get_ray(double x, double y, t_camera *camera)
{
	double	ratio;
	double	cam_scale;
	t_ray	ray;

	ratio = (double)(WIN_WIDTH / WIN_HEIGHT);
	cam_scale = tan(camera->fov / 2) / 2;
	ray.origin.x = camera->position.x;
	ray.origin.y = camera->position.y;
	ray.origin.z = camera->position.z;
	ray.direction.x = (2 * ((x + 0.5) / (double)WIN_WIDTH) - 1)
		* ratio * cam_scale;
	ray.direction.y = (1 - 2 * (y + 0.5) / (double)WIN_HEIGHT) * cam_scale;
	ray.direction.z = camera->vector_norm.z;
	ray.direction = norm(ray.direction);
	return (ray);
}

static void	reset_closest_dist(void)
{
	*sphere_dist() = DBL_MAX;
	*cylinder_dist() = DBL_MAX;
	*plane_dist() = DBL_MAX;
	*closest_dist() = DBL_MAX;
}

static void	init_rec(t_hit_record *rec)
{
	rec->color = (t_rgb){0, 0, 0};
	rec->hit = 0;
	rec->normal = (t_coord){0, 0, 0};
	rec->object = NULL;
	rec->object_type = 0;
	rec->p = (t_coord){0, 0, 0};
	rec->t = 0;
}

void	render(t_minirt *data, t_wdata *win_data, t_coord pixel)
{
	t_ray			ray;
	t_index			id;
	t_hit_record	rec;

	(void)win_data;
	init_rec(&rec);
	id.i = -1;
	id.t = 0;
	reset_closest_dist();
	while (++id.i < data->nbr_object)
	{
		ray = get_ray(pixel.x, pixel.y, data->camera);
		if (id.i < data->nbr_plane && data->plane[id.i].flag != 0)
			render_plane(ray, data->plane[id.i], &rec);
		if (id.i < data->nbr_sphere && data->sphere[id.i].flag != 0)
			render_sphere(ray, data->sphere[id.i], &rec);
		if (id.i < data->nbr_cylinder && data->cylinder[id.i].flag != 0)
			render_cylinder(ray, data->cylinder[id.i], &rec);
	}
	if (rec.hit)
		render_light(data, ray, &rec, pixel);
}

void	ray_trace(t_minirt *data, t_wdata *win_data)
{
	t_coord		pixel;

	pixel.y = 0;
	while (pixel.y < WIN_HEIGHT)
	{
		pixel.x = 0;
		while (pixel.x < WIN_WIDTH)
		{
			render(data, win_data, pixel);
			pixel.x++;
		}
		pixel.y++;
	}
	mlx_put_image_to_window(win_data->mlx,
		win_data->win, win_data->img, 0, 0);
}
