/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:47:27 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/04 12:01:21 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

t_coord vector_cross(t_coord v1, t_coord v2)
{
    t_coord cross_product;

    cross_product.x = v1.y * v2.z - v1.z * v2.y;
    cross_product.y = v1.z * v2.x - v1.x * v2.z;
    cross_product.z = v1.x * v2.y - v1.y * v2.x;

    return (cross_product);
}

double	vector_dot(t_coord v1, t_coord v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_coord	vector_norm(t_coord v)
{
	double length;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length == 0)
		return (v);
	return (vector_scale(v, 1 / length));
}
