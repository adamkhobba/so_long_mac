/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:29:16 by akhobba           #+#    #+#             */
/*   Updated: 2024/04/01 20:46:10 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/so_long_bonus.h"

void	img_ptr(t_data *data)
{
	int	width;
	int	height;

	width = 64;
	height = 64;
	data->wall = mlx_xpm_file_to_image(data->mlx, "./textures/wall.xpm", &width,
			&height);
	data->floor = mlx_xpm_file_to_image(data->mlx, "./textures/floor.xpm",
			&width, &height);
	data->coin = mlx_xpm_file_to_image(data->mlx, "./textures/coin1.xpm",
			&width, &height);
	if (data->map->collectif_count != data->map->collected)
		data->exit = mlx_xpm_file_to_image(data->mlx, "./textures/exit_f.xpm",
				&width, &height);
	else
		data->exit = mlx_xpm_file_to_image(data->mlx, "./textures/odoor_f.xpm",
				&width, &height);
}

int	grid(t_data *data)
{
	ft_anim_enem(data);
	data->y = 0;
	while (data->y < data->map->height)
	{
		data->x = 0;
		while (data->x < data->map->width)
		{
			if (data->map->map[data->y][data->x] == 'G')
				mlx_put_image_to_window(data->mlx, data->win, data->grid,
					data->x * 64, data->y * 64);
			data->x++;
		}
		data->y++;
	}
	return (1);
}

int	put_player(t_data *data)
{
	int	width;
	int	height;

	width = 64;
	height = 64;
	if (data->view == 2)
		data->player = mlx_xpm_file_to_image(data->mlx,
				"./textures/Character.xpm", &width, &height);
	else if (data->view == 1)
		data->player = mlx_xpm_file_to_image(data->mlx,
				"./textures/Character_top.xpm", &width, &height);
	else if (data->view == 3)
		data->player = mlx_xpm_file_to_image(data->mlx,
				"./textures/Character_right2.xpm", &width, &height);
	else if (data->view == 4)
		data->player = mlx_xpm_file_to_image(data->mlx,
				"./textures/Character_left.xpm", &width, &height);
	ft_invalid_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->player,
		data->map->p_pos_x * PIXEL, data->map->p_pos_y * PIXEL);
	mlx_hook(data->win, 2, 1L << 0, &move, data);
	return (1);
}

int	draw_map(t_data *data)
{
	data->y = -1;
	while (++data->y < data->map->height)
	{
		data->x = -1;
		while (data->x++ < data->map->width)
		{
			if (data->map->map[data->y][data->x] == '1')
				data->img_ptr = data->wall;
			else if (data->map->map[data->y][data->x] == 'C')
				data->img_ptr = data->coin;
			else if (data->map->map[data->y][data->x] == 'E')
				data->img_ptr = data->exit;
			else
				data->img_ptr = data->floor;
			ft_invalid_image_p(data);
			mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, data->x
				* 64, data->y * 64);
		}
	}
	put_player(data);
	mlx_loop_hook(data->mlx, grid, data);
	return (1);
}
