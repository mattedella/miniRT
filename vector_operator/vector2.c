/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:47:27 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/16 11:47:31 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord	cross(t_coord v1, t_coord v2)
{
	t_coord	cross_product;

	cross_product.x = v1.y * v2.z - v1.z * v2.y;
	cross_product.y = v1.z * v2.x - v1.x * v2.z;
	cross_product.z = v1.x * v2.y - v1.y * v2.x;
	return (cross_product);
}

double	dot(t_coord v1, t_coord v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_coord	norm(t_coord v)
{
	double	length;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length == 0)
		return (v);
	return (scale(v, 1 / length));
}

t_rgb multiply(t_rgb c1, t_rgb c2)
{
    return (t_rgb){
        c1.x * c2.x,
        c1.y * c2.y,
        c1.z * c2.z
    };
}