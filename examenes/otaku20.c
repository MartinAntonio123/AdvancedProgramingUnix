#include "header.h"

int main(int argc, char* argv[]) {
	int semid;
	key_t key;

	if (argc != 1) {
		printf("usage: %s \n", argv[0]);
		return -1;
	}

	if ( (key = ftok("/dev/null", 65)) == (key_t) -1 ) {
		perror(argv[0]);
		exit(-1);
	}

	if ( (semid = semget(key, 4, 0666))  < 0 ) {
		perror(argv[0]);
		exit(-1);
	}
	int a = 0, b = 0, max = 10;
	while (1) {
		a = semctl(semid, CINCUENTA, GETVAL, 0);
		b = semctl(semid, CIEN, GETVAL, 0);
		if((a == 1) && (b == 1)){
			sem_wait(semid, CINCUENTA, 1);
			printf("Otaku20 = %i took 50.\n", getpid());
			sem_wait(semid, CIEN, 1);
			printf("Otaku20 = %i took 100.\n", getpid());
			printf("Otaku20 = %i buy poki.\n\n", getpid());
			sleep(2);
			mutex_signal(semid, BMUTEX);
		}
	}

	return 0;
}
