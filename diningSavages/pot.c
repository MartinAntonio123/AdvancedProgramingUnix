#include "header.h"

int main(int argc, char* argv[]) {
	int size = 0, semid;
	key_t key;

	if (argc != 1) {
		printf("usage: %s \n", argv[0]);
		return -1;
	}

	if ( (key = ftok("/dev/null", 65)) == (key_t) -1 ) {
		perror(argv[0]);
		return -1;
	}

	if ( (semid = semget(key, 3, 0666 | IPC_CREAT))  < 0 ) {
		perror(argv[0]);
		return -1;
	}

	semctl(semid, CSLEEP, SETVAL, 0);
	semctl(semid, MUTEXSERVE, SETVAL, 1);
	semctl(semid, PORTIONS, SETVAL, SERVINGS);
  printf("pot filled with 3 PORTIONS\n");

	return 0;
}
