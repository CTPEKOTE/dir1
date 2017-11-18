#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
	int *array;
	int shmid; 
	int is_new = 1;
	key_t key = 123;
	int semid;
	key_t semkey = 124;
	struct sembuf mybuf , mybuf2;

	if ((semid = semget(semkey , 2, 0666 | IPC_CREAT)) < 0) {
		printf("Can`t get semid\n");
		exit(-1);
	}

	if ((shmid = shmget(key , sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
		if(errno != EEXIST) {
			printf("Can't create shared memory\n");
			exit(-1);
		} else {
			if((shmid = shmget(key, sizeof(int), 0)) < 0){
				printf("Can't find shared memory\n");
				exit(-1);
			}
			is_new = 0;
		}
	}

	if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
		printf("Can't attach shared memory\n");
		exit(-1);
	}

	mybuf.sem_op = 1;// 0 is to close b. 1 is to close a
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;

	mybuf2.sem_op = -1;
	mybuf2.sem_flg = 0;
	mybuf2.sem_num = 1;

	while(1){
		scanf("%d", array);

		if (*array == 0){
			break;
		}

		printf("before 1-st sem\n");
		if (semop(semid , &mybuf , 1) < 0) {
			printf("Can`t wait for condition\n");
			exit(-1);
		}
		printf("before 2-nd sem\n");
		if (semop(semid , &mybuf2 , 1) < 0) {
			printf("Can`t wait for condition\n");
			exit(-1);
		}
		printf("after them \n");

		printf("square is %d\n", *array);
	}

	if (shmdt(array) < 0) {
		printf("Can't detach shared memory\n");
		exit(-1);
	}


	return 0;
}

