#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "DatosMemCompartida.h"

int main(int argc, char **argv)
{
	// 1. Puntero a DatosMemCompartida
	DatosMemCompartida *pMemC;

	// 2. Abrir el fichero creado por el tenis y proyectarlo en memoria
	int fd = open("/tmp/datosBot.txt", O_RDWR);
	if (fd < 0) {
		perror("No puede abrirse el fichero (esta el tenis en ejecucion?)");
		return 1;
	}
	pMemC = (DatosMemCompartida *) mmap(NULL, sizeof(DatosMemCompartida),
	                                    PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	// 3. Cerrar el descriptor de fichero
	close(fd);
	if (pMemC == MAP_FAILED) {
		perror("Error en la proyeccion del fichero");
		return 1;
	}

	// 5. Bucle infinito: decide la accion cada 25 ms
	while (1) {
		usleep(25000);
		float centro = (pMemC->raqueta1.y1 + pMemC->raqueta1.y2) / 2;

		if (pMemC->esfera.centro.y > centro)
			pMemC->accion = 1;
		else if (pMemC->esfera.centro.y < centro)
			pMemC->accion = -1;
		else
			pMemC->accion = 0;
	}
	return 0;
}
