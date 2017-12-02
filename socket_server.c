#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#define MAXMSGLEN 100
#define PORT 5000
#define MAXQUEUE 10

struct clientinfo
{
	int fd , self;
	//char *msgstory;
	char name[11];
	int *sock , *clinum ;//, *preclinum;
};
struct retransarg
{
	int *sock;
	int *clinum;
	char *msgstory;
};
void die(char *msg) {
	printf("error: %s, %s\n", msg, strerror(errno));
	exit(1);
}

void* retranslator(void *x){//retranslator send last 1000 chars from servstory file
	struct retransarg *list = (struct retransarg*)x;
	long end , i;
	char message[126];

	FILE *servstory;
	if ((servstory = fopen("./servstory","a")) == NULL){
		die("Can't open servstory\n");
	}
	fclose(servstory);
	while(1){
		if ((servstory = fopen("./servstory","r")) == NULL){
			die("Can't open servstory\n");
		}
		fseek(servstory , 0 , SEEK_END);
		end = ftell(servstory);
		if(end >= 999){
			fseek(servstory , end - 999 , SEEK_SET);
			while(fgetc(servstory) != '[');
			i = ftell(servstory);
			fseek(servstory , i - 1 , SEEK_SET);
		}
		else {
			rewind(servstory);
		}
		//fscanf(servstory , "%s" , list -> msgstory);
		fgets(list -> msgstory , 1001 , servstory);
		while(fgets(message , 1001 , servstory) != '\0'){
			strcat(list -> msgstory , message);
		}
		fclose(servstory);
		//printf("%s\n", list -> msgstory);

		for(int i = 0; i < *(list -> clinum) ; i++){
			if (send((list ->sock)[i], list -> msgstory, 1001 , MSG_CONFIRM) < 0) {
				die("can't send msgstory\n");
			}
		}

		sleep(10);
	}
}

pthread_mutex_t lock;

