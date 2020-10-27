#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
/****************************************
 * Martin Antonio Vivanco Palacios A01701167
 * Lab 2 programacion avanzada
 * Encription file
 ****************************************/

int main(int argc, char* argv[]){

	int fd_in, fd_out; //utilizar los file descriptors para leer y escribir los archivos

	printf("argc: %d\n", argc );
	for (int i = 0; i < (int)argc; ++i)
	{
		printf("%s\n",argv[i] );
	}

	if (argc != 4){ // verificar numero de parametros
		printf("usage: cifrado numero origen destino\n");
		return -1;
	}
	if (*argv[1] < 1){ // verificar que el shift sea un numero positivo
		printf("the first number must be a positive integer\n");
		return -1;
	}
	if ((fd_in = open(argv[2], O_RDONLY)) < 0){ // abrir primer archivo modo lectura
		perror(argv[0]);
		return -1;
	}
	if ((fd_out = open(argv[3], O_WRONLY | O_TRUNC | O_CREAT, 0666)) < 0){ // abrir segundo archivo modo escritura
		perror(argv[0]);
		return -1;
	}

	char buffer[128]; // crear buffer de 128 bits
	ssize_t nbytes;
	char bufferAux[128];

	int n ;
	sscanf(argv[1], "%d", &n);


	while((nbytes = read(fd_in, buffer, sizeof(buffer))) != 0){
		if(0)//buffer[127] == '\0')
		{
			write(fd_out, buffer, nbytes);
		}
		else
		{
			for (int i = 0; i < (128-n); ++i)
			{
				bufferAux[i] = buffer[i+n];
			}
			for (int i = (128-n); i < 128; ++i)
			{
				bufferAux[i] = buffer[i -(128-n)];
			}
			bufferAux[128] = buffer[128];
			write(fd_out, bufferAux, nbytes);
		}
	}


	close(fd_in);
	close(fd_out);
	return 0;
}
