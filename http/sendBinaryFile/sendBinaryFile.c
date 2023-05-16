
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>

void sendBinaryFile(int fd, char path[], char mime[]){

	printf("sendBinaryFile()\n");

	FILE *file;
	file = fopen(path, "rb");
	if ( file == NULL ) perror("sendBinaryFile fopen");
        //              M  K 
	int idx, max = 8000000; // 8MB
	size_t readCntRet;
	char buf[max];
	char *ptr;
	size_t size = 1;
	size_t nmemb = 1;

	for(idx=0;idx<max;idx++){
		ptr = &buf[idx];
		readCntRet = fread(ptr, size, nmemb, file);
		if(readCntRet < 1){
			printf("bytes read: %d\n", idx);	
			break;
		}
	}
	fclose(file);

	//  last one returned 0, so we can skip it, 
	int bodyLen = idx; // ie) Content-Length: %d, bodyLen

	char header[80];
	sprintf(header, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\nContent-Type: %s;\r\n\r\n", bodyLen, mime);
	// TYPE: image/x-icon

	int headerLen = strlen(header);

	int ret;

	// send header
	ret = send(fd, header, (size_t)headerLen, 0);
	if(ret == -1) perror("perror send: ");	

	// send image
	ret = send(fd, buf, (size_t)bodyLen, 0);
	if(ret == -1) perror("perror send: ");		
}


