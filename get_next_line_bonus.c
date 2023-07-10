//#header

#include "get_next_line_bonus.h"

static char *read_file(int fd, char *str);
static char *get_line(char *str);
static char *get_rest(char *str);

char	*get_next_line(int fd)
{
	static char	*saved[OPEN_MAX];
	char		*line;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved[fd] = read_file(fd, saved[fd]);
	if (saved[fd] == NULL)
		return (NULL);
	line = get_line(saved[fd]);
	saved[fd] = get_rest(saved[fd]);
	return (line);
}

static char	*read_file(int fd, char *str)
{
	char	*temp;
	ssize_t	n;

	if (str == NULL)
	{
		str = (char *)malloc(1);
		if (!str)
			return (NULL);
		str[0] = 0;
	}
	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	n = 1;
	while( n > 0 && ft_strchr(str, '\n') == NULL)
	{
		n = read(fd, temp, BUFFER_SIZE);
		if( n == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[n] = 0;
		str = ft_strjoin(str, temp);
	}
	free(temp);
	return (str);
}

static char	*get_line(char *str)
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

static char	*get_rest(char *str)
{
	int		i;
	int		k;
	char	*rest;
	if (!str)
		return (NULL);
	i = 0;
	while(str[i] && str[i] != '\n')
		i++;
	rest = (char *)malloc(ft_strlen(str) - i + 1);
	if(!rest)
		return (NULL);
	i++;
	k = 0;
	while (str[i])
	{
		rest[k] = str[i];
		k++;
		i++;
	}
	rest[k] = 0;
	free(str);
	return (rest);
}
