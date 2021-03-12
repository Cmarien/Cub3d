/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarien <cmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:43:07 by cmarien           #+#    #+#             */
/*   Updated: 2021/03/08 10:32:45 by cmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			i++;
	while (s2[j])
		j++;
	if (!(str = malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = 0;
	while (s1[size])
		size += 1;
	str = (char*)malloc(sizeof(*str) * size + 1);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = s1[i];
		i++;
	}
	str[size] = '\0';
	return (str);
}

t_list	read_line(int fd, t_list *lst)
{
	int		ret;
	char	buff[BUFFER_SIZE + 1];
	char	*tmp;

	lst->end = 0;
	ret = 0;
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (lst->str == NULL)
			lst->str = ft_strdup(buff);
		else
		{
			tmp = ft_join(lst->str, buff);
			free(lst->str);
			lst->str = tmp;
		}
		if ((lst->r = ch_n(lst->str)) > 0)
			break ;
	}
	lst->end = ret;
	return (*lst);
}

char	*s_dup(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!(line = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int		get_next_line(int fd, char **line)
{
	static t_list	lst;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (!(lst.str) || lst.str == NULL)
	{
		lst.str = NULL;
		lst.r = 0;
	}
	if (lst.r == 0)
		lst = read_line(fd, &lst);
	if (lst.end < 0)
		return (-1);
	if (lst.str == NULL)
		*line = s_dup("");
	else
		*line = s_dup(lst.str);
	lst.str = str_edit(lst.str, lst.end);
	if (lst.r > 0)
		lst.r--;
	if (lst.end == 0)
		return (0);
	return (1);
}
