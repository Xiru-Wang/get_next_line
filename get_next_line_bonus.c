/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:45:11 by xiwang            #+#    #+#             */
/*   Updated: 2023/07/11 19:04:48 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
//OPEN_MAX: ulimit -a

char	*read_file(int fd, char *str);
char	*get_line_bonus(char *str);
char	*get_rest(char *str);

char	*get_next_line(int fd)
{
	static char	*saved[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved[fd] = read_file(fd, saved[fd]);
	if (saved[fd] == NULL)
		return (NULL);
	line = get_line_bonus(saved[fd]);
	saved[fd] = get_rest(saved[fd]);
	return (line);
}

char	*read_file(int fd, char *str)
{
	char	*temp;
	ssize_t	n;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	n = 1;
	while (n > 0 && ft_strchr(str, '\n') == NULL)
	{
		n = read(fd, temp, BUFFER_SIZE);
		if (n == -1)
		{
			free(temp);
			free(str);
			return (NULL);
		}
		temp[n] = 0;
		str = ft_strjoin(str, temp);
	}
	free(temp);
	return (str);
}

char	*get_line_bonus(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (str[i] == 0)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*get_rest(char *str)
{
	int		i;
	int		k;
	char	*rest;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == 0)
	{
		free(str);
		return (NULL);
	}
	rest = (char *)malloc(ft_strlen(str) - i + 1);
	if (!rest)
		return (NULL);
	i++;
	k = 0;
	while (str[i])
		rest[k++] = str[i++];
	rest[k] = 0;
	free(str);
	return (rest);
}
