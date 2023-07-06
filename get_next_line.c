/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:40:34 by xiwang            #+#    #+#             */
/*   Updated: 2023/07/06 23:14:46 by xiruwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
ssize_t read(int fd, void *buf, size_t nbyte);
[read()] attempts to read nbyte bytes of data from the object to buf
https://github.com/jdecorte-be/42-Get-next-line/blob/master/get_next_line.c
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

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	stash = get_rest(stash);
	return (line);
}

static char	*read_file(int fd, char *stash)
{
	ssize_t	bytes;
	char	*temp;

	if (!stash)
	{
		stash = (char *)malloc(1);
		stash[0] = '\0';
	}
	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(stash, '\n'))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		temp[bytes] = '\0';
		stash = ft_strjoin(stash, temp);
	}
	if (bytes == -1)
	{
		free(temp);
		free(stash);
		return (NULL);
	}
	free(temp);
	return (stash);
}

static char	*get_line(char *stash)
{
	unsigned int	i;
	char			*line;

	i = 0;
	if (stash[i] == 0)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *)malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
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

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == 0)
	{
		free(stash);
		return (NULL);
	}
	new = (char *)malloc(ft_strlen(stash) - i + 1);
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
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
//gcc -Wall -Werror -Wextra -D BUFFER_SIZE=10000 get_next_line.c get_next_line_utils.c