void* client(void* a){//clients append servstory file
					//all strcat to fprintf servstory
	FILE *names , *passwords , *regnum , *servstory;
	if ((names = fopen("./names","a+")) == NULL){
		die("Can't open names array\n");
	}
	if ((passwords = fopen("./passwords","a+")) == NULL){
		die("Can't open passwords array\n");
	}
	if ((regnum = fopen("./regnum","a")) == NULL){
		die("Can't open regnum\n");
	}
	fclose(regnum);
	if ((regnum = fopen("./regnum","r+")) == NULL){
		die("Can't open regnum\n");
	}
	
	int regnu;
	fscanf(regnum , "%d" , &regnu);
	fclose(regnum);
	time_t local;
	struct tm *timeinfo;

	char message[MAXMSGLEN + 2] , timeval[26] , password[10] , arpass[10] , arname[10];
	int i , present = 0;
	struct clientinfo *arg = (struct clientinfo*)a;
	i = recv(arg -> fd, arg -> name, 10, 0);

	if (i < 0){
		die("Can't receive name\n");
	}
    
    for(i = 0 ; i < regnu ; i++){
    	fscanf(names , "%s" , arname);
    	fscanf(passwords , "%s" , arpass);
    	if (strcmp(arname , arg -> name) == 0){
    		present = 1;
    		break;
    	}
    }


    if (present > 0){ 
    	
    	if (send(arg ->fd, "Enter your password\n", 22 , MSG_CONFIRM) < 0) {
			die("can't send enter password");
		}
		
		if(recv(arg -> fd , password , 10, 0) < 0){
			die("Can't read password");
		}
		
		if(strcmp(password , arpass) != 0){
			if (send(arg -> fd, "Password is invalid", 21 , MSG_CONFIRM) < 0) {
				die("can't send enter password");
			}
			fclose(names);
			fclose(passwords);
			close(arg -> fd);
			return NULL;
		}
		else{
			if (send(arg -> fd, "You are logged in\nWelcome\n", 27 , MSG_CONFIRM) < 0) {
				die("can't send log in");
			}
			(arg -> sock)[*(arg -> clinum)] = arg -> fd;
			*(arg -> clinum) += 1;
		}
    
    }
    else{
    	if (send(arg -> fd, "Create your password", 22, MSG_CONFIRM) < 0) {
			die("can't send invent password");
		}
		if(i = recv(arg -> fd , password, 10, 0) < 0){
			die("Can't read password");
		}
		fprintf(names , "%s " , arg -> name);
		fprintf(passwords , "%s " , password);
		
		regnu++;
		if ((regnum = fopen("./regnum","w")) == NULL){
			die("Can't open passwords array\n");
		}
		fprintf(regnum , "%d" , regnu);
		fclose(regnum);
		(arg -> sock)[*(arg -> clinum)] = arg -> fd;
		*(arg -> clinum) += 1;
		if (send(arg -> fd, "You are logged in\nWelcome\n", 27 , MSG_CONFIRM) < 0) {
				die("can't send log in");
		}
    }
    
	time(&local);
	timeinfo = localtime(&local);
	asctime_r(timeinfo , timeval);
	*strchr(timeval,'\n') = '\0';
	pthread_mutex_lock(&lock);//connection message
	//strcat(arg -> msgstory , "[");
	//strcat(arg -> msgstory , timeval);
	//strcat(arg -> msgstory , "] ");
	if ((servstory = fopen("./servstory","a")) == NULL){
		die("Can't open servstory\n");
	}
	fprintf(servstory , "[%s] %s has connected\n", timeval , arg -> name);
	fclose(servstory);
	//strcat(arg -> msgstory ,arg -> name);
	//strcat(arg -> msgstory , " has connected\n");
	pthread_mutex_unlock(&lock);
	//printf("%s\n",arg -> msgstory);

	while(1){
		i = recv(arg -> fd , message, MAXMSGLEN , 0);
		if (i <= 0 ){
			break;
		}
			
		
		time(&local);
		timeinfo = localtime(&local);
		asctime_r(timeinfo , timeval);
		*strchr(timeval,'\n') = '\0';
		pthread_mutex_lock(&lock);
		/*strcat(arg -> msgstory , "[");
		strcat(arg -> msgstory , timeval);
		strcat(arg -> msgstory , " | ");
		strcat(arg -> msgstory ,arg -> name);
		strcat(arg -> msgstory , "] ");
		strcat(arg -> msgstory , message);
		strcat(arg -> msgstory , "\n");*/
		if ((servstory = fopen("./servstory","a")) == NULL){
			die("Can't open servstory\n");
		}
		fprintf(servstory , "[%s | %s] %s\n", timeval , arg -> name, message);
		fclose(servstory);
		pthread_mutex_unlock(&lock);
		//printf("%s\n",arg -> msgstory);
		
	}
	time(&local);
	timeinfo = localtime(&local);
	asctime_r(timeinfo , timeval);
	*strchr(timeval,'\n') = '\0';
	pthread_mutex_lock(&lock);//disconnection message
	/*strcat(arg -> msgstory , "[");
	strcat(arg -> msgstory , timeval);
	strcat(arg -> msgstory , "] ");
	strcat(arg -> msgstory ,arg -> name);
	strcat(arg -> msgstory , " has disconnected\n");*/
	if ((servstory = fopen("./servstory","a")) == NULL){
		die("Can't open servstory\n");
	}
	fprintf(servstory , "[%s] %s has disconnected\n", timeval , arg -> name);
	fclose(servstory);
	for (int k = arg -> self ; k < *(arg -> clinum) ; k++){
		(arg -> sock)[k] = (arg -> sock)[k + 1];
	}
	*(arg -> clinum) -= 1;
	//*(arg -> preclinum) -= 1;
	pthread_mutex_unlock(&lock);
	fclose(names);
	fclose(passwords);
	close(arg -> fd);
	//printf("%s\n",arg -> msgstory);
	
	return NULL;
}

int main(int argc, char *argv[]) {
	int listenfd;
	struct sockaddr_in serv_addr;
	pthread_t thread_id[1000] , retrans_id;
	/*FILE *namesfile;
	FILE *passwordsfile;*/
	

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {//Server creation
		die("can't create socket");
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(PORT); 

	if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		die("can't bind");
	}
	if (listen(listenfd, MAXQUEUE) < 0) {
		die("can't listen");
	}
	printf("server was started\n");//end of creation

	char story[1000] = {0} ;
	
	int clientfd[100];

	int connfd ;
	int *clinum = (int*)malloc(sizeof(int)) , *preclinum = (int*)malloc(sizeof(int));
	*clinum = 0;
	*preclinum = 0;
	struct clientinfo *arg;
	int i = 0;
	struct retransarg clients;
	clients.sock = clientfd;
	clients.msgstory = story;
	clients.clinum = clinum;
	pthread_create(&retrans_id , NULL , retranslator , (void*)&clients);

	while(1){
		if ((connfd = accept(listenfd , (struct sockaddr*)NULL, NULL)) < 0) {
			die("can't accept");
		}
		arg = (struct clientinfo*)malloc(sizeof(struct clientinfo));
		//arg -> msgstory = story;
		arg -> fd = connfd;
		arg -> sock = clientfd;
		arg -> self = *clinum;
		arg -> clinum = clinum;
		//arg -> preclinum = preclinum;
		//clientfd[*clinum] = connfd;
		printf("got new connection\n");
		pthread_create(&thread_id[*preclinum] , NULL , client , (void*)arg);
		*preclinum += 1;
		
		
	}
	

	

	return 0;
}
