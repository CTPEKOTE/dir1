#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* my_func(void *x){

        printf("Thread created\n");
        printf("input 0 is %llu input 1 is %llu\n",*((long long int*)x) , *((long long int*)(x + 8)));

        static long long int k;
        long long int result = 0, i;
	

        for(i = *((long long int*)x); i < *((long long int*)(x + 8)); i++){
                result += i;
        }
	
	k += result;

       return &k;
}
int main(int argc , char** argv){
        pthread_t *thread_id;
        int num_thread, k;
	long long int  i , shag , start , finish , sum = 0;  
        long long int* result = (long long int*)malloc(sizeof( long long int*));
        long long int* input;
        num_thread = atoi(argv[3]);
        start = atoll(argv[1]);
        finish = atoll(argv[2]);

        shag = (finish - start + 1) / num_thread;

        input = (long long int*)malloc(sizeof(long long int) * 2);

        *input = start;
        *(input + 1) = start + shag;

        thread_id = (pthread_t*) malloc(sizeof(pthread_t*) * num_thread);

        for(i = 0; i < num_thread; i++){

                k = pthread_create((thread_id + 8 * i),
                                        NULL ,
                                        my_func,
                                        (void*)input);
                if(k != 0){
                        printf("Can't create thread\n");
                        exit(1);
                }


       		input = (long long int*) malloc(2 * sizeof(long long int));
		*input = start + (i + 1) * shag;
		*(input + 1) = start + (i + 2) * shag;
        }
	for(i = 0; i < num_thread; i++){
	        pthread_join(*(thread_id + 8 *(i + 1) - 8) , (void**) &result);
	}	
	sum = *result;
	if(num_thread != 1){
		i = *(input + 1) - shag;
		while(i <= finish){
			sum += i;
			i++;
		}
	}	

        printf("Sum is %llu\n",sum);
        return 0;
}

