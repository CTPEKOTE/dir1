#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SIZE 100

int main(){
	char *array;
	int shmid;
	int is_new = 1;
	key_t key = 322;
	/*shmget is to create and get adress
	 * shmat is to attach memory to adress space
	 * shmdt is to detach memory
	 * shmctl is to manage memory*/
	  if ((shmid = shmget(key, SIZE, 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
                if(errno != EEXIST){
                        printf("Can't create shared memory\n");
                        return -1;
                } else {
                        if((shmid = shmget(key, SIZE , 0)) < 0) {
                                printf("Can't find shared memory\n");  
                                return -1;                                        
                        }                                      
                        is_new = 0;
                }
        }                                                              
                                                                             
        if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {                      
                printf("Can't attach shared memory\n");                        
                return -1;                                                             
        }
	for (int i = 0; i < SIZE - 1; i++){
		array[i] = 0;
	} 
	
	while(array[99] == 0){
		sleep(1);
	}

	while (array[i] != 0 && i < SIZE - 1){
		printf("%c",array[i]); 
		i++;
	}
	printf("\n");

	if(shmdt(array) < 0){
                printf("Can't detach shared memory\n");
                return -1;
        }		
	return 0;
}

