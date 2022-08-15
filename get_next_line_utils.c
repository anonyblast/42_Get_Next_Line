/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusluiz- <gusluiz-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 22:16:20 by gusluiz-          #+#    #+#             */
/*   Updated: 2022/08/14 00:43:36 by gusluiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == '\0' && c != '\0')
		return (0);
	return ((char *)s);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s) + 1;
	dup = (char *)malloc(len + sizeof(char));
	if (!dup)
	{
		free (dup);
		return (NULL);
	}
	ft_strlcpy(dup, s, len);
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*aux;
	size_t	s1_length;
	size_t	s2_length;

	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	aux = (char *) malloc((s1_length + s2_length) + 1 * sizeof(char));
	if (!aux)
		return (NULL);
	ft_strlcpy(aux, s1, s1_length + 1);
	ft_strlcpy(aux + s1_length, s2, s2_length + 1);
	return (aux);
}
