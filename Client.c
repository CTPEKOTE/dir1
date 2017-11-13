#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main (int argc, char** argv){
	int msqid , msqid2;
	int chislo , key1 = 100 , key2 = 200;


	struct mymsgbuf {
		long mtype;
		int ch;
	} mybuf;

	if((msqid = msgget(key1, 0666 | IPC_CREAT)) < 0) {
		printf("Can\'t get msqid\n");
		exit(-1);
	}
	if((msqid2 = msgget(key2, 0666 | IPC_CREAT)) < 0) {
		printf("Can\'t get msqid2\n");
		exit(-1);
	}


	mybuf.mtype = getpid();
	mybuf.ch = atoi(argv[1]);

	if (msgsnd(msqid, (struct mymsgbuf *) &mybuf, sizeof(int) , 0) < 0) {
			printf("Can\'t send message to queue\n");
			msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
			exit(-1);
	}
	if ((chislo = msgrcv(msqid2, (struct mymsgbuf *)&mybuf, sizeof(int) , mybuf.mtype , 0)) < 0){
			printf("Can\'t receive message from queue\n");
			exit(-1);
		}
		printf("%d\n",mybuf.ch);
		return 0;

}