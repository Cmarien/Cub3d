/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:27:16 by cmarien           #+#    #+#             */
/*   Updated: 2021/03/05 15:21:52 by cmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(const char *str);

typedef struct s_cub
{
	int		start;
	char	*str;
	int		**map;
	int		error;
	int		x;
	int		y;
	int		ceiling_color;
	int		floor_color;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*sprite;
	int		res_x;
	int		res_y;
}			t_cub;

#endif
