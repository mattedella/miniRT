/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:07:31 by mdella-r          #+#    #+#             */
/*   Updated: 2024/09/25 15:20:41 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

void	put_pixel(t_wdata *win_data, int x, int y, t_rgb color)
{
	char	*dst;

	dst = win_data->addr + (y * win_data->line_length + x
		* (win_data->bits_per_pixel / 8));
	*(unsigned int*)dst = create_rgb(color.x, color.y, color.z);
}
