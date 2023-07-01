/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:41:06 by xiwang            #+#    #+#             */
/*   Updated: 2023/07/01 17:42:00 by xiruwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>//open()
#include <stdlib.h>//malloc
#include <unistd.h>//read?
#define BUFFER_SIZE 1024

//https://42-cursus.gitbook.io/guide/useful-tools/file-descriptors-fd

char	*get_next_line(int fd);
