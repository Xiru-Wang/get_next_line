/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:45:29 by xiwang            #+#    #+#             */
/*   Updated: 2023/07/11 18:13:10 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
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
	size_t	i;
	size_t	k;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = 0;
	}
	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new || !s2)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	k = 0;
	while (s2[k])
		new[i++] = s2[k++];
	new[i] = 0;
	free(s1);
	return (new);
}
