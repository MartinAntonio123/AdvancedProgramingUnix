#include "header.h"

void a_savage(char* program) {
	int semid, i = 1;
	key_t key;

	if ( (key = ftok("/dev/null", 65)) == (key_t) -1 ) {
		perror(program);
		exit(-1);
	}

	if ( (semid = semget(key, 3, 0666))  < 0 ) { //identificador del semaforo, numero de semaforos asociados, y otra cosa
		perror(program);
		exit(-1);
	}
  srand( getpid() );
  while(1){
    printf("Savage %i trying to get the spoon.\n", getpid());
  	mutex_wait(semid, MUTEXSERVE);
  	printf("Savage %i get in the spoon, pot with %i servings\n", getpid(), semctl(semid, PORTIONS, GETVAL, 0));
    if (semctl(semid, PORTIONS, GETVAL, 0) == 0) {
      printf("Pot empty, waking cooker\n");
      mutex_signal(semid, CSLEEP);
    }
  	sem_wait(semid, PORTIONS, 1);
    printf("Savage %i get food\n", getpid());
  	mutex_signal(semid, MUTEXSERVE);
    sleep((rand() % 3) + 1);
  }
	exit(0);
}

int main(int argc, char* argv[]) {
	int amount = 0, semid, i, pid;
	key_t key;

	if (argc != 2) {
		printf("usage: %s amount\n", argv[0]);
		return -1;
	}

	amount = atoi(argv[1]);
	if (amount < 1) {
		printf("%s: The amount must be a positive number greater than zero.\n", argv[0]);
		return -1;
	}

	for (i = 0; i < amount; i++) {
		if ( (pid = fork()) < 0 ) {
			perror("fork");
			return -1;
		} else if (pid == 0) {
			a_savage(argv[0]);
		} else {
		}
	}
	return 0;
}
