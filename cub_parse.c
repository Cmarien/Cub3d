/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:44:48 by cmarien           #+#    #+#             */
/*   Updated: 2021/03/05 15:25:04 by cmarien          ###   ########.fr       */
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

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;
	int		l;

	l = 0;
	i = 0;
	while (src[l])
		l++;
	str = malloc(sizeof(char) * (l + 1));
	if (str == NULL)
		return (NULL);
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_atoi(const char *str, int i)
{
	int sign;
	int nb;

	sign = 1;
	nb = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		nb *= 10;
		nb += str[i] - '0';
		i++;
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

int		check_map_format(char *str)
{
	int i;

	i = 0;
	while (str[i + 1])
		i++;
	while (str[i] != '.')
		i--;
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b' &&
			str[i + 4] == '\0')
	{
		if ((i = open(str, O_RDONLY)) == -1)
			return (0);
		close(i);
		return (i);
	}
	write(2, "Error\n", 6);
	write(2, "Wrong Format for ", 18);
	write(2, str, ft_strlen(str));
	return (0);
}

int		error_code(char c)
{
	if (c == 'R')
		write(2, "Error\nWrong Resolution", 22);
	else if (c == 'T')
		write(2, "Error\nWrong Texture Path", 30);
	else if (c == 'F')
		write(2, "Error\nWrong Floor Color Code", 28);
	else if (c == 'C')
		write(2, "Error\nWrong Ceiling Color Code", 31);
	else if (c == 'c')
		write(2, "Error\nWrong Line In Configuration File", 39);
	else if (c == 'M')
		write(2, "Error\nWrong Map Configuration", 29);
	else if (c == 'A')
		write(2, "Error\nCrash While Allocating Memory", 35); 
	return (0);
}

