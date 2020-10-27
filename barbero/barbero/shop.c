#include "header.h"

int main (int argc, char* argv[]) {

	if(argc!=2)
	{
		printf("Usage: barbershop chairs\n");
		return -1;
	}

	int semid;
  key_t key;
	int chairs = atoi(argv[1]);

	if( (key = ftok("/dev/null", 65)) == (key_t) - 1){
		perror(argv[0]);
		return -1;
	}
	if( (semid = semget(key, 4, 0666 | IPC_CREAT)) < 0 ){
		perror(argv[0]);
		return -1;
	}
	semctl(semid, SLEEPING, SETVAL, 0);
	semctl(semid, CUTTING, SETVAL, 0);
	semctl(semid, CHAIRS, SETVAL, chairs);
	semctl(semid, OCUPIED, SETVAL, 0);


	return 0;
}
