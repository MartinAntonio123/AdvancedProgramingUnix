# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
/****************************************
 * Martin Antonio Vivanco Palacios A01701167
 * Lab 3 programacion avanzada
 * arbol de procesos
 ****************************************/

# define SLEEP 1

int n_process (int count, int numb) {
  pid_t pid = getpid ();
  for (int i = 0; i < count; i++) {
    printf("  ");
  }
  printf("Nivel %d: ", count );
  printf ("PID = %i PPID = %i \n" , getpid () , getppid ());
  if(count == numb){
    sleep ( SLEEP );
  }
  if (count < numb) {
    for (int i = 0; i <= count; i++) {
      pid = fork();
      if ( pid == 0){
        n_process (count + 1, numb) ;
        return 0;
      }
      else { /* parent process */
        wait ( NULL ) ;
      }
    }
  }
  return 0 ;
}

int main ( int argc , char * argv []) {

  int number, count = 0;
  float validacion;
  sscanf(argv[1], "%i", &number);
  printf("number: %d\n", number);
  sscanf(argv[1], "%f", &validacion);
  //printf("%f\n", validacion);

  if(argc != 2)
 	{
 		printf("usage: descending integer \n");
 		return -1;
 	}
  if(((validacion - number) != 0) || (number < 1))
  {
    printf("usage: descending integer parameter must be a positive integer \n");
    return -1;
  }


  n_process(count, number);
  return 0;
}
