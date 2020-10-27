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
 int copiar(char *name, char *origin, char *destination, char *program) {

 	char filenameO[PATH_MAX + NAME_MAX + 1];
  char filenameD[PATH_MAX + NAME_MAX + 1];
  int lineas=61, numeros=625;
  FILE *fileorigin, *filedestination;
 	sprintf(filenameO, "%s/%s", origin, name);
 	sprintf(filenameD, "%s/%s", destination, name);
  fileorigin = fopen(filenameO, "r");
  filedestination = fopen(filenameD, "w");
 	printf("Origen: %s \n", filenameO);
 	printf("Destino: %s \n\n", filenameD);
  float buffer1, buffer2, min, max;
  float buffer[numeros];

  for (int i = 0; i < lineas; i++) {
    fscanf(fileorigin,"%f,%f", &buffer1, &buffer2);
    fprintf(filedestination, "%f,%f", buffer1, buffer2);

    for (int j = 0; j < numeros; j++) {
      fscanf(fileorigin,",%f", &buffer[j]);
      if(j == 0){
        min = buffer[j];
        max = buffer[j];
      }
      if(min > buffer[j]){
        min = buffer[j];
      }
      if(max < buffer[j]){
        max = buffer[j];
      }
    }
    for (int j = 0; j < numeros; j++) {
      fprintf(filedestination, ",%f", (buffer[j]-min)/(max-min));
    }
    fprintf(filedestination, "\n");
  }
}

 void explore(char *origin, char *destination, char * program){
  DIR* dir;
  struct dirent* direntry;
  struct stat info;
  char filename[PATH_MAX + NAME_MAX + 1];

  if ( (dir = opendir(origin)) == NULL ) {
  	perror(program);
  	exit(-1);
  }
  while ( (direntry = readdir(dir)) != NULL ) {
  	if (strcmp(direntry->d_name, ".") != 0 && strcmp(direntry->d_name, "..") != 0) {
  		copiar(direntry->d_name, origin, destination, program);
  	}
  }
}
 int main(int argc, char* argv[]){

 	if(argc != 3)
 	{
 		printf("usage: normalize origin_directory destination_directory \n");
 		return -1;
 	}
 	char *origin, *destination;
 	destination = argv[2];
  origin = argv[1];
 	explore(origin, destination, argv[0]);
 	return 0;
 }
