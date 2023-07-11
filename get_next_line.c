/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:40:34 by xiwang            #+#    #+#             */
/*   Updated: 2023/07/11 15:38:19 by xiruwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
ssize_t read(int fd, void *buf, size_t nbyte);
[read()] attempts to read nbyte bytes of data from the object to buf
[Static local variables] value persist across function calls
1. a loop to read the file in chunks/blocks
2. append it to a static var(stash)
3. extract(copy) a single line, and return it as a string
4. reset the stash, prepre for the next call
*/

static char	*read_file(int fd, char *stash);
static char	*get_line(char *stash);
static char	*get_rest(char *stash);

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	stash = get_rest(stash);
	return (line);
}

//be careful with mem leak: malloc will be used in ft_strjoin
static char	*read_file(int fd, char *stash)
{
	ssize_t	bytes;
	char	*temp;

	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	bytes = 1;
	while (bytes > 0 && ft_strchr(stash, '\n') == NULL)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(temp);
			//free(stash);//should I? did not malloc
			return (NULL);
		}
		temp[bytes] = '\0';
		stash = ft_strjoin(stash, temp);
	}
	free(temp);
	return (stash);
}

//if the end of file was reached and does not end with a \n character.
static char	*get_line(char *stash)
{
	unsigned int	i;
	char			*line;

	i = 0;
	if (!stash[i])
		//free(stash);//wrong get_rest还要用
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

/*
copy the rest content in the stash, and return it
*/

static char	*get_rest(char *stash)
{
	char			*new;
	unsigned int	i;
	unsigned int	k;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == 0)
	{
		free(stash);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new)
		return (NULL);
	i++;
	k = 0;
	while (stash[i])
		new[k++] = stash[i++];
	new[k] = '\0';
	free(stash);
	return (new);
}

// int	main()
// {
// 	char *line;
// 	int i = 0;

// 	int fd = open("read_error.txt", O_RDONLY);
// 	while (i < 10)
// 	{
// 		line = get_next_line(fd);
// 		printf("%d: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
//cc -g3 -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
//valgrind --leak-check=full ./a.out
