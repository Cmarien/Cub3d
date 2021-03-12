/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarien <cmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:35:36 by cmarien           #+#    #+#             */
/*   Updated: 2020/12/15 17:04:42 by cmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ch_n(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == '\n')
			j++;
	return (j);
}

char	*str_edit(char *str, int end)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (end == 0)
	{
		free(str);
		str = NULL;
		return (str);
	}
	while (str[i] && str[i] != '\n')
		i++;
	while (str[i++])
		str[j++] = str[i];
	str[j] = '\0';
	return (str);
}
