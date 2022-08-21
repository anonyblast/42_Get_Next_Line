/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusluiz- <gusluiz-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:57:49 by gusluiz-          #+#    #+#             */
/*   Updated: 2022/08/21 17:33:29 by gusluiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*backup(char *backup_buffer)
{
	char	*line;
	size_t	len;
	size_t	size;

	len = 0;
	while (backup_buffer[len] && backup_buffer[len] != '\n')
		len++;
	if (!backup_buffer[len])
	{
		free (backup_buffer);
		backup_buffer = NULL;
		return (NULL);
	}
	line = malloc((ft_strlen(backup_buffer) - len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	size = ft_strlen(backup_buffer) - len + 1;
	ft_strlcpy(line, backup_buffer + (len + 1), size);
	free (backup_buffer);
	backup_buffer = NULL;
	return (line);
}

static char	*get_line(char *backup_buffer)
{
	char	*line;
	size_t	len;

	len = 0;
	if (!backup_buffer[len])
		return (NULL);
	while (backup_buffer[len] && backup_buffer[len] != '\n')
		len++;
	line = malloc((len + 2) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, backup_buffer, (len + 2));
	return (line);
}

static char	*reader(int fd, char **buffer, char	*backup_buffer)
{
	char	*tmp;
	int		read_return;

	read_return = 1;
	while (!ft_strchr(backup_buffer, '\n') && read_return != 0)
	{
		read_return = read(fd, *buffer, BUFFER_SIZE);
		if (read_return < 0)
		{
			free (*buffer);
			*buffer = NULL;
			free (backup_buffer);
			return (NULL);
		}
		(*buffer)[read_return] = '\0';
		tmp = backup_buffer;
		backup_buffer = ft_strjoin(tmp, *buffer);
		free (tmp);
		tmp = NULL;
	}
	free (*buffer);
	*buffer = NULL;
	return (backup_buffer);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*backup_buffer = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!backup_buffer)
		backup_buffer = ft_strdup("");
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	backup_buffer = reader(fd, &buffer, backup_buffer);
	if (!backup_buffer)
		return (NULL);
	line = get_line(backup_buffer);
	backup_buffer = backup(backup_buffer);
	return (line);
}

// int main(void)
// {
// 	int fd = open("./file.html", O_RDONLY);
// 	char *line = "";
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
