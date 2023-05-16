#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h> // sockaddr_in|6
#include<arpa/inet.h> // inet_ntop
#include<unistd.h> // fork()

void handleClient(int acceptSocketFD);


void listenLoop( int sockfd ){
	
	int acceptSocketFD;

	char addrStr[INET6_ADDRSTRLEN];
	socklen_t addrStrSize = sizeof addrStr;

	struct sockaddr_storage addrStorage;
	socklen_t sin_size;
	sin_size = sizeof addrStorage;

	struct sockaddr *clientAddr;
	clientAddr = ( struct sockaddr * ) &addrStorage;

	struct sockaddr_in *sa4;
	struct sockaddr_in6 *sa6;

	printf("listenLoop() while(1){} started\n");
	while(1){
		
		acceptSocketFD = accept(sockfd,
				clientAddr,
				&sin_size );

		if(acceptSocketFD == -1){
			perror("accept: ");
			continue;
		}

		if(clientAddr->sa_family == AF_INET){
			printf("--------------\nclient address is ip version 4\n");

			sa4 = ( struct sockaddr_in * )  clientAddr;
			inet_ntop(clientAddr->sa_family, 
					&(sa4)->sin_addr,
					addrStr, addrStrSize );

		} else if(clientAddr->sa_family == AF_INET6){
			printf("client address is ip version 6\n");

			sa6 = ( struct sockaddr_in6 * ) clientAddr;
			inet_ntop(clientAddr->sa_family, 
					&(sa6)->sin6_addr,
					addrStr, addrStrSize );

		} else {
			printf("should never happen, will be either 4 or 6\n");
		}	 

		printf("addrStr %s\n", addrStr);
		
		
		
		if( !fork() ){
			// fork returned 0 - child process
			close(sockfd);

			handleClient(acceptSocketFD);
			close(acceptSocketFD);
			//exit(0); // make to exit or break 
			//so  client process does not run while(1){} loop again
			exit(0);

		} else { 

			// parent process does nothing
			close(acceptSocketFD);
		}



	}

}
