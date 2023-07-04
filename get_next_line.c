/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:40:34 by xiwang            #+#    #+#             */
/*   Updated: 2023/07/04 18:43:12 by xiruwang         ###   ########.fr       */
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

schroeder_jan@posteo.de
*/

char	*get_next_line(int fd)
{
	static char	*stash;//temp storage
	char		*line;

	if (fd < 0 || read(fd, 0 , 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_file(fd, stash);
	if (!stash)
	{
		free(stash);//?
		stash = NULL;//?
		return (NULL);
	}
	line = get_line(stash);//get a line from stash
	stash = reset_stash(stash);
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
	// 当 read() 函数返回值为 0 时，表示已经读取到了文件的结尾（EOF）。
	while ((read_byte = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_byte] = '\0';//手动添加string
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
	//if (read_byte == 0)//read nothing, break the loop
	//	break;
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
	line = (char *)malloc(i + 2);//为目标行的字符数（包括换行符）加上空字符预留的空间
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
	if (stash[i] == 0)//end of line
	{
		free(stash);//不懂这一步
		return (NULL);//不懂
	}
	new = (char *)malloc(ft_strlen(stash) - i + 1);
	if (!new)
		return (NULL);
	i++; // skip '\n'
	k = 0;
	while (stash[i])
		new[k++] = stash[i++];
	free(stash);//复制完剩饭，free原来的
	return (new);
}


int	main()
{
	int fd = open("filename.txt", O_RDONLY);
	get_next_line(fd);
	close(fd);
	return (0);
}
//...ErQSHTv6ewY3NF8//
