/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:21:15 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/16 14:21:18 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	calculate_cylinder_coefficients(t_ray ray, t_cylinder cylinder,
		t_coord axis, t_coord oc, t_double *coeffs)
{
	coeffs->a = dot(ray.direction, ray.direction)
		- pow(dot(ray.direction, axis), 2);
	coeffs->b = 2 * (dot(ray.direction, oc)
			- dot(ray.direction, axis) * dot(oc, axis));
	coeffs->c = dot(oc, oc) - pow(dot(oc, axis), 2)
		- pow(cylinder.diameter / 2, 2);
}

static int	solve_quadratic(t_double *coeffs, t_double *t)
{
	double	discriminant;
	double	sqrt_discriminant;

	discriminant = coeffs->b * coeffs->b - 4 * coeffs->a * coeffs->c;
	if (discriminant < 0)
		return (0);
	sqrt_discriminant = sqrt(discriminant);
	t->a = (-coeffs->b - sqrt_discriminant) / (2 * coeffs->a);
	t->b = (-coeffs->b + sqrt_discriminant) / (2 * coeffs->a);
	if (t->a > t->b)
	{
		double temp = t->a;
		t->a = t->b;
		t->b = temp;
	}
	return (1);
}

static double	intersect_cylinder_body(t_ray ray, t_cylinder cylinder,
		t_coord axis, t_double *t)
{
	t_coord	hit_point;
	t_coord	center_to_hit;
	double	half_height;

	half_height = cylinder.height / 2;
	if (t->a >= 0)
	{
		hit_point = add(ray.origin, scale(ray.direction, t->a));
		center_to_hit = subtract(hit_point, cylinder.position);
		if (fabs(dot(center_to_hit, axis)) <= half_height)
			return (t->a);
	}
	else if (t->b >= 0)
	{
		hit_point = add(ray.origin, scale(ray.direction, t->b));
		center_to_hit = subtract(hit_point, cylinder.position);
		if (fabs(dot(center_to_hit, axis)) <= half_height)
			return (t->b);
	}
	return (-1);
}

static double	intersect_cylinder_cap(t_ray ray, t_cylinder cylinder,
		t_coord axis, double half_height, t_coord *cap_normal)
{
	t_coord	cap_center;
	double	denom;
	double	t;
	t_coord	hit_point;
	int		i;

	i = 0;
	while (i < 2)
	{
		cap_center = add(cylinder.position,
			scale(axis, (i == 0 ? -1 : 1) * half_height));
		denom = dot(ray.direction, axis);
		if (fabs(denom) > 1e-6)
		{
			t = dot(subtract(cap_center, ray.origin), axis) / denom;
			if (t >= 0)
			{
				hit_point = add(ray.origin, scale(ray.direction, t));
				if (length(subtract(hit_point, cap_center))
					<= cylinder.diameter / 2)
				{
					*cap_normal = i == 0 ? scale(axis, -1) : axis;
					return (t);
				}
			}
		}
		i++;
	}
	return (-1);
}

static void	set_hit_record(t_hit_record *rec, t_ray ray, double t,
		t_coord normal, t_rgb color)
{
	*closest_dist() = t;
	*cylinder_dist() = t;
	rec->t = t;
	rec->p = add(ray.origin, scale(ray.direction, t));
	rec->normal = normal;
	rec->color = color;
	rec->hit = 1;
}

static t_coord	calculate_body_normal(t_ray ray, t_cylinder cylinder,
		t_coord axis, double t)
{
	t_coord	hit_point;
	t_coord	center_to_hit;
	t_coord	radial_vector;

	hit_point = add(ray.origin, scale(ray.direction, t));
	center_to_hit = subtract(hit_point, cylinder.position);
	radial_vector = subtract(center_to_hit, scale(axis, dot(center_to_hit, axis)));
	return (norm(radial_vector));
}

