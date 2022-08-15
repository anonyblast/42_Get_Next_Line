/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusluiz- <gusluiz-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:55:58 by gusluiz-          #+#    #+#             */
/*   Updated: 2022/08/15 23:43:38 by gusluiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// # define BUFFER_SIZE 10

# include <stdlib.h>
# include <fcntl.h> // TIRE ESSA IMPORTAÇÃO DAQUI
# include <stdio.h> // TIRE ESSA IMPORTAÇÃO DAQUI
# include <unistd.h>

char	*get_next_line(int fd);

// Import functions
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);

#endif