/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:49:27 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 17:03:49 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_in_shadow(t_minirt *data, t_coord point, t_coord light_dir,
		double light_distance)
{
	t_ray			shadow_ray;
	t_hit_record	temp_rec;
	double			epsilon;

	epsilon = 0.001;
	shadow_ray.origin = add(point, scale(light_dir, epsilon));
	shadow_ray.direction = light_dir;
	return (intersect_scene(data, shadow_ray, &temp_rec)
		&& temp_rec.t < light_distance);
}

static void	calculate_light(t_minirt *data, t_ray *ray,
		t_hit_record *rec, t_rgb *result)
{
	t_coord	view_dir;
	t_coord	light_dir;
	t_coord	reflect_dir;
	double	diffuse_factor;
	double	spec_factor;

	view_dir = norm(scale(ray->direction, -1));
	light_dir = norm(subtract(data->light->position, rec->p));
	reflect_dir = calculate_reflect_dir(rec->normal, light_dir);
	*result = calculate_ambient(data->alight);
	if (!is_in_shadow(data, rec->p, light_dir,
			length(subtract(data->light->position, rec->p))))
	{
		diffuse_factor = fmax(dot(rec->normal, light_dir), 0.0);
		*result = add(*result, scale(calculate_diffuse(data->light,
						rec->normal, light_dir, rec->color), diffuse_factor));
		spec_factor = pow(fmax(dot(view_dir, reflect_dir), 0.0), 32);
		*result = add(*result, scale(calculate_specular(data->light,
						view_dir, reflect_dir, rec->color), spec_factor));
		*result = color_check(*result);
	}
}

void	render_light(t_minirt *data, t_ray ray,
				t_hit_record *rec, t_coord pixel)
{
	t_rgb	result;
	t_rgb	global_illum;

	calculate_light(data, &ray, rec, &result);
	global_illum = global_illumination(data, rec, 2, 1);
	result = add(result, scale(global_illum, data->alight->ratio));
	result = multiply(result, rec->color);
	result.x /= 255;
	result.y /= 255;
	result.z /= 255;
	put_pixel(data->win_data, pixel.x, pixel.y, result);
}

t_rgb	global_illumination(t_minirt *data, t_hit_record *rec,
		int samples, int depth)
{
	int				i;
	t_ray			scattered_ray;
	t_hit_record	new_rec;
	t_rgb			indirect_light;
	t_rgb			color;

	color = (t_rgb){0, 0, 0};
	i = -1;
	if (depth <= 0)
		return (color);
	while (++i < samples)
	{
		scattered_ray.origin = rec->p;
		scattered_ray.direction = random_in_hemisphere(rec->normal);
		scattered_ray.half_fov = 0;
		if (intersect_scene(data, scattered_ray, &new_rec))
		{
			indirect_light = global_illumination(data, &new_rec, 1, depth - 1);
			color = add(color, scale(indirect_light, 0.5));
		}
	}
	return (scale(color, 1.0 / samples));
}
