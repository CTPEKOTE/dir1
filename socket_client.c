#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>

struct threadarg{
	int fd;
	char *story , *message;
};
void die(char *msg) {
	printf("error: %s, %s\n", msg, strerror(errno));
	exit(1);
}
void* receiver(void* x){//autorefresh needed
	int i , k = 0;
	//char message[20];
	char locstory[2000];
	struct threadarg *arg = (struct threadarg*)x;
	while (k < 2){
		
		if(i = recv(arg -> fd , arg -> message, 30, 0) < 0){
				die("Can't read server message");
		}
			k++;
			//printf("%s\n",message);
		
		if (strcmp(arg -> message , "Password is invalid") == 0){
			close(arg -> fd);
			return NULL;
		}
	}
	//termios is kicking in! terminals are melting!
	while(1){
		if(i = recv(arg -> fd ,locstory, 1000 , 0) < 0){
			die("Can't read server message");
		}
		if(strlen(locstory) > 1){
			strcpy(arg -> story , locstory);
		}
		

		sleep(5);
	}
}
void clear(void){
	char *arg[] = {"clear",NULL};
	execvp(arg[0],arg);
	return ;
}
int main(int argc, char *argv[]) {
	int sockfd;
	
	struct sockaddr_in serv_addr; 

	if(argc != 3) {
		printf("\n Usage: %s <ip of server> <nickname> \n",argv[0]);
		return 1;
	} 

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		die("can't create socket");
	} 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000); 

	if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
		die("inet_pton error occured");
	}

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		die("Connect Failed");
	}

	//printf("sending msg '%s' to server...\n", argv[2]);
	if (send(sockfd, argv[2], 1 + strlen(argv[2]), MSG_CONFIRM) < 0) {
		die("can't send");
	}
	//printf("send have done\n");
	char message[100] = {0}, a , story[2000] , messagec[100];
	pthread_t thread_id;
	struct threadarg arg;
	arg.fd = sockfd;
	arg.story = story;
	arg.message = message;
	int i = 0, pass = 0;

	int fd, fd2;
	struct termios settings , backup;
	

	pthread_create(&thread_id , NULL , receiver , (void*)&arg);
	tcgetattr(STDIN_FILENO , &backup);
	tcgetattr(STDIN_FILENO , &settings);
	settings.c_lflag &= ~(ECHO|ICANON);

	//settings.c_cc[VMIN] = 1;
	//settings.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW ,  &settings);
	sleep(10);
	printf("%s\n", message);
	while(pass == 0){
		
		a = getc(stdin);
		switch(a){
			case '\0':{
				messagec[i] = '\0';
				if (send(sockfd, messagec, strlen(messagec) + 1, MSG_CONFIRM) < 0) {
					die("can't send");
				}
				for(i = strlen(messagec) ; i > -1 ; i--){
					messagec[0] = '\0';
				}
				i = 0;
				pass = 1;
				break;
			}
			case 127:{
				messagec[strlen(messagec) - 1] = '\0';
				i--;
				break;
			}
			default:{
				messagec[i] = a;
				i++;
				break;
			}

		}
		if(fork() == 0){
			clear();
		}
		wait(NULL);
		//usleep(10000);
		printf("%s\n%s\n%d\n",message , messagec , i);
		
	}
	//i = 0;
	
	while(1){
		//scanf("%s", message);
		//fgets(message , 100 , stdin);
		
		a = getchar();
		switch(a){
			case '\0':{
				messagec[i] = '\0';
				if (send(sockfd, messagec, strlen(messagec) + 1, MSG_CONFIRM) < 0) {
					die("can't send");
				}
				for (i = strlen(messagec) ; i > -1 ; i--){
					messagec[i] = '\0';
				}
				i = 0;
				break;
			}
			case 127:{
				if(i > 0){
					messagec[strlen(messagec) - 1] = '\0';
					i--;
				}
				break;
			}
			default:{
				messagec[i] = a;
				i++;
				break;
			}

		}
		if(fork() == 0){
			clear();
		}
		//usleep(10000);
		wait(NULL);
		printf("%s\n---------------------------------------------------------------\n%s\n%d\n",story , messagec, i);

		//message[strcspn(message , "\n")] = 0;
		//if (send(sockfd, message, strlen(message) + 1, MSG_CONFIRM) < 0) {
		//	die("can't send");
		//}
	}
	tcsetattr(STDIN_FILENO, 0 , &backup);
	//pthread_join(thread_id , (void**)NULL);
	return 0;
}
