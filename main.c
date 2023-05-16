#include<stdio.h>
#include<netdb.h> // struct addrinfo

struct addrinfo *servinfo; 
// linked list -dyn allocated -needs to be global

void configureHints ( struct addrinfo *hints );

void gai ( struct addrinfo *hints, char *port );

int getSocketFD (  ) ;

void registerSigHandler ();

void listenLoop ( int sockfd );

int main ( int argc , char *argv[] ) { 

	printf("Usage: The default port is 8000. \n");
	printf("An example of suppling a different port: \n");
	printf("$./httpServer01 8080\n");

	char port[5] = "8000";
	if(argc > 1) sprintf( port , argv[1] ); 
	printf("Currently set listening port to %s\n", port);

	struct addrinfo hints;

	configureHints( &hints );

	gai( &hints , port);
	
	int sockfd = getSocketFD( );

	registerSigHandler( );

	listenLoop( sockfd );

	// handleClient(); 
	// called from fork'ed child process in
	// listenLoop for each client connection

	return 0;
}
