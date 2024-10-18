/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_distance.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:29:42 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 17:13:46 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*closest_dist(void)
{
	static double	dist = DBL_MAX;

	return (&dist);
}

double	*sphere_dist(void)
{
	static double	dist = DBL_MAX;

	return (&dist);
}

double	*cylinder_dist(void)
{
	static double	dist = DBL_MAX;

	return (&dist);
}

double	*plane_dist(void)
{
	static double	dist = DBL_MAX;

	return (&dist);
}

void	set_dist(double t)
{
	*closest_dist() = t;
	*cylinder_dist() = t;
}
