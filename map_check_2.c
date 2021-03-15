/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:11:27 by cmarien           #+#    #+#             */
/*   Updated: 2021/03/15 13:28:52 by cmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		map_create(char *lines, int ***map, int *y, int *x)
{
	int index;
	int	count;

	index = -1;
	*y = 0;
	while (lines[++index])
		if (lines[index] == '\n')
			*y += 1;
	if (!(*map = malloc(sizeof(int *) * *y)))
		return (error_code('A'));
	index = -1;
	count = 0;
	*x = 0;
	while (lines[++index])
	{
		if (*x < count && lines[index] == '\n')
			*x = count;
		count = (lines[index] == '\n' ? 0 : count + 1);
	}
	while (count < *y)
		if (!(map[0][count++] = malloc(sizeof(int) * *x)))
			return (error_code('A'));
	return (1);
}

int		border_map_check_2(int **map, int i, int j, int x)
{
	if (i == x)
	{
		if (j == 0)
			if ((map[j + 1][i] != 32 && map[j + 1][i] != '1') ||
				(map[j][i - 1] != 32 && map[j][i - 1] != '1'))
				return (0);
		if (j > 0)
			if ((map[j - 1][i] != 32 && map[j - 1][i] != '1') ||
				(map[j][i - 1] != 32 && map[j][i - 1] != '1'))
				return (0);
	}
	if (i > 0 && i < x)
	{
		if (j == 0)
			if ((map[j + 1][i] != 32 && map[j + 1][i] != '1') ||
				(map[j][i + 1] != 32 && map[j][i + 1] != '1') ||
				(map[j][i - 1] != 32 && map[j][i + 1] != '1'))
				return (0);
		if (j > 0)
			if ((map[j - 1][i] != 32 && map[j - 1][i] != '1') ||
				(map[j][i + 1] != 32 && map[j][i + 1] != '1') ||
				(map[j][i - 1] != 32 && map[j][i - 1] != '1'))
				return (0);
	}
	return (1);
}

int		core_map_check_2(int **map, int i, int j, int t)
{
	if (i == 0)
	{
		if ((map[j + 1][i] != t && map[j + 1][i] != '1') ||
			(map[j][i + 1] != t && map[j][i + 1] != '1') ||
			(map[j - 1][i] != t && map[j - 1][i] != '1'))
			return (0);
	}
	return (1);
}

int		core_set(int **map, int j, int i, int t)
{
	if (map[j][i] != t && map[j][i] != '1' && map[j][i] != 'N'
			&& map[j][i] != 'S' && map[j][i] != 'E' && map[j][i] != 'W')
		return (0);
	return (1);
}
