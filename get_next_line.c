/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelmon <albelmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:35:36 by albelmon          #+#    #+#             */
/*   Updated: 2025/11/04 14:48:20 by albelmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//En line quiero guardar el resto del archivo. Lo mueestro con buffer y almaceno el resto en line.
char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static int	i;
	
	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = -1;
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	read(fd, buffer, BUFFER_SIZE);
	while (buffer[++i] != '\n')
		line[i] = buffer[i];
	line[i] = '\n';
	line[++i] = '\0';
	free(buffer);
	return (line);
}

//Calcular el numero de veces que hay que hacer read.
//Lector de una linea de un archivo.

int	main(void)
{
	int		fd;
	char	*gnl;
	int		i = 0;

	fd = open("ejemplo.txt", O_RDONLY);
	gnl = get_next_line(fd);
	while (i < 3)
	{
		printf("%s\n", gnl);
		gnl = get_next_line(fd);
		free(gnl);
		i++;
	}
}
