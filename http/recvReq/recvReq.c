#include<stdio.h>
#include<string.h>
#include<sys/socket.h> // recv()

int recvReq( int fd , 
		char methodBuf[] , 
		char pathBuf[]     ){

	printf("\nrecvReq()\n");

	// must read the request first
	// http request
	int bigLim= 512;
	char reqBuf[bigLim];

	int readByteCnt = recv( fd , reqBuf , bigLim - 1 , 0 );
	if(readByteCnt == -1){ perror("recv"); return -1; }
	reqBuf[readByteCnt] = '\0';
	int reqLen = strlen(reqBuf);
	//printf("req recv() len: %d, : %s", len, reqBuf);

	// POST,GET,PUT,PATCH,DELETE 3-6 chars

	int idx, smLim = 128;
	char reqLine1Buf[smLim];

	for ( idx = 0 ; idx < smLim ; idx++ ) {

		if ( reqBuf[ idx ] == '\n' ) {

			reqLine1Buf [ idx ] = '\0'; break;
		}

		reqLine1Buf [ idx ] = reqBuf [ idx ] ;
	}
	//printf ( "request line 1: %s\n" , reqLine1Buf ) ;

	sscanf ( reqLine1Buf , "%s %s", methodBuf , pathBuf ) ;
	//printf ( "%s\n" , methodBuf );
	//printf ( "%s\n" , pathBuf );

	return 0;
}
