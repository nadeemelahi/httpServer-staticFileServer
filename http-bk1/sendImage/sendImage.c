#include<stdio.h>
#include<string.h>
#include<sys/socket.h> // send()

void checkIfNull(void *item){
	if(item == NULL){
		printf("item is NULL");
	}
}
void sendImage( int fd, char imagepath[], char mime[] ){
	printf("sendImage()\n");

	char *inFileName = "./webroot/favicon.ico"; // 
	FILE *inFile;

	inFile = fopen(inFileName, "rb");
	checkIfNull(inFile);

	// size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
	// ptr - pointer to buf with min size*nmemb bytes
	// size - size in bytes of each element to be read
	// nmemb - number of elelemts 
	// stream - the input file to read
	// favicon is 1.4k
	int idx, max = 15000;
	size_t readCntRet;
	char buf[max];
	char *ptr;
	size_t size = 1;
	size_t nmemb = 1;

	for(idx=0;idx<max;idx++){
		ptr = &buf[idx];
		readCntRet = fread(ptr, size, nmemb, inFile);
		if(readCntRet < 1){
			printf("bytes read: %d\n", idx);	
			break;
		}
	}
	fclose(inFile);


	//  last one returned 0, so we can skip it, 
	int bodyLen = idx; // ie) Content-Length: %d, bodyLen

	char header[80];
	sprintf(header, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\nContent-Type: image/%s;\r\n\r\n", bodyLen, mime);
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
