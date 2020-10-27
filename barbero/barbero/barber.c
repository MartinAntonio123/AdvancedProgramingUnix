#include "header.h"

int main(int argc, char* argv[]) {
	if(argc!=1)
	{
		printf("Usage: barber\n");
		return -1;
	}
	int semid;
  key_t key;

  if( (key = ftok("/dev/null", 65)) == (key_t) - 1){
    perror(argv[0]);
    return -1;
  }
  if( (semid = semget(key, 4, 0666 | IPC_CREAT)) < 0 ){
    perror(argv[0]);
    return -1;
  }

	while(1)
	{
		if (semctl(semid, OCUPIED, GETVAL, 0) == 0) {
			printf("barber sleep\n");
			sem_wait(semid, SLEEPING, 1);
		}
		else{
			sem_wait(semid, OCUPIED, 1);
			sem_signal(semid, CUTTING, 1);
			printf("barber start cutting hair\n");
			sleep(1);
			printf("barber finish cutting hair\n");
			
		}

	}
	return 0;
}
