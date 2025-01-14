/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:51:15 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 10:16:57 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//	0================ DEBUG FUNCTIONS ================0

void	print_tile(t_tile *tile)
{
	if (tile)
	{
		if (tile->coords)
			printf("%i:%i", tile->coords->x, tile->coords->y);
		else
			printf("ERR");
	}
	else
		printf("NUL");
}

void	print_neighbours(t_tile *tile)
{
	printf("\n     [");
	print_tile(tile->north);
	printf("]\n[");
	print_tile(tile->west);
	printf("] ");
	print_tile(tile);
	printf(" [");
	print_tile(tile->east);
	printf("]\n     [");
	print_tile(tile->south);
	printf("]\n");
}

void	print_tiles(void)
{
	t_tile	**tiles;
	int		i;

	tiles = get_master()->tiles;
	i = -1;
	while (tiles[++i])
	{
		print_neighbours(tiles[i]);
	}
}

void	announce_tile(t_tile *tile, char c)
{
	printf("Created tile at %i:%i with type ", tile->coords->x,
			tile->coords->y);
	if (tile->type == TTYPE_ROOM)
		printf("floor");
	else if (tile->type == TTYPE_WALL)
		printf("wall ");
	else
		printf("%i", tile->type);
	printf(" (%c)\n", c);
}

void	print_paths(void)
{
	t_master	*d;
	int			i;

	d = get_master();
	i = -1;
	printf("\n");
	if (d->t_paths)
	{
		while (++i < ASSET_COUNT)
		{
			if (d->t_paths && d->t_paths[i])
				printf("Path %i  : '%s'\n", i, d->t_paths[i]);
			else
				printf("Path %i  : missing\n", i);
		}
	}
	else
		printf("Paths    : missing\n");
}

void	print_colours(void)
{
	t_master	*d;
	int			i;

	d = get_master();
	i = -1;
	printf("\n");
	if (d->c_floor)
		printf("Floor   : '%i,%i,%i'\n", d->c_floor->r, d->c_floor->g,
				d->c_floor->b);
	else
		printf("Floor   : missing\n");
	if (d->c_floor)
		printf("Ceiling : '%i,%i,%i'\n", d->c_ceiling->r, d->c_ceiling->g,
				d->c_ceiling->b);
	else
		printf("Ceiling : missing\n");
}

void	print_entity(t_entity *e)
{
	printf("\nEntity with radius %.2f at (%.2f : %.2f) looking towards %.2f\n",
			e->radius, e->vector->x, e->vector->y, e->vector->d);
}
