/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:27:16 by cmarien           #+#    #+#             */
/*   Updated: 2021/03/15 13:34:00 by cmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_cub
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
}				t_cub;

int				ft_strlen(const char *str);
int				get_next_line(int fd, char **line);
char			*ft_strdup(const char *s1);
int				map_edit(t_cub *cub);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_atoi(const char *str, int *i);
char			*ft_strndup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				map_create(char *lines, int ***map, int *y, int *x);
int				border_map_check_2(int **map, int i, int j, int x);
int				core_map_check_2(int **map, int i, int j, int t);
int				core_set(int **map, int j, int i, int t);
int				line_check(const char *line);
int				resolution_check(char *line, t_cub *cub, int index);
int				texture_path_check(char *line, t_cub *cub, int index,
		char orientation);
int				floor_check(char *line, t_cub *cub, int index);
int				ceiling_check(char *line, t_cub *cub, int index);
int				map_verif(char *line, t_cub *cub);
int				error_code(char c);

#endif
