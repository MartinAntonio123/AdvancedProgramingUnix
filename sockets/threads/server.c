#include "header.h"
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* serves_client(void *param) {
	int number_sent, number_guess;
	int guess, answer;
	int nsfd = *( (int*) param);

	srand(getpid());
	do {
		guess = 0;
		number_guess = (rand() % 100) + 1;
		printf("PID = %i <-> number to  guess = %i\n", getpid(), number_guess);
		while (!guess) {
			read(nsfd, &number_sent, sizeof(number_sent));
			if (number_sent < number_guess) {
				answer = SMALLER;
			} else if (number_sent > number_guess) {
				answer = BIGGER;
			} else {
				answer = EQUAL;
				guess = 1;
			}
			write(nsfd, &answer, sizeof(answer));
			pthread_mutex_lock(&mutex);
			FILE * file;
			file = fopen("log.txt","a");
			printf("mutex\n" );
			fprintf(file, "has adivinado %i\n", number_guess);
			fclose(file);
			pthread_mutex_unlock(&mutex);
		}
		read(nsfd, &answer, sizeof(answer));
	} while (answer == CONTINUE);
	close(nsfd);
}

void server(char* ip, int port, char* program) {
	int sfd, nsfd, pid;
	pthread_t thread_id;
	struct sockaddr_in server_info, client_info;

	if ( (sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
		perror(program);
		exit(-1);
	}

	server_info.sin_family = AF_INET;
	server_info.sin_addr.s_addr = inet_addr(ip);
	server_info.sin_port = htons(port);
	if ( bind(sfd, (struct sockaddr *) &server_info, sizeof(server_info)) < 0 ) {
		perror(program);
		exit(-1);
	}

	listen(sfd, 1);
	while (1) {
		int len = sizeof(client_info);
		if ( (nsfd = accept(sfd, (struct sockaddr *) &client_info, &len)) < 0 ) {
			perror(program);
			exit(-1);
		}

		pthread_create(&thread_id, NULL, serves_client, ((void *) &nsfd));
	}
}

int main(int argc, char* argv[]) {
	char ip[15];
	int port;

	strcpy(ip, DEFAULT_IP);
	port = DEFAULT_PORT;
	if (argc != 1) {
		printf("usage: %s\n", argv[0]);
		return -1;
	}

	server(ip, port, argv[0]);

	return 0;
}
