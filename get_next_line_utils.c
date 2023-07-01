/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:40:29 by xiwang            #+#    #+#             */
/*   Updated: 2023/07/01 17:43:52 by xiruwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//find \n
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while(*s)
		i++;
	return (i);
}

//find what left in buffer
/*
The substring begins at index ’start’ and is of maximum size ’len’.
sub ---> a new string
*/
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t i;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	if (start >= i)
	{
		ret = malloc(1);
		if (!ret)
			return (NULL);
		*ret = 0;
		return (ret);
	}
	if (start + len >  i)
		len = i - start;
	ret = (char *)malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	while(len--)//not sure if it's working
	{
		*ret = *(s + start);
		ret++;
		s++;
	}
	*ret = 0;
	return (ret);
}

char	*ft_strdup(const char *s1)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (new_str == NULL)
		return (NULL);
	while(*s1)
		*new_str++ = *s1++;//check again
	*new_str = 0;
	return (new_str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)//  ||!s1 || !s2
		return (NULL);
	while (*s1)
		*new++ = *s1++;
	while (*s2)
		*new++ = *s2++;
	*new = 0;
	return (new);
}
