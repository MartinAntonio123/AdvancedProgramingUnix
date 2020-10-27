#include "header.h"

int main(int argc, char* argv[]) {
	int semid;
	key_t key;

	if (argc != 1) {
		printf("usage: %s\n", argv[0]);
		return -1;
	}

	if ( (key = ftok("/dev/null", 65)) == (key_t) -1 ) {
		perror(argv[0]);
		return -1;
	}

	if ( (semid = semget(key, 4, 0666 | IPC_CREAT))  < 0 ) {
		perror(argv[0]);
		return -1;
	}

	semctl(semid, BMUTEX, SETVAL, 1);
	semctl(semid, VEINTE, SETVAL, 0);
	semctl(semid, CINCUENTA, SETVAL, 0);
	semctl(semid, CIEN, SETVAL, 0);

	srand( getpid() );
	int i = 0, j = 0, max = 10;
	while (1) {
		mutex_wait(semid, BMUTEX);
		while (j == i) {
			i = (rand() % 3) + 1;
			j = (rand() % 3) + 1;
			printf("%i %i\n", i,j);
		}
		sem_signal(semid, i, 1);
		sem_signal(semid, j, 1);
		printf("Benji = %i put %i 20s, %i 50s, %i 100\n", getpid(), semctl(semid, VEINTE, GETVAL, 0), semctl(semid, CINCUENTA, GETVAL, 0), semctl(semid, CIEN, GETVAL, 0));
		i =0;
		j=0;
	}
	return 0;
}
