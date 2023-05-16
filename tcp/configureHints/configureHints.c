#include<string.h> 
#include<netdb.h>

void configureHints( struct addrinfo *hints ){
	memset(hints, 0, sizeof *hints);
	hints->ai_flags = AI_PASSIVE;
	hints->ai_family = AF_UNSPEC;
	hints->ai_socktype = SOCK_STREAM;

}
