/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:00:35 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 16:02:31 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rgb	calculate_ambient(t_alight *alight)
{
	return (scale(alight->color, alight->ratio));
}

t_rgb	calculate_diffuse(t_light *light, t_coord normal,
			t_coord light_dir, t_rgb color)
{
	double	diff;

	diff = dot(normal, light_dir);
	return (scale(color, light->brightness * diff));
}

t_rgb	calculate_specular(t_light *light, t_coord view_dir,
	t_coord reflect_dir, t_rgb color)
{
	double	spec;

	spec = pow(dot(view_dir, reflect_dir), 256);
	return (scale(color, light->brightness * spec));
}

t_coord	calculate_reflect_dir(t_coord normal, t_coord light_dir)
{
	double	dot_product;
	t_coord	scaled_normal;

	dot_product = dot(normal, light_dir);
	scaled_normal = scale(normal, dot_product);
	return (norm(subtract(scaled_normal, light_dir)));
}
