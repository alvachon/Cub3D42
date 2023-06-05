/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/06/05 13:41:09 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

//copies the .cub file's contents into d.level
void	read_file(int fd)
{
	char		*c;
	t_master	*d;
	int			i;

	c = ft_calloc(1, sizeof(char *));
	d = get_master();
	d->level = ft_calloc(M_CHARS, sizeof(char *));

	i = -1;
	while (++i < M_CHARS)
	{
		if (0 < read(fd, c, 1))
			d->level[i] = c[0];
		else
			break ;
	}
	ft_free_null(ADRS c);
	close(fd);
	if (M_CHARS <= i)
		close_with_error(ERR_MAP_SIZE);
}

/*
Check the path of assets and verify content is there and usable*/
void	check_asset(void)
{
	t_master	*d;
	int			img;
	int			i;

	d = get_master();
	i = 4;
	while (i > 0)
	{
		if (d->t_paths[i])
		{
			img = open(d->t_paths[i], O_RDONLY);
			if (img < 0)
				close_with_error(ERR_FILE_OPEN);
			close(img);
		}
		else
			close_with_error(ERR_FILE_TEXT);
		i--;
	}
}

//opens the .cub file and copies its contents into d.level
void	read_level(char *path)
{
	int	fd;
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (ft_strncmp(&path[i - 4], ".cub", 5))
		close_with_error(ERR_FILE_NAME);
	fd = open(path, O_RDONLY);
	if (fd <= 0)
		close_with_error(ERR_FILE_OPEN);
	read_file(fd);
	close(fd);
	printf(">%s<\n\n", get_master()->level); //	0============ DEBUG ============0

	get_info(); //		parses the non-map info from d.level and voids it (replaces it by \n)
	check_asset();

//	check_info(); //	verifies the texture paths and floor/ceiling colours

}
