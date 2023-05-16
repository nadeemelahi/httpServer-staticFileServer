#include<stdio.h>
#include<stdlib.h> // NULL
#include<errno.h>
#include<wait.h>
#include<signal.h>
// let OS kill zombie processes
void sigchld_handler(int s){
	int saved_errno = errno;
	while(waitpid(-1,NULL,WNOHANG)>0);
	errno = saved_errno;
}
void registerSigHandler(){
	printf("registerSigHandler()\n");
	int ret = 0;
	struct sigaction sa;
	sa.sa_handler = sigchld_handler;
	sa.sa_flags = SA_RESTART;
	ret = sigaction(SIGCHLD, &sa, NULL);
	if(ret == -1){
		perror("sigaction");
		exit(1);
	}
}
