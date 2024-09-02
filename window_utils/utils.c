/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:03:27 by mdella-r          #+#    #+#             */
/*   Updated: 2024/08/29 17:33:57 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT.h"

static int	quit(char id, t_wdata *data)
{
	if (data)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(id);
}

int	press_x(t_wdata *data)
{
	quit(0, data);
	return (0);
}

int	key_hook(int keycode, t_wdata *data)
{
	if (keycode == ESC_KEY)
		quit(0, data);
	if (keycode == S_KEY)
		printf("sono la sfera!!!\n");
	if (keycode == C_KEY)
		printf("sono la camera!!\n");
	if (keycode == P_KEY)
		printf("sono il piano!!\n");
	if (keycode == Y_KEY)
		printf("sono il cilindro!!\n");
	if (keycode == L_KEY)
		printf("sono le luci!!\n");
	if (keycode == A_KEY)
		printf("ruotato verso sinistra!!\n");
	if (keycode == D_KEY)
		printf("ruotato verso destra!!\n");
	if (keycode == UP_ARROW)
		printf("mosso verso l'alto!!\n");
	if (keycode == DOWN_ARROW)
		printf("mosso verso il basso!!\n");
	if (keycode == LEFT_ARROW)
		printf("mosso verso sinistra!!\n");
	if (keycode == RIGHT_ARROW)
		printf("mosso verso destra!!\n");
	return (0);
}
