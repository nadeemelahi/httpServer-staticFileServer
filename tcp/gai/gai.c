#include<stdio.h>
#include<stdlib.h> // NULL, abort()
#include<netdb.h> // struct addrinfo

extern struct addrinfo *servinfo;
void gai( struct addrinfo *hints,
		char *port	){

	int ret = getaddrinfo(NULL, port, hints, &servinfo);
	if( ret ){
	       printf("%s\n", gai_strerror(ret));
	       abort();
	}
}
