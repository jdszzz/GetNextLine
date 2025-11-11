/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelmon <albelmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:35:36 by albelmon          #+#    #+#             */
/*   Updated: 2025/11/11 18:16:20 by albelmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Funcion que mira si hay un salto de linea dentro del buffersize indicado
//Retorna -1 si NO ha encontrado un salto de linea dentro del buffer en los bytes indicados
//Si ha encontrado un salto de linea, retorna la posición en la que está.
static int	ft_line_found(char *buffer, int n_bytes)
{
	int	i;

	i = 0;
	while (i < n_bytes)
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*buffer;
	int			jump;
	size_t		n_bytes;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	//Es la forma terniaria
	line = rest ? ft_strdup(rest) : ft_strdup("");
	//De esto:
	if (rest)
		line = ft_strdup(rest);
	else
		line = ft_strdup("");
	free(rest);
	rest = NULL;
	while ((n_bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[n_bytes] = '\0';
		line = ft_strjoin(line, buffer);
		jump = ft_line_found(line, ft_strlen(line));
		if (jump >= 0)
		{
			rest = ft_strdup(line + jump + 1);
			line[jump + 1] = '\0';
			break;
		}
	}
	free(buffer);
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

//Calcular el numero de veces que hay que hacer read.
//Lector de una linea de un archivo.
int	main(void)
{
	int		fd;
	char	*gnl;

	fd = open("ejemplo.txt", O_RDONLY);
	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		printf("%s", gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
	close(fd);
}
