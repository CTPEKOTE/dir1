#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/ipc.h>                                            
#include <sys/shm.h>
#define SIZE 100
int main(){
	char array[SIZE];
	int shmid;
	int is_new = 1;
	int i = 0;
	key_t key = 322;
	if ((shmid = shmget(key, SIZE , 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
		if(errno != EEXIST){
			printf("Can't create shared memory\n");
                        exit(-1);
                } else {
                        if((shmid = shmget(key, SIZE  , 0)) < 0) {
                                printf("Can't find shared memory\n");
                                exit(-1);
                        }
                        is_new = 0;
                }
        }

        if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
                printf("Can't attach shared memory\n");
                exit(-1);
        }

	while(scanf("%c",&(array[i]) != "\n" && i < SIZE - 1){
                i++;
        }
	array[i + 1] = 0;
	

	if(shmdt(array) < 0){
                printf("Can't detach shared memory\n");
                exit(-1);
        }
	return 0;
}
