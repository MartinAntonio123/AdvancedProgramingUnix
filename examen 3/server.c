#include "header.h"
#include <string.h>

pthread_mutex_t mutexlog = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t empty = PTHREAD_MUTEX_INITIALIZER;
int vcompartida = 0;
int escritores = 0;
int lectores = 0;

char * log;

void* serves_client(void *param) {
	int newnumber, request;
	int nsfd = *( (int*) param);

	do {
		read(nsfd, &request, sizeof(request));
		printf("request = %i \n", request);
		int aux = vcompartida;
		if(request == 101){
			write(nsfd, &vcompartida, sizeof(vcompartida));
		}
		if(request == 201){
			read(nsfd, &newnumber, sizeof(newnumber));
			printf("new number = %i\n", newnumber);
			pthread_mutex_lock(&empty);
			vcompartida = newnumber;
			pthread_mutex_unlock(&empty);
		}
		if(request == 101 || request == 201){
			pthread_mutex_lock(&mutexlog);
			FILE * file;
			file = fopen(log,"a");
			time_t t;
		  struct tm *tm;
		  char fechayhora[100];
		  t = time(NULL);
		  tm = localtime(&t);
		  strftime(fechayhora, 100, "%d/%m/%Y", tm);
			fprintf(file, "date: %s anterior: %i nuevo: %i\n",fechayhora, aux, vcompartida);
			fclose(file);
			pthread_mutex_unlock(&mutexlog);
		}
		if(request == 301){
			pthread_mutex_lock(&mutexlog);
			FILE * file;
			file = fopen(log,"a");
			time_t t;
		  struct tm *tm;
		  char fechayhora[100];
		  t = time(NULL);
		  tm = localtime(&t);
		  strftime(fechayhora, 100, "%d/%m/%Y", tm);
			fprintf(file, "date: %s conexion cerrada\n",fechayhora);
			fclose(file);
			pthread_mutex_unlock(&mutexlog);
		}

	} while (request == 101 || request == 201);
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
	if (argc != 4) {
		printf("usage: %s ip port log\n", argv[0]);
		return -1;
	}
	strcpy(ip, argv[1]);
	port = atoi(argv[2]);
	log = argv[3];
	printf("%s\n", log );
	server(ip, port, argv[0]);
	return 0;
}
