#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
/****************************************
 * Martin Antonio Vivanco Palacios A01701167
 * Examen Final Programacion Avanzada
 * Encription file
 ****************************************/

int main(int argc, char* argv[]){

	int fd_in, fd_out; //utilizar los file descriptors para leer y escribir los archivos

	if (argc != 3){ // verificar numero de parametros
		printf("usage: ./decrypt origen destination\n");
		return -1;
	}
	if(access(argv[1], F_OK) == -1){
    printf("usage: origin file must exist\n");
    return -1;
  }
	if ((fd_in = open(argv[1], O_RDONLY)) < 0){ // abrir primer archivo modo lectura
		perror(argv[0]);
		return -1;
	}
	if ((fd_out = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0666)) < 0){ // abrir segundo archivo modo escritura
		perror(argv[0]);
		return -1;
	}

	char buffer;
	ssize_t nbytes;

	while((nbytes = read(fd_in, &buffer, sizeof(char))) != 0){
    buffer = (buffer & 0xF0) >> 4 | (buffer & 0x0F) << 4;
		write(fd_out, &buffer, nbytes);
	}
	close(fd_in);
	close(fd_out);
	return 0;
}
