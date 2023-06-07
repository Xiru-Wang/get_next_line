/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:41:06 by xiwang            #+#    #+#             */
/*   Updated: 2023/06/07 12:37:44 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>//open()
#include <stdlib.h>//malloc

//https://42-cursus.gitbook.io/guide/useful-tools/file-descriptors-fd

char	*get_next_line(int fd);

// 下面是一个基础的`get_next_line`函数的实现。
// 这个实现没有考虑到一些边界情况和错误处理，你可能需要根据实际需要进行修改。在使用这个函数之前，
// 你应该使用`open()`函数打开你想要读取的文件，并得到一个文件描述符。

#include <unistd.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

char	*get_next_line(int fd)
{
	static char *buffer = NULL;
	char	*newline_ptr;
	char	*result;
	ssize_t	read_size;

	if (!buffer)
	{
		buffer = malloc(sizeof(char) * (BUFF_SIZE + 1));
		if (!buffer)
			return (NULL); // Failed to allocate memory
		buffer[0] = '\0';
	}

	newline_ptr = strchr(buffer, '\n');
	while (!newline_ptr)
	{
		read_size = read(fd, buffer + strlen(buffer), BUFF_SIZE - strlen(buffer));
		if (read_size <= 0)
			break ;
		buffer[read_size] = '\0';
		newline_ptr = strchr(buffer, '\n');
	}

	if (newline_ptr)
	{
		*newline_ptr = '\0';
		result = strdup(buffer);
		memmove(buffer, newline_ptr + 1, strlen(newline_ptr + 1) + 1);
	}
	else if (strlen(buffer) > 0)
	{
		result = strdup(buffer);
		buffer[0] = '\0';
	}
	else
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (result);
}

// 这个函数会维持一个静态缓冲区用于存储未处理的输入。当调用`get_next_line`时，会首先检查缓冲区中是否有一个完整的行（即包含换行符）。
// 如果没有，它会尝试从文件描述符读取更多的数据到缓冲区，然后再次进行检查。
// 如果找到一个完整的行，它会将这一行从缓冲区中删除，并返回一个包含这一行内容的新字符串。
// 如果读取文件到达末尾，但是缓冲区中还有数据，它会返回剩下的数据。然后，下一次调用将返回NULL，表示文件已经完全读取完毕。
