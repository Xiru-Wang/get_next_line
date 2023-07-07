/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:40:29 by xiwang            #+#    #+#             */
/*   Updated: 2023/07/07 18:28:23 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
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
//return (NULL)

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
