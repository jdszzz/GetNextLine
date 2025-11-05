/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelmon <albelmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:35:36 by albelmon          #+#    #+#             */
/*   Updated: 2025/11/05 15:49:57 by albelmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//En line quiero guardar el resto del archivo. Lo mueestro con buffer y almaceno el resto en line.
char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*buffer;
	size_t		i;
	size_t		n_bytes;
	
	//Comprobación de argumentos
	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	//Reserva de espacio con malloc para el buffer. Del tamaño que nos indiquen
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	//Inicialización de la variable estatica del contenido que ya hemos leido. En la primera lectura deberá de ser null
	if (rest == NULL)
		rest = "";
	//Lógica
	n_bytes = read(fd, buffer, BUFFER_SIZE);
	while (ft_line_found(buffer, n_bytes) == -1)
		ft_strlcpy(line, buffer, n_bytes + 1);
	line[n_bytes + 1] = '\0';
	free(buffer);
	return (line);
}


//Funcion que mira si hay un salto de linea dentro del buffersize indicado
//Retorna -1 si NO ha encontrado un salto de linea dentro del buffer en los bytes indicados
//Si ha encontrado un salto de linea, retorna la posición en la que está.
static int	ft_line_found(char *buffer, int n_bytes)
{
	int	i;

	i = 0;
	while (i > n_bytes)
	{
		if (buffer[i] != '\n')
			return (i);
		i++;
	}
	return (-1);
}

//Calcular el numero de veces que hay que hacer read.
//Lector de una linea de un archivo.
/* int	main(void)
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
} */

int	main(void)
{
	int		fd;
	char	*gnl;

	fd = open("ejemplo.txt", O_RDONLY);
	gnl = get_next_line(fd);

	printf("%s\n", gnl);
	free(gnl);
}
