#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

typedef struct msgbuf {
	long    mtype;
	char    mtext[50];
} msg_buf;


main()
{
	int id;
	key_t key;
	msg_buf  rbuf,sbuf;
	size_t buf_length;

	key = 1234;

	if ((id = msgget(key, 0666)) < 0) {
		perror("msgget");
		exit(1);
	}


	while(1){
		
		if (msgrcv(id, &rbuf, 50, 1, 0) < 0) {
			perror("msgrcv");
			exit(1);
		}else
			printf("\nProcess 1:%s", rbuf.mtext);
		
		
		
		sbuf.mtype = 2;
		printf("\nEnter Message :");
		gets(&sbuf.mtext);
			
		buf_length = strlen(sbuf.mtext) + 1 ;
		if (msgsnd(id, &sbuf, buf_length, IPC_NOWAIT) < 0) {
			printf ("%d, %d, %s\n", id, sbuf.mtype, sbuf.mtext);
			perror("msgsnd");
			exit(1);
		}else 
			printf("Process 2:%s", sbuf.mtext);
	

	}
	
	exit(0);
}
