/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusluiz- <gusluiz-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:57:49 by gusluiz-          #+#    #+#             */
/*   Updated: 2022/08/10 18:19:57 by gusluiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*backup(char *backup_buffer)
{
	char	*line;
	size_t	counter;
	int		len;

	counter = 0;
	while (!backup_buffer[counter] && backup_buffer[counter] != '\n')
		counter++;
	if (!backup_buffer[counter])
	{
		free (backup_buffer);
		backup_buffer = NULL;
		return (NULL);
	}
	len = ft_strlen(backup_buffer) - (counter + 1);
	line = malloc(len * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, backup_buffer + (counter + 1), len + 2);
	free(backup_buffer);
	backup_buffer = NULL;
	return (line);
}

char	*get_line(char *backup_buffer)
{
	char	*line;
	size_t	counter;

	counter = 0;
	if (!backup_buffer[counter])
		return (NULL);
	while (backup_buffer[counter] != '\n')
		counter++;
	line = malloc((counter + 2) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, backup_buffer, (counter + 2));
	return (line);
}

char	*reader(int fd, char **buffer, char	*backup_buffer)
{
	char	*tmp;
	size_t	read_return;

	read_return = 1;
	while (!ft_strchr(backup_buffer, '\n') && read_return != 0)
	{
		read_return = read(fd, *buffer, BUFFER_SIZE);
		if (read_return < 0)
		{
			free(*buffer);
			*buffer = NULL;
			free(backup);
			return (NULL);
		}
		(*buffer)[read_return] = '\0';
		tmp = backup_buffer;
		backup_buffer = ft_strjoin(backup_buffer, *buffer);
		free(tmp);
		tmp = NULL;
	}
	free(*buffer);
	*buffer = NULL;
	return (backup_buffer);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*backup_buf = NULL;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!backup_buf)
		backup_buf = ft_strdup("");
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	backup_buf = reader(fd, &buf, backup_buf);
	if (!backup_buf)
		return (NULL);
	line = get_line(backup_buf);
	backup_buf = backup(backup_buf);
	return (line);
}


/* 

 ** ** ** ** ** ** TEST ** ** ** ** ** **

int main(void)
{
	int	fd = open("file.html", O_RDONLY);
	// char *line = get_next_line(fd);
	// printf("%s\n", line);
	int counter = 0;
	int lines_to_print = 2;
	char *gnl;
	while (counter <= lines_to_print)
	{
		gnl = get_next_line(2);
		printf("PRINT %d\t:\t%s", ++counter, gnl);
		free(gnl);
	}
	return (0);
}
 */