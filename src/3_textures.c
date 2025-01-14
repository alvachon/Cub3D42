/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 14:58:26 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
typedef struct mlx_texture
{
	uint32_t	width;
	uint32_t	height;
	uint8_t		bytes_per_pixel;
	uint8_t*	pixels;
}	mlx_texture_t;
*/

//initializes a mlx texture from a png
mlx_texture_t	*make_texture(char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	return (texture);
}

void	find_texture_pos(t_ray *r)
{
	if (r->is_checking_x)
	{
		r->wall_pos = ((r->y_coord) - floor(r->y_coord));
		if (0 <= r->ray_to_x_ratio)
			r->hit_dir = 1;
		else
			r->hit_dir = 3;
	}
	else
	{
		r->wall_pos = ((r->x_coord) - floor(r->x_coord));
		if (0 <= r->ray_to_y_ratio)
			r->hit_dir = 2;
		else
			r->hit_dir = 0;
	}
	if (r->hit_dir == 2 || r->hit_dir == 3)
		r->wall_pos = (1 - r->wall_pos);
}

t_colour	get_texture_colour(t_slice *s, double h)
{
	mlx_texture_t	*t;
	t_colour		c;
	int				x;
	int				y;

	t = get_master()->textures[s->hit_dir];
	x = (int)floor(s->texture_pos * t->width);
	y = (int)floor(h * t->height);
	c.r = t->pixels[0 + ((x + (y * t->width)) * t->bytes_per_pixel)];
	c.g = t->pixels[1 + ((x + (y * t->width)) * t->bytes_per_pixel)];
	c.b = t->pixels[2 + ((x + (y * t->width)) * t->bytes_per_pixel)];
	return (c);
}
