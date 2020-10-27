# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
/****************************************
 * Martin Antonio Vivanco Palacios A01701167
 * Proyecto 1 programacion avanzada
 * log
 ****************************************/
 void createlog(char * dir, char * filename){
   char filenameN[PATH_MAX + NAME_MAX + 1];
   FILE *filenew;
   sprintf(filenameN, "%s/%s.log", dir, filename);
   filenew = fopen(filenameN, "w");
   printf("%s created\n", filenameN);
   fclose(filenew);
 }
 void rotation(char * dir, char * filename, int number){
   char filenameO[PATH_MAX + NAME_MAX + 1];
   char filenameD[PATH_MAX + NAME_MAX + 1];
   if(number == 0){
     sprintf(filenameO, "%s/%s.log", dir, filename);
   }
   else{
     sprintf(filenameO, "%s/%s.%i", dir, filename, number);
   }
   sprintf(filenameD, "%s/%s.%i", dir, filename, number+1);
   int boolen;
   boolen = rename(filenameO, filenameD);
   if(!boolen){
     printf("%s renamed to %s \n", filenameO, filenameD);
   }
   else{
     printf("error ocurred\n");
   }
 }
int main ( int argc , char * argv []) {

  int number, timeout, ccreated = 0;
  char *dir, *file;
  dir = argv[1];
  file = argv[2];
  sscanf(argv[3], "%i", &number);
  printf("number: %d\n", number);
  sscanf(argv[4], "%i", &timeout);
  printf("number: %d\n", timeout);

  if(argc != 5)
  {
    printf("usage: $rotation working_directory log_filename max_number_of_files timeout \n");
    return -1;
  }
  if(timeout < 1)
  {
    printf("usage: timeout must be greater than 0 \n");
    return -1;
  }
  if(number < 1)
  {
    printf("usage: number must be greater than 0 \n");
    return -1;
  }
  char filename[PATH_MAX + NAME_MAX + 1];
  sprintf(filename, "%s/%s.log", dir, file);
  if(access(filename, F_OK) == -1){
    printf("usage: file must exists \n");
    return -1;
  }
  if(access(filename, R_OK|W_OK) == -1){
    printf("usage: file must have rw permisions \n");
    return -1;
  }


  while (1) {
    for (int i = ccreated; i >= 0; i--) {
      rotation(dir, file, i);
    }
    createlog(dir, file);
    if(ccreated < (number-1)){
      ccreated ++;
    }
    printf("\n");
    printf("\n");
    sleep(timeout);
  }

  return 0;
}
