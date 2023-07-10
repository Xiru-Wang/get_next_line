/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:45:29 by xiwang            #+#    #+#             */
/*   Updated: 2023/07/10 19:45:32 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	len;
	len = 0;
	while(str[len])
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	//if(!s)
	//	return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (c == 0)
		return (s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;

	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if(!new || !s1 || !s2)
		return (NULL);
	while(*s1)
		*new++ = *s1++;
	while(*s2)
		*new++ = *s2++;
	*new = 0;
	free(s1);
	return (new);
}
