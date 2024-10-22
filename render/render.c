/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:55:45 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/21 16:26:51 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_coord	get_camera_right(t_coord cam_dir)
{
	t_coord	up;
	t_coord	right;

	up = (t_coord){0, 1, 0};
	if (fabs(cam_dir.y) > 0.9999)
		right = (t_coord){1, 0, 0};
	else
		right = norm(cross(up, cam_dir));
	return (right);
}

static t_ray	get_ray(double x, double y, t_camera *camera)
{
	t_ray		ray;
	t_rayutils	utils;

	utils.ratio = (double)WIN_WIDTH / WIN_HEIGHT;
	utils.cam_scale = 2.0 * tan(camera->fov / 2);
	utils.width = utils.ratio * utils.cam_scale;
	ray.origin = camera->position;
	utils.w = norm(scale(camera->vector_norm, -1));
	utils.u = get_camera_right(utils.w);
	utils.v = cross(utils.w, utils.u);
	utils.v = scale(utils.v, -1);
	utils.hor = scale(utils.u, utils.width);
	utils.ver = scale(utils.v, utils.cam_scale);
	utils.low_cor = subtract(ray.origin,
			add(scale(utils.hor, 0.5), add(scale(utils.ver, 0.5), utils.w)));
	utils.s = x / (WIN_WIDTH - 1);
	utils.t = y / (WIN_HEIGHT - 1);
	ray.direction = subtract(add(utils.low_cor, add(scale(utils.hor, utils.s),
					scale(utils.ver, utils.t))), ray.origin);
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
