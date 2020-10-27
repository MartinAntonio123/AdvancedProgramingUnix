#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
/****************************************
 * Martin Antonio Vivanco Palacios A01701167
 * Examen 1 programacion avanzada
 * min max recursive
 ****************************************/
double get_info(char *name, char *directory, char* program) {
	char filename[PATH_MAX + NAME_MAX + 1];
	sprintf(filename, "%s/%s", directory, name);
	int fd_in; 

	if ((fd_in = open(filename, O_RDONLY)) < 0){ // abrir primer archivo modo lectura
		perror(program);
		return -1;
	}

	off_t length;
	length = lseek(fd_in, 0, SEEK_END);
	lseek(fd_in, 0, SEEK_SET);
	close(fd_in);
	return length;
}
double funtotal(char *directory, char *program){
	DIR* dir;
	struct dirent* direntry;
	struct stat info;
	char filename[PATH_MAX + NAME_MAX + 1];
	double total = 0, aux;
	
	if ( (dir = opendir(directory)) == NULL ) {
		perror(program);
		exit(-1);
	}
	while ( (direntry = readdir(dir)) != NULL ) {
		if (strcmp(direntry->d_name, ".") != 0 && strcmp(direntry->d_name, "..") != 0) {
			sprintf(filename, "%s/%s", directory, direntry->d_name);
			lstat(filename, &info);
			if (S_ISDIR(info.st_mode)) {
				aux = funtotal(filename, program);
				total = total + aux;
			}
			else{
				aux = get_info(direntry->d_name, directory, program);
				total = total + aux;
			}
		}
	}
	return total;
	
}
void list(char *directory, char *program){
	DIR* dir;
	struct dirent* direntry;
	struct stat info;
	char filename[PATH_MAX + NAME_MAX + 1];
	double minimo = 0, maximo = 0, total = 0, aux, i = 1;
	
	if ( (dir = opendir(directory)) == NULL ) {
		perror(program);
		exit(-1);
	}
	while ( (direntry = readdir(dir)) != NULL ) {
		if (strcmp(direntry->d_name, ".") != 0 && strcmp(direntry->d_name, "..") != 0) {
			sprintf(filename, "%s/%s", directory, direntry->d_name);
			lstat(filename, &info);
			if (!S_ISDIR(info.st_mode)) {
				aux = get_info(direntry->d_name, directory, program);
				if(i){
					minimo = aux;
					i = 0;
				}
				if(aux > maximo){
					maximo = aux;
				}
				if(aux < minimo){
					minimo = aux;
				}
			}
		}
	}
	printf("\n");
	printf("Directory: %s\n", directory);
	printf("Max size: %.0f", maximo);
	printf("  Min size: %.0f\n", minimo);
	
}
int main(int argc, char* argv[]){

	if (argc != 2)
	{
		printf("usage: total directory\n");
		return -1;
	}
	
	char *directory;
	directory = argv[1];
	printf("%s\n", directory);
	list(directory, argv[0]);
	printf("Total space ocupied: %.0f\n\n", funtotal(directory, argv[0]));
	return 0;

}