#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int recvReq( int fd, char methodBuf[], char pathBuf[] );

void handleFileGet( int fd , char *path );

void handleClient( int fd ){
	printf("handleClient()\n");

	//                  1234567
	int tinyLim = 7; // DELETE
	int smLim = 128;
	char methodBuf[tinyLim];
	char pathBuf[smLim];

	int anyErrors = recvReq( fd , methodBuf, pathBuf );

	if ( anyErrors ) exit ( 1 ) ;

	printf ( "%s %s\n" , methodBuf , pathBuf ) ;

	char getMethod[] = "GET";
	int notMatch = strcmp(methodBuf, getMethod);
	if(!notMatch){
		// TODO 
		// check if req.path contains ? 
		// if so parse the key/values
		// else 
		handleFileGet( fd , pathBuf );
	}
}
