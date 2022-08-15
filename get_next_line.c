/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusluiz- <gusluiz-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:57:49 by gusluiz-          #+#    #+#             */
/*   Updated: 2022/08/15 23:41:49 by gusluiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_ptr(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

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
		free_ptr((void **)backup_buffer);
		return (NULL);
	}
	line = malloc((ft_strlen(backup_buffer) - len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	size = ft_strlen(backup_buffer) - len + 1;
	ft_strlcpy(line, backup_buffer + (len + 1), size);
	free_ptr((void **)backup_buffer);
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
	size_t	read_return;

	read_return = 1;
	while (!ft_strchr(backup_buffer, '\n') && read_return != 0)
	{
		read_return = read(fd, *buffer, BUFFER_SIZE);
		if (read_return < 0)
		{
			free_ptr((void **)buffer);
			free (backup);
			return (NULL);
		}
		(*buffer)[read_return] = '\0';
		tmp = backup_buffer;
		backup_buffer = ft_strjoin(tmp, *buffer);
		free_ptr((void **)tmp);
	}
	free_ptr((void **)buffer);
	return (backup_buffer);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*backup_buffer = NULL;

	if (fd < 0 || BUFFER_SIZE < 1)
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
// 	// ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** //
// 	//				TEST WITH MAIN FUNC					  //
// 	// ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** //

// 	// ********** Declare variables for the test **********
// 	char    *path;
//     char    *gnl_function;
//     int		pfd;
//     int		i;
// 	int		limit;

// 	// ****************** Assign values *******************
// 	#define LOCKFILE "./file.html" // Enter here the path to test file
// 	if ((pfd = open(LOCKFILE, O_RDONLY)) == -1)
// 	{
// 		printf("Cannot open %s. Please, check the specified path before running the test.\n", LOCKFILE);
// 		exit(1);
// 	}
// 	i = 0;
// 	limit = 2; // Enter here the limit of lines that will be printed

// 	// Loop to print the lines specified in the limit variable
//     while (i <= limit)
//     {
//         gnl_function = get_next_line(pfd);
//         printf("%dº LINE\t:\t\\***/ %s \\***/", i ++, gnl_function);
//         free(gnl_function);
//     }
// }
