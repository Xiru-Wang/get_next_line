/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:40:34 by xiwang            #+#    #+#             */
/*   Updated: 2023/07/04 21:04:41 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
ssize_t read(int fd, void *buf, size_t nbyte);
read() attempts to read nbyte bytes of data from the object
fd 是一个已打开的文件描述符，从中读取数据。这个文件描述符可以是一个文件，也可以是一个设备，或者是一个 socket 等。
buf 是一个指针，指向一个缓冲区，用于存储从文件描述符读取的数据。
count 是请求读取的字节数
https://github.com/jdecorte-be/42-Get-next-line/blob/master/get_next_line.c

*/

static char	*read_file(int fd, char *stash);
static char	*get_line(char *stash);
static char *reset_stash(char *stash);


char	*get_next_line(int fd)
{
	static char	*stash;//temp storage
	char		*line;

	if (fd < 0 || read(fd, 0 , 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	stash = reset_stash(stash);
	return (line);
}

static char	*read_file(int fd, char *stash)
{
	ssize_t	read_byte;//signed size_t
	char	*buffer;
	char	*temp;

	if (!stash)//if stash is empty...
		stash = (char *)malloc(1);//stash[0]= 0;??
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while ((read_byte = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_byte] = '\0';//null terminated string
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		if (strchr(buffer, '\n'))
			break;
	}
	if (read_byte == -1)//error to read
	{
		free(buffer);
		return (NULL);
	}
	//if (read_byte == 0)//EOF
	free(buffer);
	return (stash);
}

static char	*get_line(char *stash)
{
	unsigned int	i;
	char			*line;

	i = 0;
	if (stash[i] == 0)//no line to return
		return (NULL);
	while(stash[i] && stash[i]!= '\n')
		i++;
	line = (char *)malloc(i + 2);// \n + \0
	if(!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	//if (stash[i] && stash[i] == '\n')
	line[i] = '\n';
	line[i++] = 0;
	return (line);
}

static char *reset_stash(char *stash)
{
	char			*new;
	unsigned int	i;
	unsigned int	k;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == 0)//end of line, why not first?
	{
		free(stash);
		return (NULL);
	}
	new = (char *)malloc(ft_strlen(stash) - i + 1);
	if (!new)
		return (NULL);
	i++; // skip '\n'
	k = 0;
	while (stash[i])
		new[k++] = stash[i++];
	free(stash);
	return (new);
}

int	main()
{
	int fd = open("filename.txt", O_RDONLY);
	get_next_line(fd);
	close(fd);
	return (0);
}