int		resolution_check(char *line, t_cub *cub, int index)
{
	if ((cub->res_x = ft_atoi(line, index)) < 0)
		return (error_code('R'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	if ((cub->res_y = ft_atoi(line, index)) < 0)
		return (error_code('R'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index])
		if (line[index++] != ' ')
			return (error_code('R'));
	return (1);
}

int		texture_path_check(char *line , t_cub *cub, int index, char orientation)
{
	while (line[index] == ' ')
		index++;
	if (orientation == 'N')
		cub->north = ft_substr(line, index, ft_strlen(line) - (index + 1));
	else if (orientation == 'S')
		cub->south = ft_substr(line, index, ft_strlen(line) - (index + 1));
	else if (orientation == 'E')
		cub->east = ft_substr(line, index, ft_strlen(line) - (index + 1));
	else if (orientation == 'W')
		cub->west = ft_substr(line, index, ft_strlen(line) - (index + 1));
	else if (orientation == 's')
		cub->sprite = ft_substr(line, index, ft_strlen(line) - (index + 1));
	else
		return (error_code('T'));
	while (line[index] == ' ')
		index++;
	if (line[index])
		return (error_code('T'));
	return (1);
}

int		floor_check(char *line, t_cub *cub, int index)
{
	if ((cub->floor_color = (ft_atoi(line, index) * 65536)) < 0)
		return (error_code('F'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index] == ' ')
		index++;
	if (line[index] == ',')
		index++;
	if ((cub->floor_color += (ft_atoi(line, index) * 256)) < 0)
		return (error_code('F'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index] == ' ')
		index++;
	if (line[index] == ',')
		index++;
	if ((cub->floor_color += ft_atoi(line, index)) < 0)
		return (error_code('F'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index])
		if (line[index++] != ' ')
			return (error_code('F'));
	return (1);
}

int		ceiling_check(char *line, t_cub *cub, int index)
{
	if ((cub->ceiling_color = (ft_atoi(line, index) * 65536)) < 0)
		return (error_code('C'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index] == ' ')
		index++;
	if (line[index] == ',')
		index++;
	if ((cub->ceiling_color += (ft_atoi(line, index) * 256)) < 0)
		return	(error_code('C'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index] == ' ')
		index++;
	if (line[index] == ',')
		index++;
	if ((cub->ceiling_color += ft_atoi(line, index)) < 0)
		return (error_code('C'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index])
		if (line[index++] != ' ')
			return (error_code('C'));
	return (1);
}

int		map_verif(char *line, t_cub *cub)
{
	if (cub->start == 0)
	{
		cub->start = 1;
		cub->str = ft_strdup(line);
		if (cub->str == NULL)
			return (error_code('A'));
	}
	return (1);
}

int		check_line(char *line, t_cub *cub)
{
	int			index;

	index = 0;
	while (line[index] == ' ')
		index++;
	if (line[index] == 'R')
		return (resolution_check(line, cub, index + 1));
	else if (line[index] == 'N' && line[index + 1] == 'O')
		return (texture_path_check(line, cub, index + 1, 'N'));
	else if (line[index] == 'S' && line[index + 1] == 'O')
		return (texture_path_check(line, cub, index + 1, 'S'));
	else if (line[index] == 'E' && line[index + 1] == 'A')
		return (texture_path_check(line, cub, index + 1, 'E'));
	else if (line[index] == 'W' && line[index + 1] == 'E')
		return (texture_path_check(line, cub, index + 1, 'W'));
	else if (line[index] == 'S' && line[index + 1] == ' ')
		return (texture_path_check(line, cub, index + 1, 's'));
	else if (line[index] == 'F')
		return (floor_check(line, cub, index + 1));
	else if (line[index] == 'C')
		return (ceiling_check(line, cub, index + 1));
	else if (line[index] == '1')
		return (map_verif(line, cub));
	return (error_code('c'));
}

int		map_create(char *lines, int ***map)
{
	int index;
	int	j;
	int	count;

	index = -1;
	count = 0;
	j = 0;
	while (lines[++index])
		if (lines[index] == '\n')
			count++;
	if(!(map = malloc(sizeof(int *) * count)))
		return (error_code('A'));
	index = -1;
	count = 0;
	while (lines[++index])
		if (lines[index] != '\n')
			count++;
		else
		{
			if(!(map[j++] = malloc(sizeof(int) * count)))
				return (error_code('A'));
			count = 0;
		}
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

int		border_map_check(int **map, int i, int j, int x)
{
	if (map[j][i] != 32 && map[j][i] != '1')
		return (0);
	else if (map[j][i] == 32)
	{
		if (i == 0)
		{
			if (j == 0)
				if ((map[j + 1][i] != 32 && map[j + 1][i] != '1') ||
					(map[j][i + 1] != 32 && map[j][i + 1] != '1'))
					return (0);
			if (j > 0)
				if ((map[j - 1][i] != 32 && map[j - 1][i] != '1') ||
					(map[j][i + 1] != 32 && map[j][i + 1] != '1'))
					return (0);
			if (border_map_check_2(map, i, j, x) == 0)
				return (0);
		}
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

int		core_map_check(int **map, int i, int j, int x)
{
	int t;

	t = map[j][i];
	if (t != '1' && t != '0' && t != 32)
		t = '0';
	if (t != '1')
	{
		if (core_map_check_2(map, i, j, t) == 0)
			return (0);
		if (i == x)
		{
			if ((map[j + 1][i] != t && map[j + 1][i] != '1') ||
				(map[j][i - 1] != t && map[j][i - 1] != '1') ||
				(map[j - 1][i] != t && map[j - 1][i] != '1'))
				return (0);
		}
		if (i > 0 && i < x)
		{
			if ((map[j + 1][i] != t && map[j + 1][i] != '1') ||
				(map[j][i + 1] != t && map[j][i + 1] != '1') ||
				(map[j - 1][i] != t && map[j - 1][i] != '1') ||
				(map[j][i - 1] != t && map[j][i - 1] != '1'))
				return (0);
		}
	}
	return (1);
}

int		map_check(int **map, int x, int y)
{
	int	i;
	int	j;

	j = -1;
	while (++j < y)
	{
		i = -1;
		while (++i <= x)
			if (map[j][i] != '1')
			{
				if (j == 0 || j == y)
					if (border_map_check(map, i, j, x) == 0)
						return (error_code('M'));
				if (j > 0 && j < y)
					if (core_map_check(map, i, j, x) == 0)
						return (error_code('M'));
			}
	}
	return (1);
}

int		map_edit(t_cub *cub)
{
	int	index;

	index = -1;
	cub->x = 0;
	cub->y = 0;
	while (cub->str[++index])
	{
		if (cub->str[index] == '\n' && cub->str[index + 1] != '\0')
		{	
			cub->y++;
			cub->x = 0;
		}
		else
			cub->map[cub->y][cub->x++] = cub->str[index];
	}
	cub->x--;
	cub->error = map_check(cub->map, cub->x, cub->y);
	return (cub->error);
}

t_cub	cub_parse(char *str)
{
	t_cub	cub;
	char	*tmp;
	int		fd;
	char	*line;

	cub.start = 0;
	cub.error = 1;
	if ((fd = check_map_format(str)) == 0)
		return (cub);
	while (get_next_line(fd, &line) != 0)
	{
		if (cub.start == 1)
		{
			tmp = ft_strjoin(cub.str, line);
			free(cub.str);
			cub.str = tmp;
		}
		else
			if (check_line(line, &cub) == 0)
			{
				cub.error = 0;
				return (cub);
			}
		free(line);
	}
	if (map_create(cub.str, &cub.map) == 0)
		return (cub);
	if (map_edit(&cub) == 0)
		return (cub);
	return (cub);
}
