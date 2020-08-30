#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

typedef struct msgbuf{
	long    mtype;
	char    mtext[50];
} msg_buf;

main()
{
	int id;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	msg_buf sbuf,rbuf;
	size_t buf_length;
	key = 1234;

	if ((id = msgget(key, msgflg )) < 0) {
		perror("msgget");
		exit(1);
	}
	
	while(1){
		
		sbuf.mtype = 1;
		printf("\nEnter Message :");
		gets(&sbuf.mtext);
		
		buf_length = strlen(sbuf.mtext) + 1 ;
		if (msgsnd(id, &sbuf, buf_length, IPC_NOWAIT) < 0) {
			printf ("%d, %d, %s\n", id, sbuf.mtype, sbuf.mtext);
			perror("msgsnd");
			exit(1);
		}else 
			printf("\nProcess 1:%s", sbuf.mtext);
	
		if (msgrcv(id, &rbuf, 50, 2, 0) < 0) {
			perror("msgrcv");
			exit(1);
		}else
			printf("\nProcess 2:%s", rbuf.mtext);
	}
	
	

	exit(0);
}
