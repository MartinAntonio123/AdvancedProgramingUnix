#ifndef SEMAFOROS_H
#define SEMAFOROS_H
/*
Martin Antonio Vivanco Palacios
Programacion avanzada
Problema del barbero
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define	CHAIRS 0
#define CUTTING	1
#define SLEEPING 2
#define	OCUPIED 3


int sem_wait(int semid, int num, int valor) {
	struct sembuf op;

	op.sem_num = num;
	op.sem_op = -valor;
	op.sem_flg = 0;
	return semop(semid, &op, 1);
}

int sem_signal(int semid, int num, int valor) {
	struct sembuf op;

	op.sem_num = num;
	op.sem_op = valor;
	op.sem_flg = 0;
	return semop(semid, &op, 1);
}

int mutex_wait(int semid, int num) {
	return sem_wait(semid, num, 1);
}

int mutex_signal(int semid, int num) {
	return sem_signal(semid, num, 1);
}

#endif
