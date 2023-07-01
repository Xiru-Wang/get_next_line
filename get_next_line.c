/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:40:34 by xiwang            #+#    #+#             */
/*   Updated: 2023/07/01 17:40:14 by xiruwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
ssize_t read(int fd, void *buf, size_t nbyte);
read() attempts to read nbyte bytes of data from the object
fd 是一个已打开的文件描述符，从中读取数据。这个文件描述符可以是一个文件，也可以是一个设备，或者是一个 socket 等。
buf 是一个指针，指向一个缓冲区，用于存储从文件描述符读取的数据。
count 是请求读取的字节数。


*/

char	*get_next_line(int fd)
{
	char		*line;//return value
	static char	*stash;//temp storage

	if (fd < 0 || read(fd, 0 , 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_file(fd, stash);//fill temp
	if (stash == NULL)
		return (NULL);
	line = get_line(stash);//take a line
	stash = reset_stash(stash);//reset the temp
	return (line);
}

static char *read_file(int fd, char *stash)
{
	ssize_t	read_byte;//signed size_t
	char	*buffer;
	char	*temp;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if(!buffer)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte < 0)//error to read
		{
			free(buffer);
			return (NULL);
		}
		else if (read_byte == 0)//read nothing, break the loop
			break;
		buffer[read_byte] = '\0';//terminate the string
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		if (strchr(buffer, '\n'))
			break;
	}
	free(buffer);
	return (stash);
}

static char	*get_line(char *stash)
{
	unsigned int	i;
	char			*line;

	i = 0;
	while(stash[i] && stash[i]!= '\n')
		i++;
	line = (char *)malloc(i + 1);
	if(!line)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i++] = 0;
	return (line);
}

static char *reset_stash(char *stash)
{
	char			*new;
	unsigned int	i;
	unsigned int	k;

	while(stash[i] && stash[i]!= '\n')
		i++;
	new = (char *)malloc(ft_strlen(stash) - i + 1);
	i++;//skip '\n'
	k = 0;
	while (stash[i])
		new[k++] = stash[i++];
	//new[k++] = 0; no need??
	free(stash);
	return (new);
}
