/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelmon <albelmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:34:27 by albelmon          #+#    #+#             */
/*   Updated: 2026/01/09 15:05:56 by albelmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_extract_line(char *rest)
{
	char	*line;
	int		i;

	i = 0;
	if (!rest[i])
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	line = malloc(i + (rest[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
	{
		line[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_save_rest(char *rest)
{
	char	*new_rest;
	int		i;
	int		j;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
		return (free(rest), NULL);
	new_rest = malloc(ft_strlen(rest) - i + 1);
	if (!new_rest)
		return (free(rest), NULL);
	i++;
	j = 0;
	while (rest[i])
		new_rest[j++] = rest[i++];
	new_rest[j] = '\0';
	free(rest);
	return (new_rest);
}

static char	*ft_read_to_rest(int fd, char *rest)
{
	char	*buf;
	char	*tmp;
	ssize_t	n_bytes;

	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (free(rest), NULL);
	n_bytes = 1;
	while (!ft_strchr(rest, '\n') && n_bytes != 0)
	{
		n_bytes = read(fd, buf, BUFFER_SIZE);
		if (n_bytes == -1)
			return (free(buf), free(rest), NULL);
		buf[n_bytes] = '\0';
		tmp = ft_strjoin(rest, buf);
		if (!tmp)
			return (free(buf), NULL);
		rest = tmp;
	}
	free(buf);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(rest), rest = NULL, NULL);
	rest = ft_read_to_rest(fd, rest);
	if (!rest)
		return (NULL);
	line = ft_extract_line(rest);
	if (!line)
		return (free(rest), rest = NULL, NULL);
	rest = ft_save_rest(rest);
	return (line);
}
