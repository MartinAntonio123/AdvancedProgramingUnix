#ifndef SEMAFOROS_H
#define SEMAFOROS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
/*
El problema a tratar es cigarrate smokers, ya que cada cliente tiene recursos infinitos de un tipo
y Benji tiene recursos infinitos de los tres tipos
La tecnica que usare para este problema sera que Benji obtenga un semaforo mutex y
genere numeros random representando los ingredientes, luego
haga una signal a un semaforo contador, asi los ingredientes estaran disponibles
cada otaco checa si hay los dos necesarios y si es asi hace el wait para tomarlos


*/
#define	BMUTEX 	0
#define VEINTE	1
#define	CINCUENTA	2
#define CIEN 3


int sem_wait(int semid, int sem_num, int val) {
	struct sembuf op;

	op.sem_num = sem_num;
	op.sem_op = -val;
	op.sem_flg = 0;
	return semop(semid, &op, 1);
}

int sem_signal(int semid, int sem_num, int val) {
	struct sembuf op;

	op.sem_num = sem_num;
	op.sem_op = val;
	op.sem_flg = 0;
	return semop(semid, &op, 1);
}

int mutex_wait(int semid, int sem_num) {
	return sem_wait(semid, sem_num, 1);
}

int mutex_signal(int semid, int sem_num) {
	return sem_signal(semid, sem_num, 1);
}

#endif
