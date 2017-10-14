#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types>
#include <sys/shm.h>

int main(){
	int *array;
	int shmid;
	int is_new = 1;
	key_t key = 123;
	/*shmget is to create and get adress
	 * shmat is to attach memory to adress space
	 * shmdt is to detach memory
	 * shmctl is to manage memory*/
		
	return 0;
}

