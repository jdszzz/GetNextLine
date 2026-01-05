/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelmon <albelmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:11:09 by albelmon          #+#    #+#             */
/*   Updated: 2026/01/05 17:13:13 by albelmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Busca '\n' en los primeros n_bytes de buffer, devuelve posición o -1
static int	ft_line_found(char *buffer, ssize_t n_bytes)
{
	ssize_t	i;

	i = 0;
	while (i < n_bytes)
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_extract_rest(char *line, char **rest, int jump)
{
	*rest = ft_strdup(line + jump + 1);
	if (!*rest)
	{
		free(line);
		return (NULL);
	}
	line[jump + 1] = '\0';
	return (line);
}

static char	*ft_process_buffer(char *line, char *buffer, char **rest)
{
	int	jump;

	line = ft_strjoin(line, buffer);
	if (!line)
		return (NULL);
	jump = ft_line_found(line, ft_strlen(line));
	if (jump >= 0)
		return (ft_extract_rest(line, rest, jump));
	return (line);
}

static char	*ft_read_until_newline(int fd, char *line, char **rest)
{
	ssize_t	n_bytes;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	n_bytes = 1;
	while (n_bytes > 0 && !(*rest))
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes == -1)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		buffer[n_bytes] = '\0';
		line = ft_process_buffer(line, buffer, rest);
		if (!line)
			break ;
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rest)
		line = ft_strdup(rest);
	else
		line = ft_strdup("");
	free(rest);
	rest = NULL;
	line = ft_read_until_newline(fd, line, &rest);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
