/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:57:40 by dgomez-a          #+#    #+#             */
/*   Updated: 2024/08/16 20:17:19 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *saved)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!saved[i])
		return (NULL);
	while (saved[i] && saved[i] != '\n')
		i++;
	if (saved[i] == '\n')
		line = ft_substr(saved, 0, i + 1);
	else
		line = ft_substr(saved, 0, i);
	return (line);
}

static char	*save_remaining(char *saved)
{
	size_t	i;
	char	*new_saved;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	new_saved = ft_strdup(saved + i + 1);
	free(saved);
	return (new_saved);
}

static int	read_and_update(int fd, char **saved, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (-1);
	buffer[bytes_read] = '\0';
	if (*saved == NULL)
		*saved = ft_strdup(buffer);
	else
	{
		temp = ft_strjoin(*saved, buffer);
		free(*saved);
		*saved = temp;
	}
	if (*saved == NULL)
		return (-1);
	return (bytes_read);
}

static char	*read_and_store(int fd, char *saved)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(saved, '\n') && bytes_read > 0)
	{
		bytes_read = read_and_update(fd, &saved, buffer);
		if (bytes_read == -1)
		{
			free(buffer);
			free(saved);
			return (NULL);
		}
	}
	free(buffer);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = read_and_store(fd, saved);
	if (!saved)
		return (NULL);
	line = get_line(saved);
	saved = save_remaining(saved);
	return (line);
}