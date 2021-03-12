/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:44:48 by cmarien           #+#    #+#             */
/*   Updated: 2021/03/12 14:11:39 by cmarien          ###   ########.fr       */
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

int	ft_atoi(const char *str, int *i)
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

int		line_check(const char *line)
{
	int index;

	index = -1;
	while (line[++index])
		if (line[index] == '1')
			return (1);
	return (0);
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
	else if (c == 'P')
		write(2, "Error\nNo Player In Map", 22);
	else if (c == 'p')
		write(2, "Error\nToo Many Player In Map", 28);
	return (0);
}

int		resolution_check(char *line, t_cub *cub, int index)
{
	if ((cub->res_x = ft_atoi(line, &index)) < 0)
		return (error_code('R'));
	if ((cub->res_y = ft_atoi(line, &index)) < 0)
		return (error_code('R'));
	while (line[index])
	{
		if ((line[index] != ' ' || line[index] == '\t') && line[index] != '\n')
			return (error_code('R'));
		index++;
	}
	return (1);
}

int		texture_path_check(char *line , t_cub *cub, int index, char orientation)
{
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == '\0')
		return (error_code('T'));
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
	while (line[index + 1])
	{
		if ((line[index] == ' ' || line[index] == '\t') && (line[index + 1] != ' ' && line[index + 1] != '\t' && line[index + 1] != '\n'))
			return (error_code('T'));
		index++;
	}
	return (1);
}

int		floor_check(char *line, t_cub *cub, int index)
{
	if ((cub->floor_color = (ft_atoi(line, &index) * 65536)) < 0)
		return (error_code('F'));
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == ',')
		index++;
	if ((cub->floor_color += (ft_atoi(line, &index) * 256)) < 0)
		return (error_code('F'));
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == ',')
		index++;
	if ((cub->floor_color += ft_atoi(line, &index)) < 0)
		return (error_code('F'));
	index--;
	while (line[++index])
		if (line[index] != ' ' && line[index] != '\t')
			return (error_code('F'));
	return (1);
}

int		ceiling_check(char *line, t_cub *cub, int index)
{
	if ((cub->ceiling_color = (ft_atoi(line, &index) * 65536)) < 0)
		return (error_code('C'));
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == ',')
		index++;
	if ((cub->ceiling_color += (ft_atoi(line, &index) * 256)) < 0)
		return	(error_code('C'));
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == ',')
		index++;
	if ((cub->ceiling_color += ft_atoi(line, &index)) < 0)
		return (error_code('C'));
	index--;
	while (line[++index])
		if (line[index] != ' ' && line[index] != '\t')
			return (error_code('C'));
	return (1);
}

int		map_verif(char *line, t_cub *cub)
{
	if (cub->start == 0)
	{
		cub->start = 1;
		cub->str = ft_strndup(line);
		if (cub->str == NULL)
			return (error_code('A'));
	}
	return (1);
}

int		check_line(char *line, t_cub *cub)
{

	int			index;

	index = 0;
	if (line[index] == '\0')
		return (1);
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == 'R')
		return (resolution_check(line, cub, index + 1));
	else if (line[index] == 'N' && line[index + 1] == 'O')
		return (texture_path_check(line, cub, index + 2, 'N'));
	else if (line[index] == 'S' && line[index + 1] == 'O')
		return (texture_path_check(line, cub, index + 2, 'S'));
	else if (line[index] == 'E' && line[index + 1] == 'A')
		return (texture_path_check(line, cub, index + 2, 'E'));
	else if (line[index] == 'W' && line[index + 1] == 'E')
		return (texture_path_check(line, cub, index + 2, 'W'));
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

int		map_create(char *lines, int ***map, int *y, int *x)
{
	int index;
	int	count;

	index = -1;
	count = 0;
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
		if (lines[index] != '\n')
			count++;
		else
		{
			if (*x < count)
				*x = count;
			count = 0;
		}
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
				{
					printf("%d\n", map[j + 1][i]);
					return (0);
				}
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

int		core_set(int **map, int j, int i, int t)
{
	if (map[j][i] != t && map[j][i] != '1' && map[j][i] != 'N'
			&& map[j][i] != 'S' && map[j][i] != 'E' && map[j][i] != 'W')
		return (0);
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
			if ((core_set(map, j + 1, i, t)) == 0 ||
				(core_set(map, j, i - 1, t)) == 0 ||
				(core_set(map, j - 1, i, t)) == 0 || t == '0')
				return (0);
		}
		if (i > 0 && i < x)
		{
			if ((core_set(map, j + 1, i, t)) == 0 ||
				(core_set(map, j, i + 1, t)) == 0 ||
				(core_set(map, j - 1, i, t)) == 0 ||
				(core_set(map, j, i - 1, t)) == 0)
				return (0);
		}
	}
	return (1);
}

int		map_check(int **map, int x, int y)
{
	int	i;
	int	j;
	int is_player;

	j = -1;
	is_player = 0;
	while (++j <= y)
	{
		i = -1;
		while (++i <= x)
			if (map[j][i] != '1')
			{
				if (map[j][i] == 'N' || map[j][i] == 'W' || map[j][i] == 'S'
						|| map[j][i] == 'E')
					is_player += 1;
				if (j == 0 || j == y)
					if (border_map_check(map, i, j, x) == 0)
						return (error_code('M'));
				if (j > 0 && j < y)
					if (core_map_check(map, i, j, x) == 0)
						return (error_code('M'));
			}
	}
	if (is_player == 1)
		return (1);
	return (is_player == 0 ? error_code('P') : error_code('p'));
}

int		map_edit(t_cub *cub)
{
	int	index;
	int	x;
	int y;

	x = 0;
	y = -1;
	index = 0;
	while (++y < cub->y)
	{
		while (x < cub->x)
		{
			if (cub->str[index] == '\n')
			{
				while (x < cub->x && x > 0)
				{
					cub->map[y][x] = ' ';
					x++;
				}
				index++;
			}
			else
			{
				cub->map[y][x] = cub->str[index++];
				x++;
			}
		}
		x = 0;
	}
	cub->y--;
	cub->x--;
	return (map_check(cub->map, cub->x, cub->y));
}

int		cub_parse(char *str, t_cub *cub)
{
	char	*tmp;
	int		fd;
	char	*line;

	cub->start = 0;
	if ((fd = check_map_format(str)) == 0)
		return (0);
	while ((cub->error = get_next_line(fd, &line)) != 0)
	{
		if (cub->error < 0)
			return (0);
		if (cub->start == 1)
		{
			if (line_check(line) == 0)
				break;
			tmp = ft_strjoin(cub->str, line);
			free(cub->str);
			cub->str = tmp;
		}
		else if (check_line(line, cub) == 0)
			return (0);
		free(line);
	}
	if (map_create(cub->str, &cub->map, &cub->y, &cub->x) == 0)
		return (0);
	if (map_edit(cub) == 0)
		return (0);
	return (1);
}

int		main()
{
	t_cub	cub;

	if (cub_parse("map.cub", &cub) == 1)
		write(1, "OUI", 3);
	return (0);
}
