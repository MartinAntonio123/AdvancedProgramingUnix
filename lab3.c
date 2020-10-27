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
/****************************************
 * Martin Antonio Vivanco Palacios A01701167
 * Lab 3 programacion avanzada
 * ls recursive
 ****************************************/
void get_info(char name, char *directory, char program) {
	struct stat info;
	time_t rawtime;
	struct tm* datetime;
	char date[13];
	char filename[PATH_MAX + NAME_MAX + 1];
	sprintf(filename, "%s/%s", directory, name);
	if (lstat(filename, &info) < 0) {
		perror(program);
		exit(-1);
	}
	printf("NAME: %s \n", name);
	printf("PATH: %s \n\n", directory);
	rawtime = info.st_mtime;
	datetime = localtime(&rawtime);
	strftime(date, 25, "%c", datetime);
	printf("LAST MODIFICATION: %s\n\n", date);
	rawtime = info.st_atime;
	datetime = localtime(&rawtime);
	strftime(date, 25, "%c", datetime);
	printf("LAST ACCESS: %s\n\n", date);
}
void list(char *str, char *directory, unsigned char recursivo, char *program){
	DIR* dir;
	struct dirent* direntry;
	struct stat info;
	char filename[PATH_MAX + NAME_MAX + 1];

	if ( (dir = opendir(directory)) == NULL ) {
		perror(program);
		exit(-1);
	}
	while ( (direntry = readdir(dir)) != NULL ) {
		if (strcmp(direntry->d_name, ".") != 0 && strcmp(direntry->d_name, "..") != 0) {
			if(strstr(direntry->d_name, str) != NULL){
				get_info(direntry->d_name, directory, program);
			}
		}
	}

	if (recursivo) {
		rewinddir(dir);
		while ( (direntry = readdir(dir)) != NULL ) {
			if (strcmp(direntry->d_name, ".") != 0 && strcmp(direntry->d_name, "..") != 0) {

				sprintf(filename, "%s/%s", directory, direntry->d_name);
				lstat(filename, &info);
				if (S_ISDIR(info.st_mode)) {
					list(str, filename, recursivo, program);
				}
			}
		}
	}
	printf("\n");
}

int main(int argc, char* argv[]){

	if ((argc != 4) && (argc != 3))
	{
		printf("usage: find string path [-r]\n");
		return -1;
	}
	unsigned char recursivo = 0;
	if (argc == 4)
	{
		if (strcmp(argv[3], "-r") != 0)
		{
			printf("usage: find string path2 [-r]\n");
			return -1;
		}
		recursivo = 1;
	}
	char *directory, *str;
	directory = argv[2];
	str = argv[1];
	list(str, directory, recursivo, argv[0]);
	return 0;

}
