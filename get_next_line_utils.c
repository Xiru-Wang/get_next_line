/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:40:29 by xiwang            #+#    #+#             */
/*   Updated: 2023/07/06 18:20:04 by xiruwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}
//return (NULL)

//尽管此函数会修改指针s的值，但由于C语言的参数是按值传递的，因此这种修改不会影响到原始字符串或者函数外部的指针。
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s++)
		i++;
	return (i);
}

/*important*/
char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	k;

	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new || !s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	k = 0;
	while (s2[k])
		new[i++] = s2[k++];
	new[i] = 0;
	free(s1);
	return (new);
}
//free(s1);!! s[0] != 0
