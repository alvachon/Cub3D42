/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/06/12 11:45:35 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//finds the tile from given x and y (and x and y directions) and returns its type
int	find_hit_type(t_ray *r)
{
	t_tile	*hit_tile;

	hit_tile = find_tile((int)r->x_coord, (int)r->y_coord);

	printf("Hit Tile : %.3f, %.3f\n", r->x_coord, r->y_coord); //	0======== DEBUG ========0
	if (hit_tile)
	{
		printf("Hit Type : %i\n\n", hit_tile->type); //	0======== DEBUG ========0
		return (hit_tile->type);
	}
	else
	{
		printf("Hit Type : NOT FOUND\n\n"); //	0======== DEBUG ========0
		return (TTYPE_ERROR);
	}

}

void	find_first_ray_dists(t_ray *r)
{
	if (!(r->ignore_x))
	{
		if ((-90 <= r->angle && r->angle <= 90) || (270 <= r->angle && r->angle <= 450))
		{
			printf("\nPositive x dir\n"); //	0======== DEBUG ========0
			r->x_ray_dist = fabs(((r->player_pos->x) - floor(r->player_pos->x)) * r->x_to_ray_ratio); //	will crash at right angle
		}
		else
		{
			printf("\nNegative x dir\n"); //	0======== DEBUG ========0
			r->x_ray_dist = fabs((1 - ((r->player_pos->x) - floor(r->player_pos->x))) * r->x_to_ray_ratio); //	will crash at right angle
		}
	}
	else
		r->x_ray_dist = INFINITY;
	if (!(r->ignore_y))
	{
		if ((0 <= r->angle && r->angle <= 180) || (360 <= r->angle && r->angle <= 540))
		{
			printf("\nPositive y dir\n"); //	0======== DEBUG ========0
			r->y_ray_dist = fabs(((r->player_pos->y) - floor(r->player_pos->y)) * r->y_to_ray_ratio);
		}
		else
		{
			printf("\nNegative y dir\n"); //	0======== DEBUG ========0
			printf("7\n");
			r->y_ray_dist = fabs((1 - ((r->player_pos->y) - floor(r->player_pos->y))) * r->y_to_ray_ratio); //	will crash at right angle
		}
	}
	else
		r->y_ray_dist = INFINITY;

	printf("\nInitial distance in x : %.3f\n", r->x_ray_dist); //		0======== DEBUG ========0
	printf("Initial DIstance in y: %.3f\n\n", r->y_ray_dist); //	0======== DEBUG ========0
}

bool	evaluate_x_hits(t_ray *r)
{
	printf("Switching to X checks\n"); //	0======== DEBUG ========0
	while (r->x_ray_dist <= r->y_ray_dist)
	{
		r->x_coord = r->player_pos->x + (r->x_ray_dist * r->ray_to_x_ratio);
		r->y_coord = r->player_pos->y + (r->x_ray_dist * r->ray_to_y_ratio);

		r->hit_type = find_hit_type(r);

		if (r->hit_type == TTYPE_WALL)
		{
			printf("Distance : %.3f\n\n", r->x_ray_dist); //	0======== DEBUG ========0
			return (true);
		}
		else if (r->hit_type == TTYPE_ERROR)
		{
			printf("Out of bound at %.3f:%.3f\n", r->x_coord, r->y_coord); //	0======== DEBUG ========0
			printf("Distance : %.3f\n", r->x_ray_dist); //	0======== DEBUG ========0
			return (true);
		}
		r->x_ray_dist += fabs(r->x_to_ray_ratio); //	increment distance in x
	}
	return (false);
}

bool	evaluate_y_hits(t_ray *r)
{
	printf("Switching to Y checks\n"); //	0======== DEBUG ========0
	while (r->y_ray_dist <= r->x_ray_dist)
	{
		r->x_coord = r->player_pos->x + (r->y_ray_dist * r->ray_to_x_ratio);
		r->y_coord = r->player_pos->y + (r->y_ray_dist * r->ray_to_y_ratio);

		r->hit_type = find_hit_type(r);

		if (r->hit_type == TTYPE_WALL)
		{
			printf("Distance : %.3f\n\n", r->y_ray_dist); //	0======== DEBUG ========0
			return (true);
		}
		else if (r->hit_type == TTYPE_ERROR)
		{
			printf("Out of bound at %.3f:%.3f\n", r->x_coord, r->y_coord); //	0======== DEBUG ========0
			printf("Distance : %.3f\n", r->y_ray_dist); //	0======== DEBUG ========0
			return (true);
		}
		r->y_ray_dist += fabs(r->y_to_ray_ratio); //	increment distance in y
	}
	return (false);
}

t_ray	*cast_ray(t_vector *pos, double ray_angle)
{
	t_ray	*r;

	r = ft_calloc(1, sizeof(t_ray));

	r->angle = ray_angle + pos->d; //	make the angle relative to the player angle
	r->player_pos = pos;

	find_ratios(r);
	find_first_ray_dists(r);

	while (true) //don't forget test pour si depasse mur (fausse donnée, si oui on doit revoir le calcul)
	{
		if (evaluate_x_hits(r))
			break ;
		if (evaluate_y_hits(r))
			break ;
	}
	if (r->hit_type == TTYPE_ERROR)
	{
		free(r);
		r = NULL;
	}
	return r;

}

/*
	ray_cast()
		from player position & angle
		find the nearest wall (from angle relative to player)
//			find step direction (+/- x, +/- y)
			find Xi and Yi
			find Xratio and Yratio
			while (!hit)
				check in X until Dx > Dy
				check in Y until Dy > Dx
		return hit struct (distance + position + wall type)
*/