int	intersect_cylinder(t_ray ray, t_cylinder cylinder, t_hit_record *rec)
{
	t_coord		axis;
	t_coord		oc;
	t_double	coeff;
	t_double	t;
	t_coord		cap_normal;
	double		half_height;

	axis = norm(cylinder.vector_norm);
	oc = subtract(ray.origin, cylinder.position);
	calculate_cylinder_coefficients(ray, cylinder, axis, oc, &coeff);
	if (!solve_quadratic(&coeff, &t))
		return (0);
	t.c = intersect_cylinder_body(ray, cylinder, axis, &t);
	half_height = cylinder.height / 2;
	t.disc = intersect_cylinder_cap(ray, cylinder, axis, half_height, &cap_normal);
	if (t.c < 0 && t.disc < 0 && t.c > *closest_dist() && t.disc > *closest_dist()
		&& t.c > *cylinder_dist() && t.disc > *cylinder_dist())
		return (0);
	if ((t.c < t.disc || t.disc < 0) && t.c >= 0)
		set_hit_record(rec, ray, t.c,
			calculate_body_normal(ray, cylinder, axis, t.c), cylinder.color);
	else
		set_hit_record(rec, ray, t.disc, cap_normal, cylinder.color);
	return (1);
}

int intersect_plane(t_ray ray, t_plane plane, t_hit_record *rec)
{
	double numerator;
	double denominator;
	double t;

	numerator = dot(subtract(plane.position, ray.origin), plane.vector_norm);
	denominator = dot(ray.direction, plane.vector_norm);
	
	if (fabs(denominator) < 1e-6)
		return (0);
	t = numerator / denominator;
	if (t < 1e-6 || t >= rec->t)
	{
		return (0);
	}

	// Update hit record
	rec->t = t;
	rec->p = add(ray.origin, scale(ray.direction, t));
	rec->normal = plane.vector_norm;
	
	if (dot(ray.direction, rec->normal) > 0)
		rec->normal = scale(rec->normal, -1);

	rec->color = plane.color;
	rec->object_type = PLANE;
	rec->object = (void*)&plane;

	return (1);
}

t_rgb global_illumination(t_minirt *data, t_hit_record *rec, int samples, int depth);

t_coord random_in_unit_disk()
{
	t_coord p;

	do {
		p = (t_coord){
			2.0 * ((double)rand() / RAND_MAX) - 1.0,
			2.0 * ((double)rand() / RAND_MAX) - 1.0,
			0
		};
	} while (dot(p, p) >= 1.0);
	return (p);
}

int intersect_sphere(t_ray ray, t_sphere sphere, t_hit_record *rec)
{
	t_coord oc = subtract(ray.origin, sphere.position);
	double a = dot(ray.direction, ray.direction);
	double b = 2.0 * dot(oc, ray.direction);
	double c = dot(oc, oc) - (sphere.diameter / 2) * (sphere.diameter / 2);
	double discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (0);
	double sqrt_discriminant = sqrt(discriminant);
	double t1 = (-b - sqrt_discriminant) / (2 * a);
	double t2 = (-b + sqrt_discriminant) / (2 * a);

	double t = (t1 < t2) ? t1 : t2;

	if (t < 0)
		t = (t1 < t2) ? t2 : t1;

	if (t < 0)
		return (0);

	rec->t = t;
	rec->p = add(ray.origin, scale(ray.direction, t));
	rec->normal = norm(subtract(rec->p, sphere.position));
	rec->color = sphere.color;

	if (dot(ray.direction, rec->normal) > 0)
		rec->normal = scale(rec->normal, -1);

	return (1);
}

t_coord random_in_hemisphere(t_coord normal)
{
	t_coord	in_unit_sphere;

	do {
		in_unit_sphere = (t_coord){
			2.0 * ((double)rand() / RAND_MAX) - 1.0,
			2.0 * ((double)rand() / RAND_MAX) - 1.0,
			2.0 * ((double)rand() / RAND_MAX) - 1.0
		};
	} while (dot(in_unit_sphere, in_unit_sphere) >= 1.0);

	if (dot(in_unit_sphere, normal) > 0.0)
		return (in_unit_sphere);
	else
		return (scale(in_unit_sphere, -1));
}

