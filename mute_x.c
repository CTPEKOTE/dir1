#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#define TASK_N 100
#define THREAD_N 10

typedef enum{
	NEW,
	PROCESSING,
	DONE
}statuses;
typedef struct{
	int duration;
	int id;
	statuses status;
	pthread_t worker;
} task_t;

pthread_mutex_t lock;
task_t tasks[TASK_N];

void* my_thread(void* var){
	int frag = 0, k = 0;
	//long long unsigned worker = *((pthread_t*)(var + 8 + sizeof(statuses)));
	while(k <= TASK_N){
		task_t *copy = (task_t*)var;
		pthread_mutex_lock(&lock);
		while(copy[k].status != NEW /*&& k < TASK_N*/){
			//copy += sizeof(task_t);
			k++;
		}

		copy[k].status = PROCESSING;
		
		pthread_mutex_unlock(&lock);
		if (k >= TASK_N){

			break;
		}
		printf("Task No %d is putting thread to sleep for %d mks\n",copy[k].id, copy[k].duration);
		
		usleep(copy[k].duration);
		frag++;

		pthread_mutex_lock(&lock);
		copy[k].status = DONE;
		pthread_mutex_unlock(&lock);


	}
	printf("Worker has fragged %d tasks\n",frag);
	return NULL;
}
int main(){
	statuses status;
	pthread_t thread_id[THREAD_N];
	int result , i;

	for (i = 0; i < TASK_N; i++){
		tasks[i].id = i;
		tasks[i].duration = abs(random() % 1000);
	}

	for (i = 0; i < THREAD_N; i++){
		pthread_create(&(thread_id[i]), NULL, my_thread, (void*)(tasks));
	}
	for(i = 0; i < THREAD_N; i++){
		pthread_join(thread_id[i],NULL);
	}

	printf("END\n");

	pthread_mutex_destroy(&lock);

	return 0;
}