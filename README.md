*Este proyecto ha sido creado como parte del currículo de 42 por albelmon*

Get Next Line

Descripción
El objetivo de este proyecto es programar una función que devuelva una línea leída de un file descriptor. Get Next Line introduce el concepto de variables estáticas en C y requiere una gestión de memoria rigurosa. La función debe ser capaz de leer de manera eficiente, sin importar el tamaño del búfer (BUFFER_SIZE) ni el tamaño del archivo, manteniendo el estado de la lectura entre llamadas sucesivas.

Instrucciones
Compilación: cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
Ejecución: ./a.out
Main de prueba:
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int     fd;
	char    *gnl;

	fd = open("larga.txt", O_RDONLY);
	//fd = 42;
	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		printf("%s", gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
	close(fd);
}
Generar una línea de más de 2000 carácteres: python3 -c "print('HOLA' * 625)" > prueba.txt

Recursos
P2P. Tutoriales de YT sobre variables estáticas. He utilizado IA para solucionar dudas concretas, revisión general del código y creación de main exhaustivo.

Estructura de datos
El proyecto está organizado en varios archivos para separar responsabilidades y mantener el código limpio:
get_next_line_utils.c → Funciones auxiliares: ft_strlen, ft_strjoin, ft_memcpy, ft_strchr.
get_next_line.c → ft_extract_line: Limpia la línea almacenada en rest. ft_save_rest: Almacena en newrest la parte perteneciente a la siguiente línea que estaba almacenada en rest. ft_read_to_rest: Almacena en rest el contenido de una línea y posiblemente parte de la siguiente. get_next_line: Hub de llamadas al resto de funciones.

Algoritmo Seleccionado y Justificación
El algoritmo se basa en el uso de una variable estática que actúa como un acumulador de datos persistente entre llamadas.
Lectura acumulativa: Se utiliza ft_read_to_rest para leer bloques de tamaño BUFFER_SIZE y concatenarlos en la variable estática hasta
que se encuentra un salto de línea (\n) o se llega al final del archivo (EOF).
Optimización de Memoria y Tiempo: ft_memcpy dentro de ft_strjoin. Esta implementación mejora la eficiencia al copiar bloques de
memoria completos en lugar de procesar carácter por carácter.