int intersect_scene(t_minirt *data, t_ray ray, t_hit_record *rec)
{
	int hit_anything = 0;
	double closest_so_far = INFINITY;
	t_hit_record temp_rec;
	int i;

	i = -1;
	while(++i < data->nbr_sphere)
	{
		if (intersect_sphere(ray, data->sphere[i], &temp_rec) && temp_rec.t < closest_so_far)
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
	}
	i = -1;
   	while(++i < data->nbr_plane)
	{
		if (intersect_plane(ray, data->plane[i], &temp_rec) && temp_rec.t < closest_so_far)
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
	}
	i = -1;
	while(++i < data->nbr_cylinder)
	{
		if (intersect_cylinder(ray, data->cylinder[i], &temp_rec) && temp_rec.t < closest_so_far)
		{
			hit_anything = 1;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
	}

	return (hit_anything);
}

int is_in_shadow(t_minirt *data, t_coord point, t_coord light_dir, double light_distance)
{
	t_ray shadow_ray;
	t_hit_record temp_rec;
	double epsilon = 0.001;

	shadow_ray.origin = add(point, scale(light_dir, epsilon));
	shadow_ray.direction = light_dir;

	return (intersect_scene(data, shadow_ray, &temp_rec) && temp_rec.t < light_distance);
}

t_rgb soft_shadow(t_minirt *data, t_coord point, t_coord normal, t_light *light, int samples)
{
	t_rgb color = {0, 0, 0};
	t_coord light_pos, light_dir;

	for (int i = 0; i < samples; i++)
	{
		light_pos = add(light->position, random_in_unit_disk());
		light_dir = subtract(light_pos, point);
		double light_distance = length(light_dir);
		light_dir = norm(light_dir);

		if (!is_in_shadow(data, point, light_dir, light_distance))
		{
			color = add(color, calculate_diffuse(light, normal, light_dir, light->color));
		}
	}

	return (scale(color, 1.0 / samples));
}
void render_light(t_minirt *data, t_ray ray,
					t_hit_record *rec, t_coord pixel)
{
	t_coord view_dir = norm(scale(ray.direction, -1));
	t_coord light_dir = norm(subtract(data->light->position, rec->p));
	t_coord reflect_dir = calculate_reflect_dir(rec->normal, light_dir);
	t_rgb result = {0, 0, 0};

	result = calculate_ambient(data->alight);
	
	int in_shadow = is_in_shadow(data, rec->p, light_dir, length(subtract(data->light->position, rec->p)));
	if (!in_shadow) {
		double diffuse_factor = fmax(dot(rec->normal, light_dir), 0.0);
		t_rgb diffuse = calculate_diffuse(data->light, rec->normal, light_dir, rec->color);
		result = add(result, scale(diffuse, diffuse_factor));   
		double spec_factor = pow(fmax(dot(view_dir, reflect_dir), 0.0), 32);
		t_rgb specular = calculate_specular(data->light, view_dir, reflect_dir, rec->color);
		result = add(result, scale(specular, spec_factor));
	}
	t_rgb global_illum = global_illumination(data, rec, 2, 1);
	result = add(result, scale(global_illum, data->alight->ratio));
	result = result;
	result = multiply(result, rec->color);
	result.x = result.x / 255;
	result.y = result.y / 255;
	result.z = result.z / 255;
	put_pixel(data->win_data, pixel.x, pixel.y, result);
}

t_rgb global_illumination(t_minirt *data, t_hit_record *rec, int samples, int depth)
{
	int i;
	t_ray scattered_ray;
	t_hit_record new_rec;
	t_rgb indirect_light;
	t_rgb color;

	color = (t_rgb){0, 0, 0};
	i = -1;
	if (depth <= 0)
		return (color);
	while(++i < samples)
	{
		t_coord random_dir = random_in_hemisphere(rec->normal);
		scattered_ray.origin = rec->p;
		scattered_ray.direction = random_dir;
		scattered_ray.half_fov = 0;
		if (intersect_scene(data, scattered_ray, &new_rec))
		{
			indirect_light = global_illumination(data, &new_rec, 1, depth - 1);
			color = add(color, scale(indirect_light, 0.5));
		}
	}

	return (scale(color, 1.0 / samples));
}
