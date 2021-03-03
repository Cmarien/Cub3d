/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:44:48 by cmarien           #+#    #+#             */
/*   Updated: 2021/03/03 15:19:01 by cmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (i = open(str, O_RDONLY) == -1)
			return (0);
		close(i);
		return (i);
	}
	write(2, "Error\n", 6);
	write(2, "Wrong Format for ", 18);
	write(2, str, ft_strlen(str));
	return (0);
}

t_cub	error_code(char c)
{
	if (c == 'R')
		write("Error\nWrong Resolution", 22);
	else if (c == 'T')
		write("Error\nWrong Texture Path", 30);
	else if (c == 'F')
		write("Error\nWrong Floor Color Code", 28);
	else if (c == 'C')
		write("Error\nWrong Ceiling Color Code", 31);
	else if (c == 'c')
		write("Error\nWrong Line In Configuration File", 39);
}

t_cub	resolution_check(char *line, t_cub cub, int index)
{
	if (cub.res_x = ft_atoi(line, index) < 0)
		return (error_code('R'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	if (cub.res_y = ft_atoi(line, index) < 0)
		return (error_code('R'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index])
		if (line[index++] != ' ')
			return (error_code('R'));
	return (cub);
}

t_cub	texture_path_check(char *line , t_cub cub, int index, char orientation)
{
	while (line[index] == ' ')
		index++;
	if (orientation == 'N')
		cub.north = ft_str_i_dup(line, index);
	else if (orientation == 'S')
		cub.south = ft_str_i_dup(line, index);
	else if (orientation == 'E')
		cub.east = ft_str_i_dup(line, index);
	else if (orientation == 'W')
		cub.west = ft_str_i_dup(line, index);
	else if (orientation == 's')
		cub.sprite = ft_str_i_dup(line,index);
	else
		return (error_code('T'));
	while (line[index] == ' ')
		index++;
	if (line[index])
		return (error_code('T'));
	return (cub);
}

t_cub	floor_check(char *line, t_cub cub, int index)
{
	if (cub.floor_r = ft_atoi(line, index) < 0)
		return (error_code('F'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index] == ' ')
		index++;
	if (line[index] == ',')
		index++;
	if (cub.floor_g = ft_atoi(line, index) < 0)
		return (error_code('F'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index] == ' ')
		index++;
	if (line[index] == ',')
		index++;
	if (cub.floor_b = ft_atoi(line, index) < 0)
		return (error_code('F'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index])
		if (line[index++] != ' ')
			return (error_code('F'));
	return (cub);
}

t_cub	ceiling_check(char *line, t_cub cub, int index)
{
	if (cub.ceiling_r = ft_atoi(line, index) < 0)
		return (error_code('C'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index] == ' ')
		index++;
	if (line[index] == ',')
		index++;
	if (cub.ceiling_g = ft_atoi(line, index) < 0)
		return	(error_code('C'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index] == ' ')
		index++;
	if (line[index] == ',')
		index++;
	if (cub.ceiling_b = ft_atoi(line, index) < 0)
		return (error_code('C'));
	while (line[index] >= '0' && line[index] <= '9')
		index++;
	while (line[index])
		if (line[index++] != ' ')
			return (error_code('C'));
	return (cub);
}

t_cub	map_check(char *line, t_cub cub, int index)
{
	if (cub.start == 0)
	{
		cub.start = 1;
		cub.map = ft_strdup(line);
		return (cub);
	}
}

t_cub	check_line(char *line, t_cub cub);
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
	else if (line[index] = 'S' && line[index + 1] == ' ')
		return (texture_path_check(line, cub, index + 1, 's'));
	else if (line[index] = 'F')
		return (floor_check(line, cub, index + 1));
	else if (line[index] = 'C')
		return (ceiling_check(line, cub, index + 1));
	else if (line[index] == '1')
		return (map_check(line, cub, index + 1));
	return (error_code('c');
}

void	map_create(char *lines, int ***map)
{
	int index;
	int	j;
	int	count;

	index = -1;
	count = 0;
	j = 0;
	while (line[++index])
		if (line[index] == '\n')
			count++;
	if(!(map = malloc(sizeof(int *) * count)))
		return (NULL);
	index = -1;
	count = 0;
	while (line[++index])
		if (line[index] != '\n')
			count++;
		else
		{
			if(!(map[j++] = malloc(sizeof(int) * count)))
				return (NULL);
			count = 0;
		}
}

int		map_check(int **map, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j][i] == 0 && i < x)
		i++;
	while (map[j][i] == 1 && i < x)
		i++;
	while (map[j][i] == 0 && i < x)
		if (map[j][i] != 0)
			return (error_code('M'));
	while (j++ < y)
	{
		i = 0;
		while (map[j][i] == 0 && i < x)
			i++;
	}
}

void	map_edit(char *lines, int ***map, int *x, int *y)
{
	int	index;

	index = -1;
	x = 0;
	y = 0;
	while (line[++index])
	{
		if (line[index] == '\n' && line[index + 1] != '\0')
		{	
			y++;
			x = 0;
		}
		else if (line[index] == ' ')
			map[y][x++] = 0;
		else
			map[y][x++] = line[index];
	}
	x--;
	return (map_check(*map, x, y));
}

t_cub	cub_parse(char *str)
{
	t_cub	cub;
	char	*tmp;
	int		fd;
	char	*line;

	cub.start = 0;
	if (fd = check_map_format(str) == 0)
		return (NULL);
	while (get_next_line(fd, &line) != 0)
	{
		if (cub.start == 1)
		{
			tmp = ft_join(cub.str, line);
			free(cub.str);
			cub.str = tmp;
		}
		else
			if (cub = check_line(line, cub) == NULL)
				return (NULL);
		free(line);
	}
	map_create(cub.str, &cub.map);
	map_edit(cub.str, &cub.map, &cub.x, &cub.y);
}
