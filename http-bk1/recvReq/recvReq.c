#include<stdio.h>
#include<stdlib.h> // exit()
#include<string.h>
#include<sys/socket.h> // recv()

void recvReq( int fd, int smLim,
		char methodBuf[smLim],
		char pathBuf[smLim],
		char protoBuf[smLim]   ){

	printf("\nrecvReq()\n");

	// must read the request first
	// http request
	int bigLim= 512;
	char reqBuf[bigLim];

	memset(reqBuf, 0x00, bigLim);

	int readByteCnt = recv(fd, reqBuf, bigLim - 1, 0);
	if(readByteCnt == -1){
		perror("recv");
		exit(1);
	}

	reqBuf[readByteCnt] = '\0';
	int len = strlen(reqBuf);
	printf("req recv() len: %d, : %s", len, reqBuf);

	// POST,GET,PUT,PATCH,DELETE 3-6 chars

	int idx;
	char reqLine1Buf[smLim];

	for ( idx = 0 ; idx < smLim; idx++ ){

		if(reqBuf[idx] == '\n'){
			reqLine1Buf[idx] = '\0';
			break;
		}
		reqLine1Buf[idx] = reqBuf[idx];
	}
	printf("request line 1: %s\n", reqLine1Buf);

	sscanf(reqLine1Buf, "%s %s %s", methodBuf, pathBuf, protoBuf);

}
