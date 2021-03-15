/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 10:47:42 by cmarien           #+#    #+#             */
/*   Updated: 2021/03/15 10:51:55 by cmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (start >= (unsigned int)ft_strlen(s))
	{
		if ((sub = malloc(sizeof(char) * 1)) == NULL)
			return (NULL);
		sub[0] = 0;
		return (sub);
	}
	if ((sub = malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	i = -1;
	while (++i < len && s[start + i])
		sub[i] = s[start + i];
	sub[i] = '\0';
	return (sub);
}

char	*ft_strndup(const char *s1)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = 0;
	while (s1[size])
		size += 1;
	str = (char*)malloc(sizeof(*str) * size + 2);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\n';
	str[i + 1] = '\0';
	return (str);
}

int		ft_atoi(const char *str, int *i)
{
	int sign;
	int nb;

	sign = 1;
	nb = -1;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		*i += 1;
	if (str[*i] == '-')
	{
		sign = -sign;
		*i += 1;
	}
	else if (str[*i] == '+')
		*i += 1;
	if (str[*i] <= '9' && str[*i] >= '0')
		nb = 0;
	while (str[*i] <= '9' && str[*i] >= '0')
	{
		nb *= 10;
		nb += str[*i] - '0';
		*i += 1;
	}
	return (nb * sign);
}

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*str;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (len == 0)
	{
		if (!(str = malloc(sizeof(char) * 1)))
			return (NULL);
		return (str);
	}
	i = 0;
	j = 0;
	if (!(str = malloc(sizeof(char) * len + 2)))
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\n';
	str[j + 1] = '\0';
	return (str);
}
