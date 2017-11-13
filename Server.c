#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
struct arg {
		long mtype;
		int ch;
		int id;
	};

struct  mymsgbuf {
		long mtype;
		int ch;
	};

void* kvadrat(void* input){

	struct arg *var = (struct arg*)input;
	sleep(var -> ch);
	var -> ch *= var -> ch;
	struct mymsgbuf output = {var -> mtype , var -> ch };
	if (msgsnd(var -> id , (struct mymsgbuf *) &output , sizeof(int) , 0) < 0) {
			printf("Can\'t send message to queue\n");
			//msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
			exit(-1);
	}
	return input;

}

int main(){
	struct arg *input;
	int msqid , msqid2;
	key_t key = 100, key2 = 200;
	pthread_t *thread_id = NULL;
	int thread_number = 0;
	int i = 0;
	struct  mymsgbuf mybuf;
	int error;

	if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
		printf("Can\'t get msqid\n");
		exit(-1);
	}

	if((msqid2 = msgget(key2, 0666 | IPC_CREAT)) < 0) {
		printf("Can\'t get msqid2\n");
		exit(-1);
	}
	while(1){
		if ((msgrcv(msqid, (struct mymsgbuf *)&mybuf, sizeof(int) , 0 , 0)) < 0){
			printf("Can\'t receive message from queue\n");
			exit(-1);
		}
		input = (struct arg*)malloc(sizeof(struct arg));
		input -> mtype = mybuf.mtype;
		input -> ch = mybuf.ch;
		input -> id = msqid2;
		thread_number++;
		thread_id = (pthread_t*)realloc(thread_id , sizeof(pthread_t) * thread_number);
		pthread_create( (thread_id + thread_number - 1 ) , NULL , kvadrat , (void*)(input));
		while(i < thread_number){
			if (error = pthread_tryjoin_np(*(thread_id + i) , NULL) == 0){
				for(int k = i ; k < thread_number ; k++){
					if (k < thread_number - 1){
						*(thread_id + k) = *(thread_id + k + 1);
					}
				}
				if (thread_number > 1){
					thread_id = (pthread_t*)realloc(thread_id , sizeof(pthread_t) * (thread_number - 1));
					thread_number--;
				}
				else {
					thread_id = NULL;
				}
				i = 0;
			}
			i++;
		}
		i = 0;
	}
	return 0;
}