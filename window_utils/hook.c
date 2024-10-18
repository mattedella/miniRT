/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:49:00 by mdella-r          #+#    #+#             */
/*   Updated: 2024/10/18 17:13:27 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	key_hook(int keycode, t_minirt *data)
{
	if (keycode == ESC_KEY)
		quit(0, data->win_data, NULL, NULL);
	return (0);
}

void	init_hit_record(t_hit_record *rec)
{
	rec->t = 0;
	rec->p.x = 0;
	rec->p.y = 0;
	rec->p.z = 0;
	rec->normal.x = 0;
	rec->normal.y = 0;
	rec->normal.z = 0;
	rec->color.x = 0;
	rec->color.y = 0;
	rec->color.y = 0;
}
