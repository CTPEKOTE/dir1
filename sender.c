#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
int main(int argc, char **argv){
	int pid , i = 0, k;
	char buffer[100];
	printf("pid is %d\n",k = getpid());
	scanf ("%d",&pid);

	while ( 0 == 0 ){
		scanf("%c",buffer);
		while( buffer[i]  != '\n'){
			
			i++;
			scanf("%c",&buffer[i]);
			
		}
	
		buffer[i + 1] = 0;		
		

		while ( i >= 0) {
	
			for(k = 0 ; k < 8; k++){
			
				if (*buffer % 2 == 0)
					kill(pid , SIGINT);
				else 
					kill(pid , SIGILL);
			
				*buffer /= 2;

				usleep(1000);
	
			}
			
			for(k = 0; k < i; k++){
		
				buffer[k] = buffer[k + 1];
			}

			usleep(1000);
		
			i--;
			
		}

		i = 0;

	}

	
	return 0;
}
