#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> // close(int fileDescriptor)
#include<netdb.h> // struct addrinfo

extern struct addrinfo *servinfo;

int getSocketFD(){

	struct addrinfo *ptr;
	int sockfd , yes = 1 , ret = 0;

	for ( ptr = servinfo; ptr != NULL; ptr = ptr->ai_next){

		sockfd = socket ( ptr->ai_family,
				ptr->ai_socktype,
				ptr->ai_protocol );
		if(sockfd == -1){
			perror("server: socket: ");
			continue;
		}
		
		

		ret = 0;
		ret = setsockopt(sockfd,
				SOL_SOCKET,
				SO_REUSEADDR,
				&yes,
				sizeof(int) );

		if(ret){
			perror("setsockopt() ");
			exit(1);
		}
		
		ret = 0;
		ret = bind(sockfd,
				ptr->ai_addr,
				ptr->ai_addrlen);

		if(ret == -1){
			close(sockfd);
			perror("server: bind: ");
			continue;
		}
		
		break;

	}

	freeaddrinfo(servinfo);
	if(ptr == NULL){
		printf("server failed to bind\n");
		exit(1);
	}

	int listenQueueLim = 10;
	ret = 0;
	ret = listen(sockfd, listenQueueLim);
	if(ret == -1){
		perror("listen() ");
		exit(1);
	}

	printf("server socket is configured \n");
	return sockfd;

}
