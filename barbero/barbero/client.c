#include "header.h"

int main(int argc, char* argv[]) {

	if(argc!=2){
		printf("Usage: client time\n");
		return -1;
	}
	int timee = atoi(argv[1]);

	if(timee < 1){
		printf("time must be a positive integer\n");
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
	while(1){
		printf("client %i get in the shop\n", getpid());

		if (semctl(semid, CHAIRS, GETVAL, 0) != 0) {
			if (semctl(semid, CHAIRS, OCUPIED, 0) == 0) {
				printf("client %i waking barber \n", getpid());
				sem_signal(semid, SLEEPING, 1);
			}
			sem_wait(semid, CHAIRS, 1);
			sem_signal(semid, OCUPIED, 1);
			printf("client %i sit\n", getpid());
			sem_wait(semid, CUTTING, 1);
			printf("client %i being atended\n", getpid());
			sem_signal(semid, CHAIRS, 1);
			printf("client %i out the shop\n", getpid());
		}
		else{
			printf("too many clients, client %i out the shop\n", getpid());
		}
		sleep(timee);
	}
	return 0;
}
