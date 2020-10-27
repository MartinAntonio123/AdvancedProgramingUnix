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

	if ( (semid = semget(key, 3, 0666))  < 0 ) {
		perror(argv[0]);
		exit(-1);
	}
	while (1) {
		printf("Cooker sleeping\n");
		mutex_wait(semid, CSLEEP);
		printf("Cooker awake\n");
    sleep(1);
    printf("Cooker preparing food\n");
    sleep(1);
    printf("Food ready\n");
    sem_signal(semid, PORTIONS, SERVINGS);
		printf("Cooker back to sleep\n");
	}
	return 0;
}
