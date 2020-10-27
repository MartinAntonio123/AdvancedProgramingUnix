# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
/****************************************
 * Martin Antonio Vivanco Palacios A01701167
 * Lab 6 programacion avanzada
 * senales en procesos
 ****************************************/
 int count = 0, available = 1;

 void sig_handler(int signum) {
   if (signum == SIGUSR1) {
     if (available) {
       available = 0;
       printf("SIGUSR1: SIGUSR2 is ignored\n");
     }
     else if (!available) {
       available = 1;
       printf("SIGUSR1: SIGUSR2 is accepted\n");
     }
   }
   if (signum == SIGUSR2) {
     if (available) {
       count ++;
       printf("SIGUSR2: increment count");
       printf(" = %d\n", count );
     }
     else if (!available) {
       printf("SIGUSR2: is ignored\n");
     }
   }
 }

 int main ( int argc , char * argv []) {

   if(argc > 2)
  	{
  		printf("usage: signaling [n] \n");
  		return -1;
  	}
    int number = 10;
    if(argc == 2)
   	{
      float validacion;
      sscanf(argv[1], "%i", &number);
      //printf("number: %d\n", number);
      sscanf(argv[1], "%f", &validacion);
      //printf("%f\n", validacion);
      if(((validacion - number) != 0) || (number < 1))
      {
        printf("usage: signaling [n] parameter must be a positive integer \n");
        return -1;
      }
   	}
    printf("number: %d\n", number);
    printf ("PID = %i\n" , getpid ());
    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);
    while (count < number) {

    }
    printf("Count equals number\n");
    printf("Exiting...\n");
    return 0;
 }
