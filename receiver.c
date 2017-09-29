#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
int buffer = 0, flip = 0;
void sighandler (int signo) {

	flip = 1;
	
	buffer *= 2;

	return;
}
void sighandler1 (int signo) {
	
	flip = 1;

	buffer *= 2;
	
	buffer += 1;


	return;
}
int main(int argc, char **argv){
	int pid , k;
	char i = 0;
	printf("pid is %d\n",pid = getpid());
	scanf("%d",&pid);
	
	signal(SIGINT , sighandler);
	signal(SIGILL , sighandler1);
	
	while(0 == 0){
		
		if( flip == 1 ){

			for (k = 0; k < 8; k ++){
				usleep(1000);
				fprintf(stdin," ");

			}
		

			for(k = 0; k < 8; k ++){
				i *= 2;
				i += buffer % 2;
				buffer /= 2;
				
			}

			printf("%c",i);
			i = 0;	

			flip = 0;
		}
		
		usleep(1000);
		fprintf(stdin,"\n");
		
	}
	
	
	
	return 0;
}
